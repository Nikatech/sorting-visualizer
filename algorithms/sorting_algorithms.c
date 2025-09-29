#include "sorting_algorithms.h"

// 1. Bubble Sort
void bubble_sort(int *a, int N){
    int x = 0, y = N - 1; 
    int k = 1;  
    while ((x < y) && k > 0) {
        k = 0;
        for (int i = x; i < y; i++){
            if (a[i] > a[i+1]){
                int t = a[i];
                a[i] = a[i+1];
                a[i+1] = t;
                k = 1;      
            }
        }
        y--; 
        for (int i = y; i > x; i--){
            if (a[i-1] > a[i]){
                int t = a[i];
                a[i] = a[i-1];
                a[i-1] = t;
                k = 1;   
            }
        }
        x++;
        if(k == 0) break;
    }
}

// 2. Selection Sort
void selection_sort(int *a, int N) {
    for (int i = 0; i < N-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < N; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        int temp = a[i];
        a[i] = a[min_idx];
        a[min_idx] = temp;
    }
}

// 3. Insertion Sort
void insertion_sort(int *a, int N) {
    for (int i = 1; i < N; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}

// 4. Shaker Sort
void shaker_sort(int *a, int N) {
    int left = 0;
    int right = N - 1;
    int swapped = 1;
    
    while (left < right && swapped) {
        swapped = 0;
        
        // Проход слева направо
        for (int i = left; i < right; i++) {
            if (a[i] > a[i + 1]) {
                int temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
                swapped = 1;
            }
        }
        right--;
        
        // Проход справа налево
        for (int i = right; i > left; i--) {
            if (a[i - 1] > a[i]) {
                int temp = a[i];
                a[i] = a[i - 1];
                a[i - 1] = temp;
                swapped = 1;
            }
        }
        left++;
    }
}

// 5. Merge Sort
void merge(int *a, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    for (i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];
    
    i = 0;
    j = 0;
    k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void merge_sort_helper(int *a, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        merge_sort_helper(a, left, mid);
        merge_sort_helper(a, mid + 1, right);
        
        merge(a, left, mid, right);
    }
}

void merge_sort(int *a, int N) {
    merge_sort_helper(a, 0, N - 1);
}

// 6. Heap Sort
void heapify(int *a, int N, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < N && a[left] > a[largest])
        largest = left;
    
    if (right < N && a[right] > a[largest])
        largest = right;
    
    if (largest != i) {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        
        heapify(a, N, largest);
    }
}

void heap_sort(int *a, int N) {
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(a, N, i);
    
    for (int i = N - 1; i >= 0; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        
        heapify(a, i, 0);
    }
}