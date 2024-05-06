#include <stdlib.h>
#include <stdio.h>

void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}



int main() {
    printf("hello world");
    int arr[5] = {1,2,3,4,5};
    swap(&arr[2], &arr[0]);
    return 0;
}