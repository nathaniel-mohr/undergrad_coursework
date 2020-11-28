/*
 * Program Filename: state_facts.cpp
 * Author: Nathaniel Mohr
 * Date: 4/10/18
 * Description: Describes functions that read in info about states
 * 		as well as functions that perform actions on these states
 * 		and giving the information back to the user
 * Input:
 * Output:
 */

#include "state_facts.h"

/*
 * Function: is_valid_arguments
 * Description: checks to see if command line arguments are valid
 * Parameters: char**, int
 * Pre-Conditions: 
 * Post-Conditions: arguments valid
 */
bool is_valid_arguments(char* argv[], int argc){
	if(argc != 5){
		return false;
	}else if(((strcmp(argv[1], "-s") != 0) && (strcmp(argv[1], "-f") != 0))){
		return false;
	}else if(((strcmp(argv[3], "-s") != 0) && (strcmp(argv[3], "-f") != 0))){
		return false;
	}else if(strcmp(argv[1], argv[3]) == 0){
		return false;
	}else{
		return true;
	}
}

/*
 * Function: get_size
 * Description: gets the size of the states array from the command line arguments
 * Parameters: char**
 * Pre_Conditions: 
 * Post_Conditions: size gotten 
 */
int get_size(char** argv){
	if(strcmp(argv[1], "-s") == 0){
		return atoi(argv[2]);
	}else{
		return atoi(argv[4]);
	}
}

/*
 * Function: get_input_file
 * Description: gets the name of the file containing the state information
 * Parameters: char**
 * Pre_Conditions:
 * Post_Conditions: file name gotten
 */
char* get_input_file(char** argv){
	if(strcmp(argv[1], "-f") == 0){
		return argv[2];
	}else{
		return argv[4];
	}
}

/*
 * Function: create_states
 * Description: creates an array of states of size given
 * Parameters: int
 * Pre_Conditions: size was accurate
 * Post_Conditions: array created
 */
state* create_states(int size){
	return new state[size];
}

/*
 * Function: get_state_data
 * Description: gets information of the states from the file
 * Parameters: state*, int, ifstream&
 * Pre_Conditions: 
 * Post_Conditions: state array filled with data
 */
void get_state_data(state* states, int size, ifstream &input){
	for(int i = 0; i < size; i++){
		input >> states[i].name;
		input >> states[i].population;
		input >> states[i].counties;
		states[i].c = create_counties(states[i].counties);
		get_county_data(states[i].c, states[i].counties, input);
	}
}

/*
 * Function: create_counties
 * Description: creates an array of counties of size given
 * Parameters: size
 * Pre_Conditions: size was accurate
 * Post_Conditions: array created
 */
county* create_counties(int size){
	return new county[size];
}

/*
 * Function: get_county_data
 * Description: gets information of the counties from the file
 * Parameters: county*, int, ifstream &
 * Pre_Conditions: 
 * Post_Conditions: county array filed with data
 */
void get_county_data(county* counties, int size, ifstream &input){
	for(int i = 0; i < size; i++){
		input >> counties[i].name;
		input >> counties[i].population;
		input >> counties[i].avg_income;
		input >> counties[i].avg_house;
		input >> counties[i].cities;
		counties[i].city = new string[counties[i].cities];
		for(int j = 0; j < counties[i].cities; j++){
			input >> counties[i].city[j];
		}
	}
}

/*
 * Function: delete_info
 * Description: deletes all dynamically allocated memory
 * Parameters: state**, int
 * Pre_Conditions: size is accurate, array had dynamically allocated memory
 * Post_Conditions: memory deleted
 */
void delete_info(state** states, int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (*states)[i].counties; j++){
			delete[] (*states)[i].c[j].city;
		}
		delete[] (*states)[i].c;
	}
	delete[] *states;
	states = NULL;
}

/*
 * Function: max_state_pop
 * Description: determines the state with the highest population
 * Parameters: state*, int
 * Pre_Conditions: array and size are appropriate
 * Post_Conditions: max determined
 */
state max_state_pop(state* states, int size){
	int max = 0, flag = 0;
	for(int i = 0; i < size; i++){
		if(states[i].population > max){
			max = states[i].population;
			flag = i;
		}
	}
	return states[flag];
}

