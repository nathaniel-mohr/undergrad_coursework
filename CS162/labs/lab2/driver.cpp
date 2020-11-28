#include "student_db.h"

int main(){
	fstream input, output;
	int size, majors;
	student *db, *db_id_sort, *db_last_name_sort;

	input.open("input.txt");

	if(input.is_open()){
		input >> size;
		db = create_student_db(size);
		db_id_sort = create_student_db(size);
		db_last_name_sort = create_student_db(size);

		get_student_db_info(db, size, input);

		copy_db(db, db_id_sort, size);
		copy_db(db, db_last_name_sort, size);

		id_sort(db_id_sort, size);
		last_name_sort(db_last_name_sort, size);
		majors = major_count(db, size);
	}else{
		cout << "File did not open" << endl;
	}

	input.close();


	output.open("output.txt");

	if(output.is_open()){
		output << "STUDENTS" << endl;
		write_db(db, size, output);
		output << "SORT STUDENTS BY ID NUMBER" << endl;
		write_db(db_id_sort, size, output);
		output << "SORT STUDENTS BY LAST NAME" << endl;
		write_db(db_last_name_sort, size, output);
		output << "NUMBER OF UNIQUE MAJORS" << endl;
		output << majors;
	}else{

		cout << "File did not open" << endl;
	}

	output.close();

	delete_student_db_info(&db, size);
	delete_student_db_info(&db_id_sort, size);
	delete_student_db_info(&db_last_name_sort, size);
	return 0;
}
