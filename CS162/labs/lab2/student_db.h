#include <fstream>
#include <string>
#include <iostream>

using namespace std;

struct student{
	int id_number;
	string student_first_name;
	string student_last_name;
	string major;
};

student* create_student_db(int);
void get_student_db_info(student*, int, fstream &);
void delete_student_db_info(student**, int);
void copy_db(student*, student*, int);
void id_sort(student*, int);
void last_name_sort(student*, int);
int major_count(student*, int);
void write_student(student, fstream &);
void write_db(student*, int, fstream &);

