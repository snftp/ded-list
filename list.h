#ifndef LIST_H
#define LIST_H

#include <stddef.h>

#define LIST_SIZE 10
#define END       (int)0xAB0000BA
#define FREE      (int)0xAB0000BA

typedef struct {
    double value;
    int next_index;
    int previous_index;
} node_type;

typedef struct {
    node_type nodes[LIST_SIZE];
    node_type free[LIST_SIZE];
} list_type;

void ConstructList(list_type *list);
void DestructList(list_type *list);
void InsertAtTheEnd(list_type *list, double value);
void InsertAtTheStart(list_type *list, double value);
void InsertElement(list_type *list, double value, int physical_index);
void DeleteElement(list_type *list, int physical_index);
int GetHead(const list_type *list);
int GetTail(const list_type *list);

#endif
