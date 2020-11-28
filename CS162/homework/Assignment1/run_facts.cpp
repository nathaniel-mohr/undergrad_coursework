/*
 * Program Filename: run_facts.cpp
 * Author: Nathaniel Mohr
 * Date: 4/10/18
 * Description: 
 * Input:
 * Output:
 */
#include "state_facts.h"

/*
 * Function: main
 * Description: 
 * Parameters: int, char**
 * Pre_Condition: none
 * Post_Condition: 
 */
int main(int argc, char** argv){
	int size = 0;
	ifstream input; 
	ofstream output;
	state *states;
	
	if(is_valid_arguments(argv, argc) == false){
		cout << "Please enter: exe_file -s #_states -f data.txt" << endl;
		return 0;
	}
		
	size = get_size(argv);
	input.open(get_input_file(argv));
	
	states = create_states(size);
	
	if(input.is_open()){
		get_state_data(states, size, input);
	}else{
		cout << "File did not open" << endl;
		return 0;
	}
	input.close();
	
	if(get_output() == true){
		cout_facts(states, size);
	}else{
		output.open(get_output_file().c_str());
		if(output.is_open()){
			write_facts(states, size, output);
		}else{
			cout << "File did not open" << endl;
			return 0;
		}
		output.close();
	}
	
	delete_info(&states, size);
}
