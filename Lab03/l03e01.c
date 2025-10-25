#include <stdio.h>
#include <stdlib.h>

#define LEN 7

int majority(int* a, int N );

int main(){
	int vec[LEN] = {3, 3, 9, 4 ,2, 5, 3};

    int maj = majority(vec, LEN);

    if(maj > 0)
    	printf("Majority number is: %d\n", maj);
    else
    	printf("No majority number found\n");

	return 0;

        
}

int majority(int* a, int N ){ //solo divide et impera
	if(N == 1)
		return *a;

	int middle = N/2;
	int left = majority(a, N-middle);
	int right = majority(a+middle, N-middle);

	if (left == right)
		return left;
	if (left == -1)
		if (right != -1)
			return right;
	if (right == -1)
		if (left != -1)
			return left;
	return -1;

}