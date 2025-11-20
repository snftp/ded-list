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

    fputs("digraph G{\n", tmp_dot);
    fputs("\tgraph [splines=ortho];\n", tmp_dot);
    fputs("\tnode [shape=\"Mrecord\", color=\"pink\", style=\"filled\", fillcolor=\"pink\", fontsize=14];\n", tmp_dot);
    fputs("\tnodesep=0.4;\n", tmp_dot);
    fputs("\tedge[color=\"pink\"];\n", tmp_dot);

    fputs("\tsubgraph {\n\t\trank = same;\n", tmp_dot);

    fprintf(tmp_dot, "\t\tELEMENT%d [shape=ellipse, label = <<TABLE BORDER=\"0\" CELLBORDER=\"0\" CELLSPACING=\"2\" ROWS=\"*\" BGCOLOR=\"white\"> \n"
                         "\t\t  <TR> <TD BGCOLOR=\"pink\" PORT=\"index\"> %d        </TD> </TR>                                        \n"
                         "\t\t  <TR> <TD BGCOLOR=\"pink\" PORT=\"value\"> value %lg </TD> </TR>                                        \n"
                         "\t\t  <TR> <TD BGCOLOR=\"pink\" PORT=\"prev\">  prev  %d  </TD> </TR>                                        \n"
                         "\t\t  <TR> <TD BGCOLOR=\"pink\" PORT=\"next\">  next  %d  </TD> </TR>                                        \n"
                         "\t\t</TABLE>>];                                                                                              \n",
                0, 0, (list->nodes[i]).value, (list->nodes[i]).previous_index, (list->nodes[i]).next_index);

    // TODO: рисовать нулевой элемент отдельно и для него отрисовывать next и prev

    // TODO: рисовать список пустой памяти красиво
    for (int i = 1; i < LIST_SIZE; i++) {
        // printf("2\n");
        fprintf(tmp_dot, "\t\tELEMENT%d [label = <<TABLE BORDER=\"0\" CELLBORDER=\"0\" CELLSPACING=\"2\" ROWS=\"*\" BGCOLOR=\"white\"> \n"
                         "\t\t  <TR> <TD BGCOLOR=\"pink\" PORT=\"index\"> %d        </TD> </TR>                                        \n"
                         "\t\t  <TR> <TD BGCOLOR=\"pink\" PORT=\"value\"> value %lg </TD> </TR>                                        \n"
                         "\t\t  <TR> <TD BGCOLOR=\"pink\" PORT=\"prev\">  prev  %d  </TD> </TR>                                        \n"
                         "\t\t  <TR> <TD BGCOLOR=\"pink\" PORT=\"next\">  next  %d  </TD> </TR>                                        \n"
                         "\t\t</TABLE>>];                                                                                              \n",
                i, i, (list->nodes[i]).value, (list->nodes[i]).previous_index, (list->nodes[i]).next_index);
        // printf("2\n\n");
    }

    for (int i = 0; i < LIST_SIZE - 1; i++) {
        fprintf(tmp_dot, "\t\tELEMENT%d -> ELEMENT%d [constraint=true, style=invis, weight=10000]; \n",
                i, i + 1);
    }

    fputs("\t\tedge [constraint=false, weight=10];\n", tmp_dot);
    for (int i = 0; i < LIST_SIZE; i++) {
        fprintf(tmp_dot, "\t\tELEMENT%d -> ELEMENT%d; \n",
                i, (list->nodes[i]).next_index);
    }
    fputs("\t} \n", tmp_dot);

    fputs("\tedge[color=\"black\"];\n", tmp_dot);

    fprintf(tmp_dot, "\tELEMENT_FREE[shape=ellipse, style=\"filled\", fillcolor=\"white\", fontsize=12, label=\"FREE=%d\"]; \n", list->free);
    fprintf(tmp_dot, "\tELEMENT_FREE -> ELEMENT%d; \n", list->free);

    int head_index = GetHead(list);
    fprintf(tmp_dot, "\tELEMENT_HEAD[shape=ellipse, style=\"filled\", fillcolor=\"white\", fontsize=12, label=\"HEAD=%d\"]; \n", head_index);
    fprintf(tmp_dot, "\tELEMENT_HEAD -> ELEMENT%d; \n", head_index);

    int tail_index = GetTail(list);
    fprintf(tmp_dot, "\tELEMENT_TAIL[shape=ellipse, style=\"filled\", fillcolor=\"white\", fontsize=12, label=\"TAIL=%d\"]; \n", tail_index);
    fprintf(tmp_dot, "\tELEMENT_TAIL -> ELEMENT%d; \n", tail_index);

    fputc('}', tmp_dot);

    char cmd[512];
    sprintf(cmd, "/opt/homebrew/bin/dot -Tsvg \"tmp.dot\" -o \"graphs/output_%zu.svg\"" /* > \"graphs/dot.log\" 2>&1"*/, call_count);
    fclose(tmp_dot);
    system(cmd);
    call_count++;

    PrintfDebugging();
}
