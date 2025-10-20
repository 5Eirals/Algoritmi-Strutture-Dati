#include <stdio.h>

int gcd(int a, int b);

int main(){
    int a, b;
    printf("Insert the numbers: ");
    scanf("%d %d", &a, &b);

    printf("gcd: %d", gcd(a,b));
    return 0;
}

int gcd(int a, int b){

    if(b > a){
        b = a + b;
        a = b - a;
        b -= a;
    }

    if(a%b == 0)
      return b;

    if(a%2 == 0)
    	if(b%2 == 0)
        	return 2*gcd(a/2, b/2);
    	else
        	return gcd(a/2, b);
    else
    	if(b%2 == 0)
        	return gcd(a, b/2);
    	else
        	return gcd((a-b)/2, b);
}
