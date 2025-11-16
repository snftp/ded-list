#include "render.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void PrintfDebugging() {
    int symbol = 0;
    printf("Enter SPACE to continue:");
    do {
        symbol = getchar();
    } while (symbol != ' ');
}

void GraphicDump(const list_type *list) {
    static size_t call_count = 1;

    FILE *tmp_dot = fopen("tmp.dot", "w");


    fputs("digraph G{\n\trankdir=LR;\n", tmp_dot);

    if (list->size == 0) {
        fputs("\tnode [shape=ellipse, style=\"filled\", fillcolor=\"white\", fontsize=12];\n", tmp_dot);
        fputs("\tELEMENT_HEAD[label=\"HEAD\"]\n", tmp_dot);
        fputs("\tELEMENT_TAIL[label=\"TAIL\"]\n", tmp_dot);
        fputs("\tELEMENT_FREE[label=\"FREE\"]\n", tmp_dot);

        fputc('}', tmp_dot);

        char cmd[512];
        sprintf(cmd, "/opt/homebrew/bin/dot -Tsvg \"tmp.dot\" -o \"graphs/output_%zu_EMPTY_LIST.svg\" > \"graphs/dot.log\" 2>&1", call_count);
        fclose(tmp_dot);
        system(cmd);
        call_count++;

        PrintfDebugging();
        return ;
    }

    fputs("\tgraph [splines=ortho];\n", tmp_dot);
    fputs("\tnode[color=\"pink\",fontsize=14];\n", tmp_dot);
    fputs("\tedge[color=\"red\",fontcolor=\"black\",fontsize=12];\n", tmp_dot);
    fputs("\tnodesep=0.4;\n", tmp_dot);

    for (size_t i = 0; i <= list->size; i++) {
        // printf("1\n");
        fprintf(tmp_dot, "\tELEMENT%zu[group=gELEMENT%zu, shape=\"Mrecord\",style=\"filled\",fillcolor=\"pink\", label=\" data=%lg | next=%d | prev=%d\"];\n", i, i, list->data[i], list->next_index[i], list->previous_index[i]);
        // printf("1\n\n");
    }
    fprintf(tmp_dot, "\tELEMENT%d[group=gELEMENT%d, shape=\"Mrecord\",style=\"filled\",fillcolor=\"white\", label=\" next=%d | prev=%d\"];\n", list->free, list->free, list->next_index[list->free], list->previous_index[list->free]);

    fputs("\tedge [constraint=true];\n", tmp_dot);
    fputs("\tELEMENT0", tmp_dot);
    for (size_t i = 1; i <= list->size; i++) {
        // printf("2\n");
        fprintf(tmp_dot, " -> ELEMENT%zu", i);
        // printf("2\n\n");
    }
    if (list->size < (size_t)list->free) {
        fprintf(tmp_dot, " -> ELEMENT%d", list->free);
    }
    fputs(" [style=invis, weight=10000];\n", tmp_dot);

    for (size_t i = 0; i <= list->size; i++) {
        // printf("3\n");
        fprintf(tmp_dot, "\tELEMENT%zu -> ELEMENT%d [constraint=false, color=\"pink\", fontcolor=\"black\", fontsize=12];\n", i, list->next_index[i]);
        fprintf(tmp_dot, "\tELEMENT%zu -> ELEMENT%d [constraint=false, color=\"red\", fontcolor=\"black\", fontsize=12];\n", i, list->previous_index[i]);
        // printf("3\n\n");
    }

    fputs("\tnode [shape=ellipse, style=\"filled\", fillcolor=\"white\", fontsize=12];\n", tmp_dot);

    fprintf(tmp_dot, "\tELEMENT_HEAD[group=gELEMENT%d, label=\"HEAD=%d\"]\n", list->head, list->head);
    fprintf(tmp_dot, "\tELEMENT_TAIL[group=gELEMENT%d, label=\"TAIL=%d\"]\n", list->tail, list->tail);
    fprintf(tmp_dot, "\tELEMENT_FREE[group=gELEMENT%d, label=\"FREE=%d\"]\n", list->free, list->free);

    fputs("\tedge [constraint=false, color=\"pink\"]\n", tmp_dot);
    fprintf(tmp_dot, "\tELEMENT_HEAD -> ELEMENT%d [tailport=e, headport=s];\n", list->head);
    fprintf(tmp_dot, "\tELEMENT_TAIL -> ELEMENT%d [tailport=e, headport=s];\n", list->tail);
    fprintf(tmp_dot, "\tELEMENT_FREE -> ELEMENT%d [tailport=e, headport=s];\n", list->free);

    fputc('}', tmp_dot);

    char cmd[512];
    sprintf(cmd, "/opt/homebrew/bin/dot -Tsvg \"tmp.dot\" -o \"graphs/output_%zu.svg\" > \"graphs/dot.log\" 2>&1", call_count);
    fclose(tmp_dot);
    system(cmd);
    call_count++;

    PrintfDebugging();
}
