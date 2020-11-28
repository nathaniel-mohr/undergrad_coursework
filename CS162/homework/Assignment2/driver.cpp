#include "pizza.h"
#include "menu.h"
#include "restaurant.h"
#include "structs.h"

void rest_menu(Restaurant r);
void log_in(Restaurant r);
void emp_menu(Restaurant r);
void emp_switch(int ans, Restaurant r);
void cust_menu(Restaurant r);
void cust_switch(int ans, Restaurant r);

int main(){
	Restaurant restaurant;
	restaurant.load_data();
	rest_menu(restaurant);
	return 0;
}

void rest_menu(Restaurant r){
	string ans;
	do{
		cout << "Welcome to " << r.get_name() << endl;
		cout << "Are you an employee (E) or a customer (C) or would you like to quit (Q)?" << endl;
		getline(cin, ans);
	}while(ans != "E" && ans != "Q" && ans != "C");
	if(ans == "E"){
		log_in(r);
		emp_menu(r);
	}else if(ans == "C"){
		cust_menu(r);
	}
}

void log_in(Restaurant r){
	string username, password;
	cout << "Please enter credentials" << endl;
	do{	
		cout << "ID Number: ";
		getline(cin, username);
		cout << "Password: ";
		getline(cin, password);
	}while(!r.login(username,password));
}

void emp_menu(Restaurant r){
	int ans = 0;
	cout << " 1. Change Hours" << endl;
	cout << " 2. View Orders" << endl;
	cout << " 3. Remove Order" << endl;
	cout << " 4. Add Item to Menu" << endl;
	cout << " 5. Remove Item from Menu" << endl;
	cout << " 6. View Menu" << endl;
	cout << " 7. View Hours" << endl;
	cout << " 8. View Address" << endl;
	cout << " 9. View Phone" << endl;
	cout << "10. Log Out" << endl;
	do{
		cout << "Selection:  ";
		cin >> ans;
		cin.ignore();
		cin.clear();
	}while(ans < 1 || ans > 10);
	emp_switch(ans, r);
}

void emp_switch(int ans, Restaurant r){
	switch(ans){
		case 1: r.change_hours();
			break;	
		case 2: r.view_orders();
			break;
		case 3: r.remove_orders();
			break;
		case 4: r.add_to_menu();
			break;
		case 5: r.remove_from_menu();
			break;
		case 6: r.view_menu();
			break;
		case 7: r.view_hours();
			break;
		case 8: r.view_address();
			break;
		case 9: r.view_phone();
			break;
		case 10: rest_menu(r);
			break;
	}
	if(ans != 10){
		emp_menu(r);
	}
}

void cust_menu(Restaurant r){
	int ans;
	cout << " 1. View Menu" << endl;
	cout << " 2. Search by Cost" << endl;
	cout << " 3. Search by Ingredients" << endl;
	cout << " 4. Place Order" << endl; 
	cout << " 5. View Hours" << endl;
	cout << " 6. View Address" << endl;
	cout << " 7. View Phone" << endl;
	cout << " 8. Log Out" << endl;
	do{
		cout << "Selection:  ";
		cin >> ans;
		cin.ignore();
		cin.clear();
	}while(ans < 1 || ans > 8);
	cust_switch(ans, r);
}

void cust_switch(int ans, Restaurant r){
	switch(ans){
		case 1:	r.view_menu();
			break;
		case 2: r.search_menu_by_price();
			break;
		case 3: r.search_by_ingredients();
			break;
		case 4: r.place_order(r.get_menu().get_pizzas());
			break;
		case 5: r.view_hours();
			break;
		case 6: r.view_address();
			break;
		case 7: r.view_phone();
			break;
		case 8: rest_menu(r);
			break;
	}
	if(ans != 8){
		cust_menu(r);
	}
}
