/*
 * Program Filename: assignment3.cpp
 * Author: Nathaniel Mohr
 * Date: 1/29/18
 * Description: Prints all possible outcomes of 16 different helper functions
 * Input: Some user input in the form of string literals
 * Output: Prints to the screen
 */

#include <iostream>
#include <string>
#include "helper_functions.h"

using namespace std;

int main() {
	cout << " 1. check_range" << endl;
	cout << "    a. check_range(0,10,5)" << endl;
	cout << "       Expected: 1" << endl;
	cout << "       Actual  : " << check_range(0,10,5) << endl;
	if(check_range(0,10,5) == true){
		cout << "       PASS" << endl;
	}else{
		cout << "       FAIL" << endl;
	}
	cout << "    b. check_range(0,10,11)" << endl;
	cout << "       Expected: 0" << endl;
	cout << "       Actual  : " << check_range(0,10,11) << endl;
	if(check_range(0,10,5) == false){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << " 2. is_int" << endl;
	cout << "    a. is_int(\"10\")" << endl;
	cout << "       Expected: 1" << endl;
	cout << "       Actual  : " << is_int("10") << endl;
	if(is_int("10") == true){
		cout << "       PASS" << endl;
	}else{
		cout << "       FAIL" << endl;
	}
	cout << "    b. is_int(\"bag\")" << endl;
	cout << "       Expected: 0" << endl;
	cout << "       Actual  : " << is_int("bag") << endl;
	if(is_int("bag") == false){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << " 3. is_float" << endl;
	cout << "    a. is_float(\"1.23\")" << endl;
	cout << "       Expected: 1" << endl;
	cout << "       Actual  : " << is_float("1.23") << endl;
	if(is_float("1.23") == true){
		cout << "       PASS" << endl;
	}else{
		cout << "       FAIL" << endl;
	}
	cout << "    b. is_int(\"14\")" << endl;
	cout << "       Expected: 0" << endl;
	cout << "       Actual  : " << is_float("14") << endl;
	if(is_float("14") == false){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << " 4. is_capital" << endl;
	cout << "    a. is_capital('A')" << endl;
	cout << "       Expected: 1" << endl;
	cout << "       Actual  : " << is_capital('A') << endl;
	if(is_capital('A') == true){
		cout << "       PASS" << endl;
	}else{
		cout << "       FAIL" << endl;
	}
	cout << "    b. is_capital('b')" << endl;
	cout << "       Expected: 0" << endl;
	cout << "       Actual  : " << is_capital('b') << endl;
	if(is_capital('b') == false){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << " 5. is_even" << endl;
	cout << "    a. is_even(4)" << endl;
	cout << "       Expected: 1" << endl;
	cout << "       Actual  : " << is_even(4) << endl;
	if(is_even(4) == true){
		cout << "       PASS" << endl;
	}else{
		cout << "       FAIL" << endl;
	}
	cout << "    b. is_even(5)" << endl;
	cout << "       Expected: 0" << endl;
	cout << "       Actual  : " << is_even(5) << endl;
	if(is_even(5) == false){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << " 6. is_odd" << endl;
	cout << "    a. is_odd(5)" << endl;
	cout << "       Expected: 1" << endl;
	cout << "       Actual  : " << is_odd(5) << endl;
	if(is_odd(5) == true){
		cout << "       PASS" << endl;
	}else{
		cout << "       FAIL" << endl;
	}
	cout << "    b. is_odd(4)" << endl;
	cout << "       Expected: 0" << endl;
	cout << "       Actual  : " << is_odd(4) << endl;
	if(is_odd(4) == false){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << " 7. equality_test" << endl;
	cout << "    a. equality_test(4,5)" << endl;
	cout << "       Expected: -1" << endl;
	cout << "       Actual  : " << equality_test(4,5) << endl;
	if(equality_test(4,5) == -1){
		cout << "       PASS" << endl;
	}else{
		cout << "       FAIL" << endl;
	}
	cout << "    b. equality_test(5,4)" << endl;
	cout << "       Expected: 1" << endl;
	cout << "       Actual  : " << equality_test(5,4) << endl;
	if(equality_test(5,4) == 1){
		cout << "       PASS" << endl;
	}else{
		cout << "       FAIL" << endl;
	}
	cout << "    c. equality_test(5,5)" << endl;
	cout << "       Expected: 0" << endl;
	cout << "       Actual  : " << equality_test(5,5) << endl;
	if(equality_test(5,5) == 0){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << " 8. float_is_equal" << endl;
	cout << "    a. float_is_equal(4.0, 4.4, .5)" << endl;
	cout << "       Expected: 1" << endl;
	cout << "       Actual  : " << float_is_equal(4.0,4.4,.5) << endl;
	if(float_is_equal(4.0,4.4,4.5) == true){
		cout << "       PASS" << endl;
	}else{
		cout << "       FAIL" << endl;
	}
	cout << "    b. float_is_equal(4.0, 4.6, .5)" << endl;
	cout << "       Expected: 0" << endl;
	cout << "       Actual  : " << float_is_equal(4.0,4.6,.5) << endl;
	if(float_is_equal(4.0,4.6,.5) == false){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << " 9. numbers_present" << endl;
	cout << "    a. numbers_present(\"chocol4te\")" << endl;
	cout << "       Expected: 1" << endl;
	cout << "       Actual  : " << numbers_present("chocol4te") << endl;
	if(numbers_present("chocol4te") == true){
		cout << "       PASS" << endl;
	}else{
		cout << "       FAIL" << endl;
	}
	cout << "    b. numbers_present(\"chocolate\")" << endl;
	cout << "       Expected: 0" << endl;
	cout << "       Actual  : " << numbers_present("chocolate") << endl;
	if(numbers_present("chocolate") == false){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << "10. letters_present" << endl;
	cout << "    a. letters_present(\"ahD7\")" << endl;
	cout << "       Expected: 1" << endl;
	cout << "       Actual  : " << numbers_present("ahD7") << endl;
	if(letters_present("ahD7") == true){
		cout << "       PASS" << endl;
	}else{
		cout << "       FAIL" << endl;
	}
	cout << "    b. letters_present(\"93.3\")" << endl;
	cout << "       Expected: 0" << endl;
	cout << "       Actual  : " << letters_present("93.3") << endl;
	if(letters_present("93.3") == false){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << "11. contains_sub_string" << endl;
	cout << "    a. contains_sub_string(\"coconut\", \"con\")" << endl;
	cout << "       Expected: 1" << endl;
	cout << "       Actual  : " << contains_sub_string("coconut", "con") << endl;
	if(contains_sub_string("coconut", "con") == true){
		cout << "       PASS" << endl;
	}else{
		cout << "       FAIL" << endl;
	}
	cout << "    b. contains_sub_string(\"coconut\", \"cob\")" << endl;
	cout << "       Expected: 0" << endl;
	cout << "       Actual  : " << contains_sub_string("coconut", "cob") << endl;
	if(contains_sub_string("coconut", "cob") == false){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << "12. word_count" << endl;
	cout << "    a. word_count(\"This is not a string\")" << endl;
	cout << "       Expected: 5" << endl;
	cout << "       Actual  : " << word_count("This is not a string") << endl;
	if(word_count("This is not a string") == 5){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << "13. to_upper" << endl;
	cout << "    a. to_upper(\"b4n.nas\")" << endl;
	cout << "       Expected: \"B4N.NAS\"" << endl;
	cout << "       Actual  : \"" << to_upper("b4n.nas") << "\"" << endl;
	if(to_upper("b4n.nas") == "B4N.NAS"){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << "14. to_lower" << endl;
	cout << "    a. to_lower(\"b4N.nAS\")" << endl;
	cout << "       Expected: \"b4n.nas\"" << endl;
	cout << "       Actual  : \"" << to_lower("b4N.nAS") << "\"" << endl;
	if(to_lower("b4N.nAS") == "b4n.nas"){
		cout << "       PASS\n" << endl;
	}else{
		cout << "       FAIL\n" << endl;
	}

	cout << "15. get_int" << endl;
	cout << "    " << get_int() << endl;

	cout << "16. get_float" << endl;
	cout << "    " << get_float() << endl;

	return 0;
}
