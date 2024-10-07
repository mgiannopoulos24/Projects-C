#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef struct {
    int *array;
    int left;
    int right;
} SortArgs;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void *merge_sort(void *args) {
    SortArgs *data = (SortArgs *)args;
    int left = data->left;
    int right = data->right;
    int *arr = data->array;

    if (left < right) {
        int mid = left + (right - left) / 2;

        SortArgs left_args = {arr, left, mid};
        SortArgs right_args = {arr, mid + 1, right};

        pthread_t left_thread, right_thread;
        pthread_create(&left_thread, NULL, merge_sort, &left_args);
        pthread_create(&right_thread, NULL, merge_sort, &right_args);

        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);

        merge(arr, left, mid, right);
    }
    return NULL;
}

int main() {
    int array[MAX_SIZE];
    int size = 20;  // Example size

    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }

    printf("Unsorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    SortArgs args = {array, 0, size - 1};
    pthread_t sort_thread;
    pthread_create(&sort_thread, NULL, merge_sort, &args);
    pthread_join(sort_thread, NULL);

    printf("Sorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
