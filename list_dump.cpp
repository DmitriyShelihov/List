#include "list_dump.h"

void print_list_chain(FILE* dot_file, LIST* list, int start_id, const char* color);

void make_nodes_in_raw(FILE* dot_file, size_t data_size);

void print_node(FILE* dot_file, LIST* list, int index);

void print_all_nodes (FILE* dot_file, LIST* list);

void print_main_cells(FILE* dot_file, LIST* list);

void make_dot_dump(FILE* dot_file, LIST* list);

void print_list_chain(FILE* dot_file, LIST* list, int start_id, const char* color)
{
    while (start_id != 0)
    {
        fprintf(dot_file, "node%d -> node%d [color = \"%s\"];\n",
                start_id, ARRAY[start_id].next, color);

        if (ARRAY[start_id].prev != -1)
        {
            fprintf(dot_file, "node%d -> node%d [color = \"lightgoldenrod1\"];\n",
                    start_id, ARRAY[start_id].prev);
            fprintf(dot_file, "node%d -> node%d [style = invis; weight = 1000000];\n",
                    start_id, ARRAY[start_id].prev);
        }

        start_id = ARRAY[start_id].next;
    }

}

void make_nodes_in_raw(FILE* dot_file, size_t data_size)
{
    for (int i = 0; i < data_size; i++)
    {
        if (i == data_size - 1)
            fprintf(dot_file, "node%d", i);
        else
            fprintf(dot_file, "node%d ->", i);
    }
    fprintf(dot_file, "[weight = 10000; style = invis];\n");
}

void print_node(FILE* dot_file, LIST* list, int index)
{
    if (ARRAY[index].prev == -1)
    {
        fprintf(dot_file, "node%d[shape = Mrecord, style = filled, fillcolor=\"limegreen\", label = \"NODE_%d| {<data> FREE| <next> next : %d | <prev> prev : %d}\"];\n",
                index, index, ARRAY[index].next, ARRAY[index].prev);
    }
    else
    {
        fprintf(dot_file, "node%d[shape = Mrecord, style = filled, fillcolor=\"mediumturquoise\", label = \"NODE_%d| {<data> data : %.4lf| <next> next : %d | <prev> prev : %d}\"];\n",
                index, index, ARRAY[index].value, ARRAY[index].next, ARRAY[index].prev);
    }
}

void print_all_nodes (FILE* dot_file, LIST* list)
{
    fprintf(dot_file, "{rank = max;node%d[shape = Mrecord, style = filled, fillcolor=\"#FF0000\", label = \"NODE_%d|"
                      "{<data> POISON| <next> next : %d | <prev> prev : %d}\"];\n}\n"
                      "{rank = same;", 0, 0, ARRAY[0].next, ARRAY[0].prev);

    for (int i = 1; i < DATA_SIZE; i++)
        print_node(dot_file, list, i);

    fprintf(dot_file, "}\n");
}

void print_main_cells(FILE* dot_file, LIST* list)
{
    fprintf(dot_file, "head -> node%d [color = \"mediumturquoise\"];\n"
                       "tail -> node%d [color = \"mediumturquoise\"];\n"
                       "free -> node%d [color = \"limegreen\"];\n",
                       ARRAY[0].next, ARRAY[0].prev, FIRST_FREE);
}

void make_dot_dump(FILE* dot_file, LIST* list)
{
    fprintf(dot_file, "digraph G{"
                            "rankdir = HR;\n"
                            "graph [dpi = 150];\n"
                            "ranksep = 0.5;\n"
                            "splines = ortho;\n"
                            "edge[minlen = 3, penwidth = 3];\n"
                            "graph [bgcolor=\"#31353b\"]"
	                        "node[color=\"black\",fontsize=14];\n"
	                        "edge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n"
                            "node[shape = record, style = rounded, fixedsize = true, height = 1, width = 3, fontsize = 20];\n");

    fprintf(dot_file,       "{rank = min;\n"
		                        "head[label = \"head\", shape = Mrecord, style = filled, fillcolor=\"mediumturquoise\",width = 1];\n"
	                        "}\n"
                            "{rank = min;\n"
                                "tail[label = \"tail\", shape = Mrecord, style = filled, fillcolor=\"mediumturquoise\", width = 1];\n"
                            "}\n"
                            "{rank = min;\n"
                                "free[label = \"free\", shape = Mrecord, style = filled, fillcolor=\"limegreen\", width = 1];\n"
                            "}\n");

    print_main_cells(dot_file, list);

    print_all_nodes(dot_file, list);

    make_nodes_in_raw(dot_file, DATA_SIZE);

    print_list_chain(dot_file, list, ARRAY[0].next, "snow1");

    fprintf(dot_file, "node%d -> node%d [color = \"red\"];\n"
                       "node%d -> node%d [color = \"red\"];\n",
                       0, ARRAY[0].prev, 0, ARRAY[0].next);

    print_list_chain(dot_file, list, FIRST_FREE, "limegreen");

    fprintf(dot_file, "}");
}

