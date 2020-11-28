/*
 * Program Filename: state_facts.h
 * Author: Nathaniel Mohr
 * Date: 4/10/18
 * Description: header file for state_facts.cpp
 * Input: none
 * Ouput: none
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

struct county{
	string name; // name of county
	string *city; // array of city names in county
	int cities; // number of cities in county
	int population; // total population of county
	float avg_income; // avg household income
	float avg_house; // avg household price
};
struct state{
	string name; // name of state
	struct county *c; // array of counties
	int counties; // number of counties in state
	int population; // total population of state
};
bool is_valid_arguments(char *[], int);
int get_size(char**);
char* get_input_file(char**);
state* create_states(int);
void get_state_data(state *, int, ifstream &);
county* create_counties(int);
void get_county_data(county *, int, ifstream &);
void delete_info(state **, int);
state max_state_pop(state*, int);
county max_county_pop(state*, int);
void cout_income_search(state*, int, int);
void write_income_search(state*, int, int, ofstream&);
int* avg_household_costs(state*, int);
int avg_household_cost(state);
state* state_name_sort(state*, int);
state* state_pop_sort(state*, int);
state* county_pop_sort(state*, int);
state* county_name_sort(state*, int);
bool get_output();
string get_output_file();
bool is_int(string);
int string_to_int(string);
int get_income();
void cout_facts(state*, int);
void cout_counties(county*, int);
void cout_states(state*, int);
void cout_arr(state*, int, int*);
void write_facts(state*, int, ofstream &);
void write_counties(county*, int, ofstream &);
void write_states(state*, int, ofstream &);
void write_arr(state*, int, int*, ofstream &);
