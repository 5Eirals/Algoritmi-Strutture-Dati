#include <stdio.h>

int bynaryMax(int v[], int l,  int r);

int main(){
    int v[] = {60, 3, 40, 6}, n = 4;

    printf("Max: %d\n", bynaryMax(v, 0, n-1));
    return 0;
}

int bynaryMax(int v[], int l, int r){
    if(l == r)
      return v[l];

    int mid = (l + r) / 2;
    int left_max = bynaryMax(v, l, mid);
    int right_max = bynaryMax(v, mid + 1, r);

    if(left_max > right_max)
      return left_max;
    return right_max;
}
