#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "sorting_algorithms.h"

void ensure_data_dir() {
    struct stat st = {0};
    if (stat("data", &st) == -1) {
        mkdir("data", 0755);
    }
}

static int frame_count = 0;
FILE *current_json_file = NULL;

void save_state(int arr[], int size, int highlight1, int highlight2, const char* description) {
    if (frame_count > 0) {
        fprintf(current_json_file, ",\n");
    }
    
    fprintf(current_json_file, "  {\n");
    fprintf(current_json_file, "    \"array\": [");
    for (int i = 0; i < size; i++) {
        fprintf(current_json_file, "%d", arr[i]);
        if (i < size - 1) fprintf(current_json_file, ", ");
    }
    fprintf(current_json_file, "],\n");
    fprintf(current_json_file, "    \"highlight\": [%d, %d],\n", highlight1, highlight2);
    fprintf(current_json_file, "    \"description\": \"%s\"\n", description);
    fprintf(current_json_file, "  }");
    
    frame_count++;
}

void copy_array(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

void bubble_sort_with_logging(int *original, int N) {
    int *arr = malloc(N * sizeof(int));
    copy_array(original, arr, N);
    
    frame_count = 0;
    fprintf(current_json_file, "[\n");
    save_state(arr, N, -1, -1, "Начало Bubble Sort");
    
    int x = 0, y = N - 1; 
    int k = 1;  
    
    while ((x < y) && k > 0) {
        k = 0;
        
        for (int i = x; i < y; i++) {
            save_state(arr, N, i, i+1, "Сравнение элементов");
            
            if (arr[i] > arr[i+1]) {
                int t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
                k = 1;
                
                save_state(arr, N, i, i+1, "Обмен элементов");
            }
        }
        y--;
        
        for (int i = y; i > x; i--) {
            save_state(arr, N, i-1, i, "Обратный проход: сравнение");
            
            if (arr[i-1] > arr[i]) {
                int t = arr[i];
                arr[i] = arr[i-1];
                arr[i-1] = t;
                k = 1;
                
                save_state(arr, N, i-1, i, "Обратный проход: обмен");
            }
        }
        x++;
        if(k == 0) break;
    }
    
    save_state(arr, N, -1, -1, "Bubble Sort завершен");
    fprintf(current_json_file, "\n]\n");
    free(arr);
}

void selection_sort_with_logging(int *original, int N) {
    int *arr = malloc(N * sizeof(int));
    copy_array(original, arr, N);
    
    frame_count = 0;
    fprintf(current_json_file, "[\n");
    save_state(arr, N, -1, -1, "Начало Selection Sort");
    
    for (int i = 0; i < N-1; i++) {
        int min_idx = i;
        
        for (int j = i+1; j < N; j++) {
            save_state(arr, N, min_idx, j, "Поиск минимального элемента");
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
                save_state(arr, N, min_idx, j, "Найден новый минимальный элемент");
            }
        }
        
        if (min_idx != i) {
            save_state(arr, N, i, min_idx, "Обмен текущего элемента с минимальным");
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            save_state(arr, N, i, min_idx, "Элементы обменяны");
        }
    }
    
    save_state(arr, N, -1, -1, "Selection Sort завершен");
    fprintf(current_json_file, "\n]\n");
    free(arr);
}

void insertion_sort_with_logging(int *original, int N) {
    int *arr = malloc(N * sizeof(int));
    copy_array(original, arr, N);
    
    frame_count = 0;
    fprintf(current_json_file, "[\n");
    save_state(arr, N, -1, -1, "Начало Insertion Sort");
    
    for (int i = 1; i < N; i++) {
        int key = arr[i];
        int j = i - 1;
        
        save_state(arr, N, i, -1, "Взяли элемент для вставки");
        
        while (j >= 0 && arr[j] > key) {
            save_state(arr, N, j, j+1, "Сдвигаем элемент вправо");
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        
        arr[j + 1] = key;
        save_state(arr, N, j+1, -1, "Вставили элемент на правильную позицию");
    }
    
    save_state(arr, N, -1, -1, "Insertion Sort завершен");
    fprintf(current_json_file, "\n]\n");
    free(arr);
}

void shaker_sort_with_logging(int *original, int N) {
    int *arr = malloc(N * sizeof(int));
    copy_array(original, arr, N);
    
    frame_count = 0;
    fprintf(current_json_file, "[\n");
    save_state(arr, N, -1, -1, "Начало Shaker Sort");
    
    int left = 0;
    int right = N - 1;
    int swapped = 1;
    
    while (left < right && swapped) {
        swapped = 0;
        
        for (int i = left; i < right; i++) {
            save_state(arr, N, i, i+1, "Проход слева направо: сравнение");
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
                save_state(arr, N, i, i+1, "Проход слева направо: обмен");
            }
        }
        right--;
        
        for (int i = right; i > left; i--) {
            save_state(arr, N, i-1, i, "Проход справа налево: сравнение");
            if (arr[i - 1] > arr[i]) {
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = 1;
                save_state(arr, N, i-1, i, "Проход справа налево: обмен");
            }
        }
        left++;
    }
    
    save_state(arr, N, -1, -1, "Shaker Sort завершен");
    fprintf(current_json_file, "\n]\n");
    free(arr);
}

void merge_sort_with_logging(int *original, int N) {
    int *arr = malloc(N * sizeof(int));
    copy_array(original, arr, N);
    
    frame_count = 0;
    fprintf(current_json_file, "[\n");
    save_state(arr, N, -1, -1, "Начало Merge Sort");
    
    merge_sort(arr, N);
    
    save_state(arr, N, -1, -1, "Merge Sort завершен");
    fprintf(current_json_file, "\n]\n");
    free(arr);
}

void heap_sort_with_logging(int *original, int N) {
    int *arr = malloc(N * sizeof(int));
    copy_array(original, arr, N);
    
    frame_count = 0;
    fprintf(current_json_file, "[\n");
    save_state(arr, N, -1, -1, "Начало Heap Sort");
    
    heap_sort(arr, N);
    
    save_state(arr, N, -1, -1, "Heap Sort завершен");
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
    }
    
    printf("Первые 10 элементов: ");
    for (int i = 0; i < 10 && i < size; i++) {
        printf("%d ", original[i]);
    }
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
    		case 0: bubble_sort_with_logging(original, size); break;
    		case 1: selection_sort_with_logging(original, size); break;
    		case 2: insertion_sort_with_logging(original, size); break;
    		case 3: shaker_sort_with_logging(original, size); break;
    		case 4: merge_sort_with_logging(original, size); break;
    		case 5: heap_sort_with_logging(original, size); break;
	}
        
        fclose(current_json_file);
        printf("✓ Файл создан: %s\n", filenames[i]);
    }
    
    free(original);
    printf("\nВсе JSON файлы созданы!\n");
    return 0;
}