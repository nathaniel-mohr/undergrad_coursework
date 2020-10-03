// Nathaniel Mohr
// CS 344
// Project 3 - smallsh

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

int signal_status = -1, exit_status = 0;
int background = 1;
struct sigaction SIGINT_action = {0}, SIGTSTP_action = {0};
pid_t pid_array[100];
int pid_num = 0;

void catchSIGTSTP(int);
void shellLoop();
char* readLine();
char** parseLine(char*);
int shellExecute(char**);
int shell_cd(char**);
int shell_status();
int shell_exec(char**);
int find_num_args(int, int, int, int);
void get_exit_status(int);

int main(){
	SIGINT_action.sa_handler = SIG_IGN;
	sigfillset(&SIGINT_action.sa_mask);
	SIGINT_action.sa_flags = SA_RESTART;

	SIGTSTP_action.sa_handler = catchSIGTSTP;
	sigfillset(&SIGTSTP_action.sa_mask);
	SIGTSTP_action.sa_flags = SA_RESTART;

	sigaction(SIGINT, &SIGINT_action, NULL);
	sigaction(SIGTSTP, &SIGTSTP_action, NULL);

	shellLoop();

	return 0;
}

// SIGTSTP handler
void catchSIGTSTP(int signo){
	// Toggle background variable
	if(background == 1){
		background = 0;
		write(1, "Entering foreground-only mode (& is now ignored)\n", 49);
	}else{
		background = 1;
		write(1, "Exiting foreground-only mode\n", 29);
	}
}

// Shell
void shellLoop(){
	char* line;
	char** args;
	int status;
	int i, j, child_exit_status;
	pid_t wpid;

	do{
		// Check background processes
		for(i = pid_num - 1; i >= 0; i--){
			wpid = waitpid(pid_array[i], &child_exit_status, WNOHANG);
			if(wpid != 0){
				printf("background pid %ld is done: ", (long)pid_array[i]);
				fflush(stdout);
				// Get status of process
				if(WIFEXITED(child_exit_status) != 0){
					printf("exit value %d\n", WEXITSTATUS(child_exit_status));
				}else{
					printf("terminated by signal %d\n", WTERMSIG(child_exit_status));
				}
				// Remove pid from array
				if(j < i){
					for(j = i; j < pid_num; j++){
						pid_array[j] = pid_array[j - 1];
					}
				}
				pid_num--;
			}
		}

		printf(": ");
		fflush(stdout);

		line = readLine();
		args = parseLine(line);
		status = shellExecute(args);

		free(line);
		free(args);
	}while(status);
}

// Reads in the user input
char* readLine(){
	ssize_t buffer = 0;
	char* line = NULL;
	getline(&line, &buffer, stdin);
	line[strlen(line) - 1] = '\0';
	return line;
}

// Breaks the user input into arguments
char** parseLine(char* line){
	char** args = NULL;
	int j, i, num_args = 0;
	char* arg = strtok(line, " ");
	char temp[256], temp2[256];

	// Tokenizes each argument
	while(arg){
		args = realloc(args, sizeof(char*) * ++num_args);
		args[num_args - 1] = arg;
		arg = strtok(NULL, " ");
	}

	// Makes sure the last argument is a null character
	args = realloc(args, sizeof(char*) * (num_args+1));
	args[num_args] = '\0';

	// Replaces any "$$" with the pid
	for(i = 0; i < num_args; i++){
		for(j = 0; j < strlen(args[i]); j++){
			if(args[i][j] == '$' && args[i][j+1] == '$'){
				// Concatenate the beginning of the string
				// with pid and the end of the string
				strncpy(temp2,args[i] + (j + 2), strlen(args[i]) - (j + 2));
				sprintf(args[i], "%s%ld%s", temp, (long)getpid(), temp2);
				break;
			}
			temp[j] = args[i][j];
		}
		// Reset temp
		memset(temp,0,sizeof(temp));
	}

	return args;
}

// Executes the arguments
int shellExecute(char** args){
	if(args[0] == NULL || args[0][0] == '#'){
		return 1;
	}else if(strcmp(args[0], "exit") == 0){
		return 0;
	}else if(strcmp(args[0], "cd") == 0){
		return shell_cd(args);
	}else if(strcmp(args[0], "status") == 0){
		return shell_status();
	}else{
		// not built in commands
		return shell_exec(args);
	}
}

// Handles "cd"
int shell_cd(char** args){
	if(args[1] == NULL || strcmp(args[1],"~") == 0){
		chdir(getenv("HOME"));
	}else{
		chdir(args[1]);
	}
	return 1;
}

// Handles "status"
int shell_status(){
	// Exited normally
	if(exit_status != -1){
		printf("exit value %d\n", exit_status);
		fflush(stdout);
	// Terminated by signal
	}else if(signal_status != -1){
		printf("terminated by signal %d\n", signal_status);
		fflush(stdout);
	// M Night Shyamalan twist
	}else{
		printf("unknown error\n");
		fflush(stdout);
	}
	return 1;
}