/*
 * Function: max_county_pop
 * Description: determines the county with the highest population
 * Parameters: state*, int
 * Pre_Conditions: array and size are appropriate
 * Post_Conditions: max determined
 */
county max_county_pop(state* states, int size){
	int max = 0, state_num = 0, county_num = 0;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < states[i].counties; j++){
			if(states[i].c[j].population > max){
				max = states[i].c[j].population;
				state_num = i;
				county_num = j;
			}
		}
	}
	return states[state_num].c[county_num];

}

/*
 * Function: cout_income_search
 * Description: prints to the screen the counties with income above val
 * Parameters: state*, int, int
 * Pre_Conditions: array and size are appropriate
 * Post_Conditions: counties determined
 */
void cout_income_search(state* states, int size, int val){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < states[i].counties; j++){
			if(states[i].c[j].avg_income > val){
				cout << states[i].c[j].name << " ";
			}
		}
	}
	cout << "\n" << endl;
}

/*
 * Function: write_income_search
 * Description: writes to a file the counties with income above val
 * Parameters: state*, int, int ofstream
 * Pre_Conditions: array and size are appropriate
 * Post_Conditions: counties determined
 */
void write_income_search(state* states, int size, int val, ofstream &output){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < states[i].counties; j++){
			if(states[i].c[j].avg_income > val){
				output << states[i].c[j].name << " ";
			}
		}
	}
	output << "\n" << endl;
}

/*
 * Function: avg_household_costs
 * Description: determines the avg_houehold cost of each state
 * Parameters: states*, int
 * Pre_Conditions: array and size are appropriate
 * Post_Conditions: averages determined
 */
int* avg_household_costs(state* states, int size){
	int *arr = new int[size];
	for(int i = 0; i < size; i++){
		arr[i] = avg_household_cost(states[i]);
	}
	return arr;
}

/*
 * Function: avg_household_cost
 * Description: determines the avg_houehold cost of state
 * Parameters: state
 * Pre_Conditions: state is filled
 * Post_Conditions: average determined
 */
int avg_household_cost(state s){
	int sum = 0;
	for(int i = 0; i < s.counties; i++){
		sum += s.c[i].avg_house;
	}
	return sum / s.counties;
}

/*
 * Function: state_name_sort
 * Description: sorts the states in terms of name
 * Parameters: state*, int
 * Pre_Conditions: state* and int are valid
 * Post_Conditions: states sorted
 */
state* state_name_sort(state* states, int size){
	state *temp_states = states;
	state temp;
	for(int i = 0; i < size; i++){
		for(int j = i+1; j < size; j++){
			if(temp_states[i].name > temp_states[j].name){
				temp = temp_states[i];
				temp_states[i] = temp_states[j];
				temp_states[j] = temp;
			}
		}
	}
	return temp_states;
}

/*
 * Function: state_pop_sort
 * Description: sorts the states in terms of population
 * Parameters: state*, int
 * Pre_Conditions: state* and int are valid
 * Post_Conditions: states sorted
 */
state* state_pop_sort(state* states, int size){
	state* temp_states = states;
	state temp;
	for(int i = 0; i < size; i++){
		for(int j = i+1; j < size; j++){
			if(temp_states[i].population > temp_states[j].population){
				temp = temp_states[i];
				temp_states[i] = temp_states[j];
				temp_states[j] = temp;
			}
		}
	}
	return temp_states;
}

/*
 * Function: county_pop_sort
 * Description: sort the counties in terms of population
 * Parameters: state*, int
 * Pre_Conditions: state* and int are valid
 * Post_Conditions: counties sorted
 */
state* county_pop_sort(state* states, int size){
	state *temp_states = states;
	county temp;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < temp_states[i].counties; j++){
			for(int k = j+1; k < temp_states[i].counties; k++){
				if(temp_states[i].c[j].population > temp_states[i].c[k].population){
					temp = temp_states[i].c[j];
					temp_states[i].c[j] = temp_states[i].c[k];
					temp_states[i].c[k] = temp;
				}
			}
		}		
	}
	return temp_states;
}

