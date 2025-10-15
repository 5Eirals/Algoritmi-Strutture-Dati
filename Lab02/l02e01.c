#include <stdio.h>

int gcd(int a, int b);

int main(){
    int a, b;
    printf("Insert the numbers: ");
    scanf("%d %d", &a, &b);

    if(b > a){
        b = a + b;
        a = b - a;
        b -= a;
    }

    printf("gcd: %d", gcd(a,b));
    return 0;
}

int gcd(int a, int b){
    if()
      return;

    gcd();
}
