#include "list.h"
#include "render.h"
#include <stdio.h>
#include <stdlib.h>

// void DeleteElement(list_type *list, size_t index) {
// }

void InsertElement(list_type *list, double value, size_t index) {
    if (list->size == list->capacity) {
        list->capacity = (list->capacity - 1) * 2 + 1;
        list->data = (double*)realloc(list->data, list->capacity * sizeof(int));
        // TODO: Verifier list->size > list->capacity ? ptr != NULL?
        list->next_index = (int*)realloc(list->next_index, list->capacity * sizeof(int));
        list->previous_index = (int*)realloc(list->previous_index, list->capacity * sizeof(int));
    }

    list->data[list->free] = value;
    list->size++;

    if (index == 0) {
        list->head = list->free;
    }

    if (index == list->size - 1) { // NOTE: if user required to insert element on free's spot
        list->free += 1;
        list->tail = (int)index + 1;

        list->next_index[index + 1] = list->free;

        list->previous_index[list->free] = (int)index + 1;
        list->previous_index[index + 1] = (int)index;
    }

    else {
        int tmp_next_index = list->next_index[index];
        // int tmp_previous_index = list->previous_index[index];

        list->next_index[index] = list->free;
        list->previous_index[list->free] = (int)index;

        list->next_index[list->free] = tmp_next_index;
        list->previous_index[tmp_next_index] = list->free;

        list->free += 1;
        list->next_index[list->tail] = list->free;
        list->previous_index[list->free] = list->tail;

    }

    GraphicDump(list);
}

void FillDefault(int *index_array, size_t capacity) {
    for (size_t i = 1; i < capacity; i++) {
        index_array[i] = -1;
    }
}

void ConstructList(list_type *list) {
    list->capacity = 1001;
    list->size = 0;
    list->data = (double*)calloc(list->capacity, sizeof(double));

    // Verifier data != NULL
    list->next_index = (int*)calloc(list->capacity, sizeof(int));
    FillDefault(list->next_index, list->capacity);
    // Verifier next_index != NULL
    list->head = 0;

    list->previous_index = (int*)calloc(list->capacity, sizeof(int));
    FillDefault(list->previous_index, list->capacity);
    // Verifier previous_index != NULL
    list->tail = 0;

    list->free = 1; // NOTE: 1 needed for further work with data indexes (we won't enter zero-element)
    GraphicDump(list);
}

void DestructList(list_type *list) {
    list->capacity = 0;
    list->size = 0;
    free(list->data);
    free(list->next_index);
    list->head = 0;
    free(list->previous_index);
    list->tail = 0;
    list->free = 0;
    GraphicDump(list);
}

int main() {
    list_type list = {};

    printf("1\n");
    ConstructList(&list);

    printf("2\n");
    InsertElement(&list, 10.0, 0);
    printf("3\n");
    InsertElement(&list, 20.0, 1);
    printf("4\n");
    InsertElement(&list, 30.0, 2);
    printf("5\n");
    InsertElement(&list, 40.0, 1);
    printf("6\n");
    InsertElement(&list, 50.0, 2);
//
//     printf("7\n");
//     DeleteElement(&list, 2);

    printf("8\n");
    DestructList(&list);
    return 0;
}
