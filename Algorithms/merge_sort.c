#include <stdio.h>
#include <stdlib.h>

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int temp_left[n1];
    int temp_right[n2];

    for (int i = 0; i < n1; ++i) {
        temp_left[i] = arr[left + i];
    }
    for (int i = 0; i < n2; ++i) {
        temp_right[i] = arr[mid+1+i];
    }

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (temp_left[i] <= temp_right[j]) {
            arr[k] = temp_left[i];
            i++;
        } else {
            arr[k] = temp_right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = temp_left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = temp_right[j];
        j++;
        k++;
    }
}

int main() {
    int arr[] = {1, 12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    printf("Given array is \n");
    for(int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    merge_sort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    for(int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}

