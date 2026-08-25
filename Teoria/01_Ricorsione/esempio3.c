#include <stdio.h>

int gcdEuclid(int a, int b);
int gcdDijkstra(int a, int b);

int main(){
    int a = 45451845, b = 753989;
    printf("gcd: %d\n", gcdEuclid(a, b));
    printf("gcd: %d\n", gcdDijkstra(a, b));
    return 0;
}

int gcdEuclid(int a, int b){
    if (a == b)
      return a;
   if(a > b)
       return gcdEuclid(a - b, b);
   return gcdEuclid(a, b - a);
}

int gcdDijkstra(int a, int b){
    if(a < b){
        int temp = a;
        a = b;
        b = temp;
    }

    if(b == 0)
        return a;
    return gcdDijkstra(b, a % b);
}
