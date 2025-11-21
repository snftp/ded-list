#include "list.h"
#include "render.h"
#include <stdio.h>

int main() {
    list_type list = {};

    printf("1\n");
    ConstructList(&list);

    printf("2\n");
    InsertAtTheEnd(&list, 10.0);

    printf("3\n");
    InsertAtTheEnd(&list, 20.0);

    printf("4\n");
    InsertAtTheEnd(&list, 30.0);

    printf("5\n");
    DeleteElement(&list, 2);

    printf("6\n");
    DeleteElement(&list, 1);

    printf("7\n");
    InsertAtTheEnd(&list, 20.0);

    printf("8\n");
    DestructList(&list);
    return 0;
}
