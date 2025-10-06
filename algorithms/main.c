#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "sorting_algorithms.h"

void ensure_data_dir() {
    struct stat st = {0};
    if (stat("data", &st) == -1) {
        mkdir("data", 0777);
    }
}

// Глобальные переменные для логирования
static int frame_count = 0;
FILE *current_json_file = NULL;

// Функция для сохранения состояния массива
void save_array_state(int arr[], int size) {
    if (frame_count > 0) {
        fprintf(current_json_file, ",\n");
    }
    
    fprintf(current_json_file, "  [");
    for (int i = 0; i < size; i++) {
        fprintf(current_json_file, "%d", arr[i]);
        if (i < size - 1) fprintf(current_json_file, ", ");
    }
    fprintf(current_json_file, "]");
    
    frame_count++;
}

// Функция для копирования массива
void copy_array(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

// Модифицированные функции сортировки с логированием

void bubble_sort_logging(int *original, int N) {
    int *arr = malloc(N * sizeof(int));
    copy_array(original, arr, N);
    
    frame_count = 0;
    fprintf(current_json_file, "[\n");
    save_array_state(arr, N);
    
    int x = 0, y = N - 1; 
    int k = 1;  
    
    while ((x < y) && k > 0) {
        k = 0;
        for (int i = x; i < y; i++) {
            if (arr[i] > arr[i+1]) {
                int t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
                k = 1;
                save_array_state(arr, N);
            }
        }
        y--;
        for (int i = y; i > x; i--) {
            if (arr[i-1] > arr[i]) {
                int t = arr[i];
                arr[i] = arr[i-1];
                arr[i-1] = t;
                k = 1;
                save_array_state(arr, N);
            }
        }
        x++;
        if(k == 0) break;
    }
    
    fprintf(current_json_file, "\n]\n");
    free(arr);
}

void selection_sort_logging(int *original, int N) {
    int *arr = malloc(N * sizeof(int));
    copy_array(original, arr, N);
    
    frame_count = 0;
    fprintf(current_json_file, "[\n");
    save_array_state(arr, N);
    
    for (int i = 0; i < N-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < N; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            save_array_state(arr, N);
        }
    }
    
    fprintf(current_json_file, "\n]\n");
    free(arr);
}

void insertion_sort_logging(int *original, int N) {
    int *arr = malloc(N * sizeof(int));
    copy_array(original, arr, N);
    
    frame_count = 0;
    fprintf(current_json_file, "[\n");
    save_array_state(arr, N);
    
    for (int i = 1; i < N; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            save_array_state(arr, N);
        }
        arr[j + 1] = key;
        save_array_state(arr, N);
    }
    
    fprintf(current_json_file, "\n]\n");
    free(arr);
}

void shaker_sort_logging(int *original, int N) {
    int *arr = malloc(N * sizeof(int));
    copy_array(original, arr, N);
    
    frame_count = 0;
    fprintf(current_json_file, "[\n");
    save_array_state(arr, N);
    
    int left = 0;
    int right = N - 1;
    int swapped = 1;
    
    while (left < right && swapped) {
        swapped = 0;
        
        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
                save_array_state(arr, N);
            }
        }
        right--;
        
        for (int i = right; i > left; i--) {
            if (arr[i - 1] > arr[i]) {
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = 1;
                save_array_state(arr, N);
            }
        }
        left++;
    }
    
    fprintf(current_json_file, "\n]\n");
    free(arr);
}

void merge_sort_logging(int *original, int N) {
    int *arr = malloc(N * sizeof(int));
    copy_array(original, arr, N);
    
    frame_count = 0;
    fprintf(current_json_file, "[\n");
    save_array_state(arr, N);
    
    // Просто вызываем стандартную merge_sort
    merge_sort(arr, N);
    save_array_state(arr, N);
    
    fprintf(current_json_file, "\n]\n");
    free(arr);
}

void heap_sort_logging(int *original, int N) {
    int *arr = malloc(N * sizeof(int));
    copy_array(original, arr, N);
    
    frame_count = 0;
    fprintf(current_json_file, "[\n");
    save_array_state(arr, N);
    
    // Просто вызываем стандартную heap_sort
    heap_sort(arr, N);
    save_array_state(arr, N);
    
    fprintf(current_json_file, "\n]\n");
    free(arr);
}

int main() {
	ensure_data_dir();

    int size = 45;
    int *original = malloc(size * sizeof(int));

    srand(time(NULL));
    printf("Создаем массив из %d элементов:\n", size);
    for (int i = 0; i < size; i++) {
        original[i] = rand() % 1000 + 1;

    printf("...\n\n");
       char *filenames[] = {
        "data/bubble_sort.json",
        "data/selection_sort.json", 
        "data/insertion_sort.json",
        "data/shaker_sort.json",
        "data/merge_sort.json",
        "data/heap_sort.json"
    };


    for (int i = 0; i < 6; i++) {
        current_json_file = fopen(filenames[i], "w");
        if (current_json_file == NULL) {
            printf("Ошибка создания файла: %s\n", filenames[i]);
            continue;
        }
        
        printf("Генерируем %s...\n", filenames[i]);
        
        switch(i) {
            case 0: bubble_sort_logging(original, size); break;
            case 1: selection_sort_logging(original, size); break;
            case 2: insertion_sort_logging(original, size); break;
            case 3: shaker_sort_logging(original, size); break;
            case 4: merge_sort_logging(original, size); break;
            case 5: heap_sort_logging(original, size); break;
        }
        
        fclose(current_json_file);
        printf("✓ Файл создан: %s\n", filenames[i]);
    }
    
    free(original);
    printf("\nВсе JSON файлы созданы!\n");
    return 0;
}
