#include "restaurant.h"

//accessors
Menu Restaurant::get_menu() const{return menu;}
int Restaurant::get_num_employees() const{return num_employees;}
employee* Restaurant::get_employees() const{return employees;}
int Restaurant::get_num_days() const{return num_days;}
hours* Restaurant::get_week() const{return week;}
string Restaurant::get_name() const{return name;}
string Restaurant::get_phone() const{return phone;}
string Restaurant::get_address() const{return address;}

//mutators
void Restaurant::set_menu(Menu m){
	menu = m;}
void Restaurant::set_num_employees(int num){
	num_employees = num;}
void Restaurant::set_employees(employee* e){
	employees = e;}
void Restaurant::set_num_days(int num){
	num_days = num;}
void Restaurant::set_week(hours* h){
	week = h;}
void Restaurant::set_name(string n){
	name = n;}
void Restaurant::set_phone(string p){
	phone = p;}
void Restaurant::set_address(string a){
	address = a;}

//default constructor
Restaurant::Restaurant(){
	num_employees = 0;
	employees = NULL;
	num_days = 0;
	week = NULL;
	name = "";
	phone = "";
	address = "";
}

//non-default constructor
Restaurant::Restaurant(Menu m, int num_e, employee* e, int num_d, hours* h, string n, string p, string a){
	menu = m;
	num_employees = num_e;
	employees = e;
	num_days = num_d;
	week = h;
	name = n;
	phone = p;
	address = a;
}

//copy constructor
Restaurant::Restaurant(const Restaurant& orig){
	menu = orig.menu;
	num_employees = orig.num_employees;
	if(num_employees == 0){
		employees = NULL;
	}else{
		employees = new employee[num_employees];
		for(int i = 0; i < num_employees; i++){
			employees[i] = orig.employees[i];
		}
	}
	num_days = orig.num_days;
	if(num_days == 0){
		week = NULL;
	}else{
		week = new hours[num_days];
		for(int i = 0; i < num_days; i++){
			week[i] = orig.week[i];
		}
	}
	name = orig.name;
	phone = orig.phone;
	address = orig.address;
}

//assignment operator overload
const Restaurant& Restaurant::operator=(const Restaurant& orig){
	cout << "restaurant aoo" << endl;
	menu = orig.menu;
	num_employees = orig.num_employees;
	if(employees != NULL){
		delete[] employees;
	}
	if(num_employees == 0){
		employees = NULL;
	}else{
		employees = new employee[num_employees];
		for(int i = 0; i < num_employees; i++){
			employees[i] = orig.employees[i];
		}
	}
	num_days = orig.num_days;
	if(week != NULL){
		delete[] week;
	}
	if(num_days == 0){
		week = NULL;
	}else{
		week = new hours[num_days];
		for(int i = 0; i < num_days; i++){
			week[i] = orig.week[i];
		}
	}
	name = orig.name;
	phone = orig.phone;
	address = orig.address;
	return *this;
}

//destructor
Restaurant::~Restaurant(){
	delete[] employees;
	delete[] week;
}

void Restaurant::load_data(){
	ifstream rf;
	string line; int num_lines;
	rf.open("restaurant_info.txt");
	getline(rf,name);
	cout << name; 
	getline(rf,phone); 
	getline(rf,address);
	rf >> num_days;
	week = new hours[num_days];
	for(int i = 0; i < num_days; i++){
		rf >> week[i].day;
		rf >> week[i].open_hour;
		rf >> week[i].close_hour;
	}
	rf.close();
	menu.load_menu();
	rf.open("employee.txt");
	while(getline(rf, line))
		++num_lines;
	num_employees = num_lines - 1;
	rf.close();
	rf.open("employee.txt");
	employees = new employee[num_employees]; 
	for(int i = 0; i < num_employees; i++){
		rf >> employees[i].id;
		rf >> employees[i].first_name;
		rf >> employees[i].last_name;
		rf >> employees[i].password;
	}
	rf.close();
}

bool Restaurant::login(string id, string password){
	for(int i = 0; i < num_employees; i++){
		if(employees[i].id == id){
			if(employees[i].password == password){
				return true;	
			}
		}
	}
	cout << "Credentials do not match" << endl;
	return false;
}