int list_dump_png(LIST* list)
{
    FILE* dot_file = fopen("auto_file.dot", "w");

    if (dot_file == NULL)
    {
        printf(RED "ERROR: didn't create dot file\n" END_OF_COLOUR);
        return -1;
    }

    make_dot_dump(dot_file, list);

    fclose(dot_file);
    system("dot auto_file.dot -T png -o graph.png");

    FILE* dump_txt = fopen("dump.txt", "w");

    if (dump_txt == NULL)
    {
        printf("dump_txt file creating error");
        return -1;
    }

    file_dump_list(dump_txt, list);

    FILE* dump_html = fopen("dump.html", "w");

    if (dump_html == NULL)
    {
        printf(RED "dump_html file creating error" END_OF_COLOUR);
        return -2;
    }

    fprintf(dump_html, "<!DOCTYPE html>\n"
                       "<html>\n"
                       "<iframe src=\"dump.txt\" width=\"100%%\" height=\"300\">\n"
                       "</iframe>\n"
                       "<img src=\"graph.png\" width=\"%d\" height=\"200\">\n"
                       "</html>\n", 150 * DATA_SIZE);

    fclose(dump_html);
}

int file_dump_list(FILE* output_file, LIST* list)
{
    fprintf(output_file, "Main info: head: %d, tail: %d, free: %d, data_size: %d, elem_number: %d\nLIST DUMP:\nNumber: |" ,
          ARRAY[0].next, ARRAY[0].prev, FIRST_FREE, DATA_SIZE, list->elem_number);

    for (int i = 0; i < DATA_SIZE; i++)
        fprintf(output_file, " %11d |", i);

    fprintf(output_file, "\nData  : |");

    for (int i = 0; i < DATA_SIZE; i++)
    {
        if (ARRAY[i].value != POISON)
            fprintf(output_file, " %11lf |", ARRAY[i].value);
        else
            fprintf(output_file, "     Poison  |");
    }

    fprintf(output_file, "\nNext  : |");

    for (int i = 0; i < DATA_SIZE; i++)
        fprintf(output_file," %11d |", ARRAY[i].next);

    fprintf(output_file,"\nPrev  : |");

    for (int i = 0; i < DATA_SIZE; i++)
        fprintf(output_file," %11d |", ARRAY[i].prev);

    fprintf(output_file,"\n\n");
    return 0;
}

int list_dump(LIST* list)
{
    printf(YELLOW "USER LIST DUMP:\n" END_OF_COLOUR);

    if (list == NULL)
    {
        printf(RED "List_dump cannot find list, <NULL POINTER>" END_OF_COLOUR);
        return -1;
    }
    printf(RED "[" END_OF_COLOUR);

    for (int i = ARRAY[0].next; i != ARRAY[0].prev; i = ARRAY[i].next)
        printf(" %11lf " RED "," END_OF_COLOUR, ARRAY[i].value);

    if (ARRAY[0].next == ARRAY[0].prev && ARRAY[ARRAY[0].next].next != 0)
    {
        printf(RED "]" END_OF_COLOUR);
        printf("\n\n");
        return 0;
    }
    printf(" %11lf " RED "]\n\n" END_OF_COLOUR, ARRAY[ARRAY[0].prev].value);
    return 0;
}

void list_dump_verbose(LIST* list)
{
    assert(list != NULL);

    printf(YELLOW "Main info: head: %d, tail: %d, free: %d, data_size: %d, elem_number: %d\n"
           YELLOW "LIST DUMP:\n" END_OF_COLOUR
           "Number: " RED "|" END_OF_COLOUR,
           ARRAY[0].next, ARRAY[0].prev, FIRST_FREE, DATA_SIZE, list->elem_number);

    for (int i = 0; i < DATA_SIZE; i++)
        printf(BLUE " %11d " RED "|" END_OF_COLOUR, i);

    printf("\nData  : " RED "|" END_OF_COLOUR);

    for (int i = 0; i < DATA_SIZE; i++)
    {
        if (ARRAY[i].value != POISON)
            printf(" %11lf " RED "|" END_OF_COLOUR, ARRAY[i].value);
        else
            printf(GREEN"     Poison  " RED "|" END_OF_COLOUR);
    }

    printf("\nNext  : " RED "|" END_OF_COLOUR);

    for (int i = 0; i < DATA_SIZE; i++)
        printf(" %11d " RED "|" END_OF_COLOUR, ARRAY[i].next);

    printf("\nPrev  : " RED "|" END_OF_COLOUR);

    for (int i = 0; i < DATA_SIZE; i++)
        printf(" %11d " RED "|" END_OF_COLOUR, ARRAY[i].prev);

    printf("\n\n");
}
