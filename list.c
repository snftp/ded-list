#include "list.h"
#include "render.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int GetHead(const list_type *list) {
    return list->nodes[0].next_index;
}

int GetTail(const list_type *list) {
    return list->nodes[0].previous_index;
}

void FillList(list_type *list, double value) { // TODO: rename
    InsertElement(list, value, GetTail(list));
}

void DeleteElement(list_type *list, int physical_index) {
    // list->nodes[physical_index] = { .next_index = list->free };
    list->free = physical_index;

    list->nodes[list->nodes[physical_index].next_index].previous_index = list->nodes[physical_index].previous_index;
    list->nodes[list->nodes[physical_index].previous_index].next_index = list->nodes[physical_index].next_index;

    list->nodes[physical_index] = {};

    GraphicDump(list);
}

void InsertElement(list_type *list, double value, int physical_index) {
    int new_physical_index = list->free;
    list->free = (list->nodes[list->free]).next_index;
    (list->nodes[(list->nodes[physical_index]).next_index]).previous_index = new_physical_index;

    list->nodes[new_physical_index] = {
        .value = value,
        .next_index = (list->nodes[physical_index]).next_index,
        .previous_index = physical_index
    };

    (list->nodes[physical_index]).next_index = new_physical_index;

    GraphicDump(list);
}

void ConstructList(list_type *list) {
    list->nodes[0] = {};

    for (int i = 1; i < LIST_SIZE - 1; i++) {
        list->nodes[i] = { .value = 0.0, .next_index = i + 1, .previous_index = 0 };
    }

    list->nodes[LIST_SIZE - 1] = { .previous_index = LIST_SIZE - 2 };

    list->free = 1;

    GraphicDump(list);
}

void DestructList(list_type *list) {
    for (int i = 0; i < LIST_SIZE; i++) {
        list->nodes[i] = { .value = NAN, .next_index = -1, .previous_index = -1};
    }

    list->free = -1;
    GraphicDump(list);
}
