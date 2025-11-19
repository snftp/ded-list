#include "list.h"
#include "render.h"
#include <stdio.h>

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
    InsertElement(&list, 40.0, 3);
    printf("6\n");
    InsertElement(&list, 50.0, 2);
    printf("7\n");
    InsertElement(&list, 20.0, 3);
    printf("8\n");
    InsertElement(&list, 40.0, 4);
    // printf("7\n");
    // DeleteElement(&list, 2);

    printf("9\n");
    DestructList(&list);
    return 0;
}
