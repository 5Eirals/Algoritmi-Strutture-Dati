#include <stdio.h>

void divideVector(int v[], int l, int r);

int main() {
    int v[] = {1, 2 ,3, 4, 5, 6, 7, 8}, n = 8;

    divideVector(&v,0,n-1);

    return 0;
}

void divideVector(int v[], int l, int r) {
    if (l >= r) return;

    int mid = (l + r) / 2;
    printf("left division:  ");
    for (int i = l; i <= mid; i++)
        printf("%d ", v[i]);
    printf("\n");
    printf("________________\n");
    divideVector(v, l, mid);

    printf("right division: ");
    for (int i = mid+1; i <= r; i++)
      printf("%d ", v[i]);
    printf("\n");
    printf("________________\n");

    divideVector(v, mid+1, r);
}