/*
 * Function: county_name_sort
 * Description: sort the counties in terms of name
 * Parameters: state*, int
 * Pre_Conditions: state* and int are valid
 * Post_Conditions: counties sorted
 */
state* county_name_sort(state* states, int size){
	state *temp_states = states;
	county temp;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < temp_states[i].counties; j++){
			for(int k = j+1; k < temp_states[i].counties; k++){
				if(temp_states[i].c[j].name > temp_states[i].c[k].name){
					temp = temp_states[i].c[j];
					temp_states[i].c[j] = temp_states[i].c[k];
					temp_states[i].c[k] = temp;
				}
			}
		}
			
	}
	return temp_states;
}

/*
 * Function: get_output
 * Description: determines where the facts will be outputed
 * Parameters: none
 * Pre_Conditions: none
 * Post_Conditions: source determined
 */
bool get_output(){
	string choice;
	do{
		cout << "Do you want the info printed to the screen(1) or a file(0): ";
		getline(cin, choice);
	}while(choice != "1" && choice != "0");
	if(choice == "1"){
		return true;
	}else{
		return false;
	}
}

/*
 * Function: get_ouput_file
 * Description: gets the name of the file where the facts are written
 * Parameters: none
 * Pre_Conditions: none
 * Post_Conditions: file name gotten
 */
string get_output_file(){
	string file;
	cout << "What is the name of your file?: "; 
	getline(cin, file);
	return file;
}

/*
 * Function: is_int
 * Description: determines if a string has an integer equivalence
 * Parameters: string
 * Pre_Conditions: none
 * Post_Conditions: status determined
 */
bool is_int(string input){
	int neg = 0;
	if(input[0] == '-'){
		neg = 1;
	}
	for(int i = neg; i < input.length(); i++){
		if(input[i] < '0' || input[i] > '9'){
			return false;
		}
	}
	return true;
}

/*
 * Function: string_to_int
 * Description: determines the int equivalent of the string
 * Parameters: string
 * Pre_Conditions: string has an int equivalence
 * Post_Conditions: int value determined
 */
int string_to_int(string input){
	int neg = 0, ans = 0;
	if(input[0] == '-'){
		neg = 1;
	}
	for(int i = neg; i < input.length(); i++){
		ans *= 10;
		ans += (input[i] - 48);
	}
	if(neg == 1){
		ans = ans * -1;
	}
	return ans;
}

/*
 * Function: get_income
 * Description: gets the income that the counties will be compared to
 * Parameters: none
 * Pre_Conditions: none
 * Post_Conditions: income obtained
 */
int get_income(){
	string input;
	do{
		cout << "What income value would you like your counties to be above? ";
		getline(cin, input);
	}while(is_int(input) == false);
	return string_to_int(input);
}

/*
 * Function: cout_facts
 * Description: prints the facts to the screen
 * Parameters: state*, int
 * Pre_Conditions: state* and int are valid
 * Post_Conditions: facts printed
 */
void cout_facts(state* states, int size){
	int counties = 0, income = 0;
	income = get_income();
	int* avg_cost = avg_household_costs(states, size);
	cout << "STATE WITH LARGEST POPULATION" << endl;
	cout << (max_state_pop(states, size)).name << endl << endl;
	cout << "COUNTY WITH LARGEST POPULATION" << endl;
	cout << max_county_pop(states, size).name << endl << endl;
	cout << "COUNTIES WITH INCOMES OVER " << income << endl;
	cout_income_search(states, size, income);
	cout << "AVERGAGE HOUSEHOLD COST FOR ALL COUNTIES IN EACH STATE" << endl;
	cout_arr(states, size, avg_cost);
	delete[] avg_cost;
	cout << "STATES SORTED BY POPULATION" << endl;
	cout_states(state_pop_sort(states, size), size);
	cout << "STATES SORTED BY NAME" << endl;
	cout_states(state_name_sort(states, size), size);
	cout << "COUNTIES WITHIN STATES SORTED BY POPULATION" << endl;
	cout_states(county_pop_sort(states, size), size);
	cout << "COUNTIES WITHIN STATES SORTED BY NAME" << endl;
	cout_states(county_name_sort(states, size), size);
}

