#include <stdio.h>

int BinarySearch(int arr[], int l, int r, int target);

int main(){
    int v[] = {1, 7, 12, 21, 33, 48, 56, 94, 101, 125, 245, 889};
    int n = 12;
    int target = 889;

    printf("search %d\n", BinarySearch(v, 0, n - 1, target));
    return 0;
}

int BinarySearch(int arr[], int l, int r, int target){
    if(l > r){
        return -1;
    }
    int mid = (l + r) / 2;
    if(arr[mid] == target)
        return mid;
    if(arr[mid] > target)
      return BinarySearch(arr, l, mid - 1, target);
    return BinarySearch(arr, mid + 1, r, target);
}
