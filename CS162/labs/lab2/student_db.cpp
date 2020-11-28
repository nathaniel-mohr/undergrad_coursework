#include "student_db.h"

student* create_student_db(int size){
	student *db = new student[size];
}

void get_student_db_info(student* db, int size, fstream & input){
	for(int i = 0; i < size; i++){
		input >> db[i].id_number;
		input >> db[i].student_first_name;
		input >> db[i].student_last_name;
		input >> db[i].major;
	}
}

void delete_student_db_info(student** db, int size){
	delete[] *db;
	db = NULL;
}

void copy_db(student* from, student* to, int size){
	for(int i = 0; i < size; i++){
		to[i] = from[i];
	}
}

void id_sort(student* arr, int size){
	student temp;
	for(int i = 0; i < size; i++){
		for(int j = i + 1; j < size; j++){
			if(arr[i].id_number > arr[j].id_number){
				temp = arr[i];
				arr[i] = arr[j];	
				arr[j] = temp;
			}
		}
	}
}

void last_name_sort(student* arr, int size){
	student temp;
	for(int i = 0; i < size; i++){
		for(int j = i + 1; j < size; j++){
			if(arr[i].student_last_name > arr[j].student_last_name){
				temp = arr[i];
				arr[i] = arr[j];	
				arr[j] = temp;
			}
		}
	}
}

int major_count(student* arr, int size){
	int count = 0;
	for(int i = 1; i < size; i++){
		if(arr[i].major != arr[i-1].major){
			count++;
		}
	}
	return count;
}

void write_student(student s, fstream & o){
	o << s.id_number << " ";
	o << s.student_first_name << " ";
	o << s.student_last_name << " ";
	o << s.major << endl;
}

void write_db(student* db, int size, fstream & output){
	for(int i = 0; i < size; i++){
		write_student(db[i], output);
	}
	output << endl;

}
