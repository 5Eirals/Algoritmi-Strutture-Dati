#include <stdio.h>

void Hanoi(int n, int src, int dest);

int main(){
    int disks = 3;
    Hanoi(disks, 0, 2);
    return 0;
}

void Hanoi(int n, int src, int dest){
    int aux = 3 - (src + dest);
    if(n == 1){
        printf("n %d src %d -> dest %d\n", n, src, dest);
        return;
    }

    Hanoi(n - 1, src, aux);
    printf("n %d src %d -> dest %d\n", n, src, dest);
    Hanoi(n - 1, aux, dest);
}
