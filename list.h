#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct {
    size_t capacity;
    size_t size;
    double *data;
    int *next_index;
    int head;
    int *previous_index;
    int tail;
    int free;
} list_type;

// typedef struct {
//     double value;
//     int next_index;
//     int previous_index;
// } node_type;
//
// typedef struct {
//     // size_t capacity;
//     // size_t size;
//     // double *data;
//     // int *next_index;
//     // int head;
//     // int tail;
//     // int *previous_index;
//     node_type nodes[1000];
//     int free;
// } list_type;

void ConstructList(list_type *list);
void DestructList(list_type *list);
void FillDefault(int *index_array, int capacity);
// void InsertElement();
// void DeleteElement();

#endif
