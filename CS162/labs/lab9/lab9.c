#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_dimension(){
	int val;
	do{
		printf("Input the dimension: ");
		scanf("%d", &val);
	}while(val < 0 || val > 10);
	return val;
}

int** alloc_arr(int height, int width){
	int i;
	int** arr = (int**)(malloc(sizeof(int*) * width));
	for(i = 0; i < width; i++){
		arr[i] = (int*)(malloc(sizeof(int) * height));
	}
	return arr;
}

void pop_arr(int** arr, int height, int width){
	int i, j;
	for(i = 0; i < width; i++){
		for(j = 0; j < height; j++){
			arr[i][j] = rand() % 50 + 1;
		}
	}
}

void print_arr(int** arr, int height, int width){
	int i, j;
	for(i = 0; i < width; i++){
		for(j = 0; j < height; j++){
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

int get_val(){
	int val;
	do{
		printf("Number to add to each value: ");
		scanf("%d", &val);
	}while(val < 0);
}

void adjust_arr(int** arr, int height, int width, int val){
	int i, j;
	for(i = 0; i < width; i++){
		for(j = 0; j < height; j++){
			arr[i][j] += val;;
		}
	}
}

void delete_arr(int** arr, int height, int width){
	int i;
	for(i = 0; i < width; i++){
		free(arr[i]);
	}
	free(arr);
}


int main(){
	srand(time(NULL));
	int height = 0, width = 0, val = 0;

	printf("HEIGHT\n");
	height = get_dimension();

	printf("WIDTH\n");
	width = get_dimension();

	int** arr = alloc_arr(height, width);
	pop_arr(arr, height, width);
	print_arr(arr, height, width);

	val = get_val();

	adjust_arr(arr, height, width, val);
	print_arr(arr, height, width);

	delete_arr(arr, height, width);
}
