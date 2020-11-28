#include <stdlib.h>
#include <exception>
#include <stdexcept>

template <class T>
class vector {
  	private:
      		T *v;
      		int s;
		int c;
	public:
      		vector(){
	     		s=0;
	     		v=NULL;
     	 	}		
	  
      		~vector(){
	     		delete [] v;
      		}
	 
		vector(vector<T> &other){
			s = other.s;
			if(s == 0){
				v = NULL;
			}else{
				v = new T[s];
				for(int i = 0; i < s; i++){
					v[i] = other.v[i];	
				}
			}
		}

		void operator=(vector<T> &other){
			s = other.s;
			if(v != NULL){
				delete[] v;
			}
			if(s == 0){
				v = NULL;
			}else{
				v = new T[s];
				for(int i = 0; i < s; i++){
					v[i] = other.v[i];
				}
			}
		}
	  
      		int size() {
	     		return s;
     		}

		int capacity(){
			return c;
		}
	  
      		void push_back(T ele) {
	     		T *temp;
	     		temp = new T[++s];
	     		for(int i=0; i<s-1; i++)
	        	temp[i]=v[i];

	     		delete [] v;
	     		v=temp;
	     		v[s-1]=ele;
      		}

		T operator[](int index){
			T* temp = v;
			for(int i = 0; i < index; i++){
				temp++;	
			}
			return *temp;
		}

		T at(int index){
			if(index < 0 || index >= s){
				throw std::out_of_range("out of my vector bounds");
			}else{
				v[index];
			}
		}
};