void Restaurant::view_menu(){
	cout << "\n         " << name << " Menu" << endl;
	menu.print_pizzas();
}

void Restaurant::view_hours(){
	for(int i = 0; i < num_days; i++){
		cout << week[i].day << " ";
		cout << week[i].open_hour << " ";
		cout << week[i].close_hour << endl;
	}
}

void Restaurant::view_address(){
	cout << address << endl;
	cout << endl;
}

void Restaurant::view_phone(){
	cout << phone << endl;
	cout << endl;
}

void Restaurant::search_menu_by_price(){
	string size;
	Menu temp;
	int upper_bound = 0;
	do{
		cout << "What size pizza would you like to search cost?" << endl;
		getline(cin, size);
	}while(size != "small" && size != "medium" && size != "large");
	cout << "What is the max you would pay for your " << size << " pizza?" << endl;
	cin >> upper_bound;
	cin.ignore();
	cin.clear();
	temp = menu.search_pizza_by_cost(upper_bound, size);
	temp.print_pizzas();
}

void Restaurant::search_by_ingredients(){
	string ans;
	cout << "Do you want to search for ingredients to include (I) or to exclude (E)?" << endl;
	do{
		getline(cin, ans);
	}while(ans != "I" && ans != "E");
	if(ans == "I"){
		include();
	}else{
		exclude();
	}
}

void Restaurant::include(){
	string ans;
	int num_ingredients = 0;
	string *ingredients = new string[num_ingredients];
	get_ingredients(&num_ingredients, &ingredients);
	Menu temp = menu.search_pizza_by_ingredients_to_include(ingredients, num_ingredients);
	temp.print_pizzas();
	cout << "Would you like to exclude ingredients now? (Y) or (N)" << endl;
	getline(cin, ans);
	if(ans == "Y"){
		get_ingredients(&num_ingredients, &ingredients);
		temp = temp.search_pizza_by_ingredients_to_exclude(ingredients, num_ingredients);
		temp.print_pizzas();
	}
	cout << "Would you like to order with this menu? (Y) or (N)" << endl;
	getline(cin, ans);
	if(ans == "Y"){
		place_order(temp.get_pizzas());
	}
}

void Restaurant::exclude(){
	string ans;
	int num_ingredients = 0;
	string *ingredients = new string[num_ingredients];
	get_ingredients(&num_ingredients, &ingredients);
	Menu temp = menu.search_pizza_by_ingredients_to_include(ingredients, num_ingredients);
	temp.print_pizzas();
	cout << "Would you like to include ingredients now? (Y) or (N)" << endl;
	getline(cin, ans);
	if(ans == "Y"){
		get_ingredients(&num_ingredients, &ingredients);
		temp = temp.search_pizza_by_ingredients_to_include(ingredients, num_ingredients);
		temp.print_pizzas();
	}
	cout << "Would you like to order with this menu? (Y) or (N)" << endl;
	getline(cin, ans);
	if(ans == "Y"){
		place_order(temp.get_pizzas());
	}
}

void Restaurant::get_ingredients(int* num, string** ingredients){
	cout << "How many ingredients?" << endl;
	cin >> *num;
	cin.ignore();
	cin.clear();
	*ingredients = new string[*num];
	for(int i = 0; i < *num; i++){
		cout << "Ingredient #" << i+1 << endl;
		getline(cin,(*ingredients)[i]);
	}
}

void Restaurant::place_order(Pizza* selection){
	string input;
	ofstream wf;
	ifstream rf;
	char order_num;
	int num;
	rf.open("orders.txt");
	while(!rf.eof()){
		getline(rf, input);
		order_num = input[0];
	}
	rf.close();
	order_num++;
	wf.open("orders.txt");
	wf << order_num;
	cout << "What is the name for the order?" << endl;
	getline(cin, input);
	wf << input;
	cout << "What is the credit card number?" << endl;
	getline(cin, input);
	wf << input;
	cout << "What is the address?" << endl;
	getline(cin, input);
	wf << input;
	cout << "What is the phone number?" << endl;
	getline(cin, input);
	wf << input;
	cout << "How many differennt pizzas would you like?" << endl;
	cin >> num;
	cin.ignore();
	cin.clear();
	for(int i = 0; i < num; i++){
		cout << "What is the name of pizza #" << i+1 << " ?" << endl;
		getline(cin, input);
		wf << input;
		cout << "How many of those would you like?" << endl;
		getline(cin, input);
		wf << input;
	}
	wf << endl;
	wf.close();
}

