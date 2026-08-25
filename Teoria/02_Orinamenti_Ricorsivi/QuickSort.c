#include <stdio.h>
#include <stdlib.h>


typedef enum {false, true} bool;

void QuickSort(int* arr, int len);
void quickSort(int* arr, int left, int right);
int partition(int* arr, int left, int right);
void swap(int* arr, int i, int j);
int* readVector(int* len);
void printVector(int* arr, int len);

int main(){
    int len = 0;
    int *arr = readVector(&len);

    printVector(arr, len);

    QuickSort(arr, len);

    printVector(arr, len);

    free(arr);
    return 0;
}

void printVector(int* arr, int len){
    for(int i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* readVector(int* len){
    int size = 2;
    int* arr = (int*)malloc(sizeof(int)*size);
    int holder = 1;
    while(true){
        printf("Insert number: \n");
        scanf(" %d", &holder);

        if(holder < 0)
            break;

        if(*len == size){
            size *= 2;
            arr = (int*)realloc(arr, size*sizeof(int));
        }
        arr[(*len)++] = holder;
        printf("Added %d , len: %d size: %d\n", arr[(*len)-1], *len, size);
    }

    return arr;
}

void QuickSort(int* arr, int len){
    quickSort(arr, 0, len - 1);
}

void quickSort(int* arr, int left, int right){
    if(left >= right){
        return;
    }

    int pivot = partition(arr, left, right);
    quickSort(arr, left, pivot - 1);
    quickSort(arr, pivot + 1, right);
    return;
}

void swap(int* arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return;
}

int partition(int* arr, int left, int right){
    int i = left - 1, j = right; // left -1 perché procedo per pre-incremento/pre-deceremento

    int pivot = arr[right]; // prendo l'elemento esterno come pivot, va bene uno qualsiasi
    while(true){
        while(arr[++i] < pivot); 
        while(arr[--j] > pivot);
        if(i >= j)
          break;
        swap(arr, i, j);
    }
    swap(arr, left, j);
    return i;
}