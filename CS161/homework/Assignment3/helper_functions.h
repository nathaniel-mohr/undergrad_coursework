/*
 * Program Filename: helper_functions.h
 * Author: Nathaniel Mohr
 * Date: 1/27/18
 * Description: Declarations of 16 helper functions
 * Input:  None
 * Output: None
 */

#include <string>

using namespace std;

bool check_range(int lower_bound, int upper_bound, int test_value);

bool is_int(string num);

bool is_float(string num);

bool is_capital(char letter);

bool is_even(int num);

bool is_odd(int num);

int equality_test(int num1, int num2);

bool float_is_equal(float num1, float num2, float precision);

bool numbers_present(string sentence);

bool letters_present(string sentence);

bool contains_sub_string(string sentence, string sub_string);

int word_count(string sentence);

string to_upper(string sentence);

string to_lower(string sentence);

int get_int();

float get_float();
