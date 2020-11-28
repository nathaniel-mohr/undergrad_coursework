#include "./vector.hpp"
#include <vector>
#include <iostream>

//We do not want to include either stmt. We wouldn't 
//be able to compare our vector template to the Standard 
//using namespace std;
//using std::vector;
using std::cout;
using std::endl;

int main (){
   vector<int> v;   //Our vector class
   std::vector<int> stdv; //Standard vector

   //Compare operation of our vector to std
   v.push_back(23);
   stdv.push_back(23);
   
   cout << "Our vector size: " << v.size() << endl;
   cout << "STL vector size: " << stdv.size() << endl;

   vector<int> v2 = v;
   cout << "\nSize of copied vector: " << v2.size() << endl;

   vector<int> v3;
   v3.push_back(50);
   v3.push_back(27);
   cout << "\nv3[0]: " << v3[0] << endl;
   cout << "v3[1]: " << v3[1] << endl;
   cout << "Size of vector before assignment: " << v3.size() << endl;
   v3 = v;
   cout << "Size after assignment: " << v3.size() << endl;

   try{
	   cout << "\nAccessing v3.at(0)" << endl;
	   cout << v3.at(0) << endl;
	   cout << "Accessing v3.at(3)" << endl;
	   cout << v3.at(3) << endl;
   }catch(std::out_of_range &e){
		cout << e.what() << endl;
   }

   return 0;
}