int shell_exec(char** args){
	pid_t pid, wpid;
  int status, i = 0, num_args = 0, file_open = 1;
	int input_index = -1, output_index = -1, background_index = -1;
	char input[256], output[256];
	int input_result, output_result;
	int in = dup(0), out = dup(1);

	// Breaks the "arguments" into the agurments, the input, the ouput and &
	while(args[i] != NULL){
		// Handles input
		if(strcmp(args[i], "<") == 0){
			input_index = i;
			strcpy(input,args[i+1]);
			input_result = open(input, O_RDONLY);
			// File unable to be opened
			if(input_result == -1){
				printf("cannot open %s for input\n", input);
				fflush(stdout);
				exit_status = 1;
				file_open = 0;
			}else{
				// Change input from stdin to file
				dup2(input_result, 0);
				fcntl(input_result, F_SETFD, FD_CLOEXEC);
			}
		}
		// Handles output
		if(strcmp(args[i], ">") == 0){
			output_index = i;
			strcpy(output,args[i+1]);
			// Open file / create if not exist
			output_result = open(output, O_TRUNC | O_CREAT | O_WRONLY, 0777);
			// Change output from stdout to file
			dup2(output_result, 1);
			fcntl(output_result, F_SETFD, FD_CLOEXEC);
		}
		// Handles background
		if(strcmp(args[i], "&") == 0 && args[i+1] == NULL){
			background_index = i;
			// If no input file, set to /dev/null
			if(input_index == -1){
				dup2("/dev/null", 0);
			}
			// If no output file, set to /dev/null
			if(output_index == -1){
				dup2("/dev/null", 1);
			}
		}
		i++;
	}

	// Copies just the arguments of the line into a new array
	num_args = find_num_args(input_index, output_index, background_index, i);
	char* new_args[num_args+1];
	memcpy(new_args,args,sizeof(char*)*(num_args+1));
	new_args[num_args] = NULL;

	// Only fork if there was no input file
	// or the input file was opened successfuly
	if(file_open == 1){
		pid = fork();

		// Successful fork
		if(pid == 0){
			SIGINT_action.sa_handler = SIG_DFL;
			sigaction(SIGINT, &SIGINT_action, &SIGINT_action);
			if(execvp(new_args[0], new_args) == -1){
				printf("smallsh: %s: command not found\n", new_args[0]);
				fflush(stdout);
				exit(1);
			}
		// Forking error
		}else if(pid < 0){
			printf("forking error\n");
			fflush(stdout);
			exit(1);
		// Back to parent
		}else{
			// Foreground processes
			if(background_index == -1 || background == 0){
				wpid = waitpid(pid, &status, 0);
			// Background processes
			}else{
				printf("background pid is %d\n", pid);
				fflush(stdout);
				pid_array[pid_num++] = pid;
			}
		}

		// Update _status variables
		get_exit_status(status);

		// Print out signal termination
		if(signal_status != -1){
			printf("terminated by signal %d\n", signal_status);
			fflush(stdout);
		}
	}

	dup2(in, 0);
	dup2(out, 1);

  return 1;
}

// Finds where the arguments stop
int find_num_args(int input_index, int output_index, int background_index, int i){
		// If there was <, > and &
		// find which came first
		// and that is where arguments end
		if(input_index != -1 && output_index != -1 && background_index != -1){
				if(input_index < output_index && input_index < background_index){
					return input_index;
				}else if(output_index < background_index){
					return output_index;
				}else{
					return background_index;
				}

		// If there was < and >
		// find which came first
		// and that is where arguments end
		}else if(input_index != -1 && output_index != -1){
			return input_index < output_index ? input_index : output_index;

		// If there was < and &
		// find which came first
		// and that is where arguments end
		}else if(input_index != -1 && background_index != -1){
			return input_index < background_index ? input_index : background_index;

		// If there was > and &
		// find which came first
		// and that is where arguments end
		}else if(output_index != -1 && background_index != -1){
			return output_index < background_index ? output_index : background_index;

		// If there was only <
		// That is where arguments end
		}else if(input_index != -1){
			return input_index;

		// If there was only >
		// That is where arguments end
		}else if(output_index != -1){
			return output_index;

		// If there was only &
		// That is where arguments end
		}else if(background_index != -1){
			return background_index;

		// If there was no <, > or &
		// then the line is all arguments
		}else{
			return i;
		}
}

// Gets the exit status
void get_exit_status(int status){
	if(WIFEXITED(status) != 0){
		exit_status = WEXITSTATUS(status);
		signal_status = -1;
	}else{
		signal_status = WTERMSIG(status);
		exit_status = -1;
	}
}
