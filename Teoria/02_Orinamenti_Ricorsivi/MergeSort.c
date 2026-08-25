#include <stdio.h>
#include <stdlib.h>

// ATTENZIONE ALLA GESTIONE DEGLI INDICI, PARTICOLARMENTE AL CALCOLO DI mid (VA SOMMATO A LEFT)


typedef enum {false, true} bool;

void MergeSort(int arr[], int len);
void mergeSort(int arr[], int buffer[], int left, int right);
void merge(int arr[], int buffer[], int left, int mid, int right);
int* readVector(int* len);
void printVector(int* arr, int len);

int main(){
    int len = 0;
    int *arr = readVector(&len);

    printVector(arr, len);

    MergeSort(arr, len);

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

void MergeSort(int arr[], int len){
    int* buffer = (int*)malloc(sizeof(int)*len);
    mergeSort(arr, buffer, 0, len - 1);
}

void mergeSort(int arr[], int buffer[], int left, int right){
    if(left >= right)
      return;
    int mid = (right - left) / 2;
    mergeSort(arr, buffer, left, left + mid);
    mergeSort(arr, buffer, left + mid + 1, right);
    merge(arr, buffer, left, left + mid, right);
}

void merge(int arr[], int buffer[], int left, int mid, int right){
    int i = left, j = mid + 1;
    for(int k = left; k <= right; k++){
        if(i > mid){
            buffer[k] = arr[j++];
            continue;
        }

        if(j > right){
            buffer[k] = arr[i++];
            continue;
        }

        if(arr[i] > arr[j])
            buffer[k] = arr[j++];
        else
            buffer[k] = arr[i++];

    }

    for(int k = left; k <= right; k++)
      arr[k] = buffer[k];
}