#include <stdio.h>

int countNulls(int* arr, int arrSize){
    int count = 0;
    for(int i = 0; i < arrSize; i++){
        if(arr[i] == 0)
            count++;
    }
    return count;
}

int main(){
    int arr[] = {1, 2, 3, 0, 3, 6, 0, 0, 0, -4, 0};
    int nullsCount = countNulls(arr, sizeof(arr) / sizeof(arr[0]));
    printf("%d", nullsCount);
    return 0;
}
