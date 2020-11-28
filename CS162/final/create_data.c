#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int i, num = 10000;
	FILE *f = fopen("data.txt", "w"); 
	srand(time(NULL));
	for(i = 0; i < num; i++){
		fprintf(f, "%d\n", rand() % 100);
	}
	fclose(f);
	return 0;
}