void Restaurant::change_hours(){
	string d, open, close;
	cout << "Which day would you like to change hours for? ";
	getline(cin, d);
	cout << "What is the new opening hour? ";
	getline(cin, open);
	cout << "What is the new closing hour? ";
	getline(cin, close);
	for(int i = 0; i < num_days; i++){
		if(week[i].day == d){
			week[i].open_hour = open;
			week[i].close_hour = close;
			break;
		}
		break;
	}
	update_restaurant_info();
}

void Restaurant::add_to_menu(){
	int num;
	string input;
	Pizza *temp = new Pizza[menu.get_num_pizzas()+1];
	for(int i = 0; i < menu.get_num_pizzas(); i++){
		temp[i] = menu.get_pizzas()[i];
	}
	cout << "Name of pizza" << endl;
	cin >> input;
	temp[menu.get_num_pizzas()+1].set_name(input);

	cout << "cost of small" << endl;
	cin >> num;
	temp[menu.get_num_pizzas()+1].set_small_cost(num);

	cout << "cost of medium" << endl;
	cin >> num;
	temp[menu.get_num_pizzas()+1].set_medium_cost(num);

	cout << "cost of large" << endl;
	cin >> num;
	temp[menu.get_num_pizzas()+1].set_large_cost(num);

	cout << "Number of ingredients" << endl;
	cin >> num;
	temp[menu.get_num_pizzas()+1].set_num_ingredients(num);

	string *str_temp = new string[num];

	for(int i = 0; i < num; i++){
		cout << "Ingredient #" << i+1 << endl;
		cin >> input;
		str_temp[i] = input;
	}
	temp[menu.get_num_pizzas()+1].set_ingredients(str_temp);
	
	Menu temp_menu(menu.get_num_pizzas()+1, temp);
	menu = temp_menu;
}

void Restaurant::remove_from_menu(){
	string pizza;
	int num = 0;
	Pizza *temp = new Pizza[menu.get_num_pizzas()-1];
	cout << "What is the name of the pizza you would like to remove?" << endl;
	for(int i = 0; i < menu.get_num_pizzas(); i++){
		if(menu.get_pizzas()[i].get_name() != pizza){
			temp[num] = menu.get_pizzas()[i];
			num++;	
		}
	}
	Menu temp_menu(menu.get_num_pizzas()-1, temp);
	menu = temp_menu;
}

void Restaurant::view_orders(){
	ifstream rf;
	string line;
	rf.open("orders.txt");
	while(!rf.eof()){
		getline(rf, line);
		cout << line;
	}
	rf.close();
	cout << endl;
}

void Restaurant::remove_orders(){
	char order;
	ifstream rf;
	ofstream wf;
	string line;
	view_orders();
	cout << "What order number would you like to remove?" << endl;	
	cin >> order;
	rf.open("orders.txt");
	wf.open("temp.txt");
	while(!rf.eof()){
		getline(rf, line);
		if(line[0] != order){
			wf << line << endl;
		}
	}
	rf.close();
	wf.close();
	remove("orders.txt");
	rename("temp.txt", "orders.txt");
}

void Restaurant::update_restaurant_info(){
	ofstream wf;
	string line;
	wf.open("temp.txt");
	wf << name << endl;
	wf << phone << endl;
	wf << address << endl;
	wf << num_days << endl;
	for(int i = 0; i < num_days; i++){
		wf << week[i].day << " " << week[i].open_hour << " " << week[i].close_hour << endl;
	}
	wf.close();
	remove("restaurant_info.txt");
	rename("temp.txt", "restaurant_info.txt");
}
