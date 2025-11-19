#ifndef LIST_H
#define LIST_H

#include <stddef.h>

#define LIST_SIZE 10

typedef struct {
    double value;
    int next_index;
    int previous_index;
} node_type;

typedef struct {
    node_type nodes[LIST_SIZE];
    int free;
} list_type;

void ConstructList(list_type *list);
void DestructList(list_type *list);
void InsertElement(list_type *list, double value, int physical_index);
int GetHead(const list_type *list);
int GetTail(const list_type *list);
// void DeleteElement();

#endif
