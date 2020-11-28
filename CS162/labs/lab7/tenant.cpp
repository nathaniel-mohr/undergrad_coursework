#include "tenant.h"

int Tenant::get_max_budget() const{return max_budget;}
int Tenant::get_agreeability() const{return agreeability;}
string Tenant::get_name() const{return name;}

void Tenant::set_name(string n){name = n;}
void Tenant::set_max_budget(int b){max_budget = b;}
void Tenant::set_agreeability(int a){agreeability = a;}

void Tenant::print_tenant(){
	cout << "Name: " << name << endl;
	cout << "Max Budget: " << max_budget << endl;
	cout << "Agreeability: " << agreeability << endl;
}

void Tenant::vacate(){
	name = "Vacant";
	max_budget = 0;
	agreeability = 0;
}

Tenant::Tenant(){
	agreeability = rand() % 5 + 1;
}