/*
 * Function: cout_counties
 * Description: counties are printed to screen
 * Parameters: county*, int
 * Pre_Conditions: county* and int are valid
 * Post_Conditions: counties printed
 */
void cout_counties(county* c, int size){
	cout << "county_size: " << size << endl;
	for(int i = 0; i < size; i++){
		cout << "county " << i << " " << c[i].name << " ";
	}
	cout << endl;
}

/*
 * Function: cout_states
 * Description: states are printed to screen
 * Parameters: state*, int
 * Pre_Conditions: state* and int are valid
 * Post_Conditions: states printed
 */
void cout_states(state* states, int size){
	for(int i = 0; i < size; i++){
		cout << states[i].name << endl;
		for(int j = 0; j < states[i].counties; j++){
			cout << states[i].c[j].name << " ";
		}
		cout << endl << endl;
	}
}

/*
 * Function: cout_arr
 * Description: prints array corresponding to state to screen
 * Parameters: state*, int, int*
 * Pre_Conditions: state*, int, and int* are valid
 * Post_Conditions: array printed
 */
void cout_arr(state* states, int size, int* arr){
	for(int i = 0; i < size; i++){
		cout << states[i].name << ": " << arr[i] << endl;	
	}
	cout << endl;
}

/*
 * Function: write_facts
 * Description: writes facts to corresponding file
 * Parameters: state*, int, ofstream &
 * Pre_Conditions: state*, int, and ofstream& are valid
 * Post_Conditions: facts written to file
 */
void write_facts(state* states, int size, ofstream &output){
	int counties = 0, income = 0;
	income = get_income();
	int* avg_cost = avg_household_costs(states, size);
	output << "STATE WITH LARGEST POPULATION" << endl;
	output << max_state_pop(states, size).name << endl << endl;
	output << "COUNTY WITH LARGEST POPULATION" << endl;
	output << max_county_pop(states, size).name << endl << endl;
	output << "COUNTIES WITH INCOMES OVER " << income << endl;
	write_income_search(states, size, income, output);
	output << "AVERGAGE HOUSEHOLD COST FOR ALL COUNTIES IN EACH STATE" << endl;
	write_arr(states, size, avg_cost, output);
	delete[] avg_cost;
	output << "STATES SORTED BY POPULATION" << endl;
	write_states(state_pop_sort(states, size), size, output);
	output << "STATES SORTED BY NAME" << endl;
	write_states(state_name_sort(states, size), size, output);
	output << "COUNTIES WITHIN STATES SORTED BY POPULATION" << endl;
	write_states(county_pop_sort(states, size), size, output);
	output << "COUNTIES WITHIN STATES SORTED BY NAME" << endl;
	write_states(county_name_sort(states, size), size, output);
}

/*
 * Function: write_counties 
 * Description: writes counties to the file
 * Parameters: county*, int, ofstream &
 * Pre_Conditions: county*, int and ofsream & are valid
 * Post_Conditions: counties written
 */
void write_counties(county* c, int size, ofstream &output){
	for(int i = 0; i < size; i++){
		output << c[i].name << " ";
	}
	output << endl;
}

/*
 * Function: write_states
 * Description: writes states to the file
 * Parameters: state*, int, ofstream &
 * Pre_Conditions: state*, int and ofsream & are valid
 * Post_Conditions: states written
 */
void write_states(state* states, int size, ofstream &output){
	for(int i = 0; i < size; i++){
		output << states[i].name << endl;
		for(int j = 0; j < states[i].counties; j++){
			output << states[i].c[j].name << " ";
		}
		output << endl << endl;
	}
}

/*
 * Function: write_arr
 * Description: write array with state to file
 * Parameters: state*, int, int*, ofstream &
 * Pre_Conditions: state*, int, int*, and ofsream & are valid
 * Post_Conditions: array written
 */
void write_arr(state* states, int size, int* arr, ofstream &output){
	for(int i = 0; i < size; i++){
		output << states[i].name << ": " << arr[i] << endl;	
	}
	output << endl;
}

