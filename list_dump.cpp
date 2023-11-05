#include "list_dump.h"

void print_list_chain(FILE* dot_file, LIST* list, int start_id, const char* color)
{
    while (start_id != 0)
    {
        fprintf(dot_file, "node%d: <next> -> node%d [color = \"%s\"];\n",
                start_id, array[start_id].next, color);
        if (array[start_id].prev != -1)
        {
            fprintf(dot_file, "node%d: <prev> -> node%d [color = \"lightgoldenrod1\"];\n",
                    start_id, array[start_id].prev);
        }

        start_id = array[start_id].next;
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
    if (array[index].prev == -1)
    {
        fprintf(dot_file, "node%d[shape = Mrecord, style = filled, fillcolor=\"limegreen\", label = \"NODE_%d| {<data> FREE| <next> next : %d | <prev> prev : %d}\"];\n",
                index, index, array[index].next, array[index].prev);
    }
    else
    {
        fprintf(dot_file, "node%d[shape = Mrecord, style = filled, fillcolor=\"mediumturquoise\", label = \"NODE_%d| {<data> data : %.4lf| <next> next : %d | <prev> prev : %d}\"];\n",
                index, index, array[index].value, array[index].next, array[index].prev);
    }
}

void print_all_nodes (FILE* dot_file, LIST* list)
{
    fprintf(dot_file, "{rank = max;");
    fprintf(dot_file, "node%d[shape = Mrecord, style = filled, fillcolor=\"#FF0000\", label = \"NODE_%d| {<data> POISON| <next> next : %d | <prev> prev : %d}\"];\n",
                0, 0, array[0].next, array[0].prev);
    for (int i = 1; i < list->data_size; i++)
        print_node(dot_file, list, i);

    fprintf(dot_file, "}\n");
}

void print_main_cells(FILE* dot_file, LIST* list)
{
    fprintf(dot_file, "head -> node%d [color = \"mediumturquoise\"];\n", array[0].next);
    fprintf(dot_file, "tail -> node%d [color = \"mediumturquoise\"];\n", array[0].prev);
    fprintf(dot_file, "free -> node%d [color = \"limegreen\"];\n", list->first_free);
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

    make_nodes_in_raw(dot_file, list->data_size);

    print_list_chain(dot_file, list, array[0].next, "snow1");

    fprintf(dot_file, "node%d: <prev> -> node%d [color = \"red\"];\n", 0, array[0].prev);
    fprintf(dot_file, "node%d: <prev> -> node%d [color = \"red\"];\n", 0, array[0].next);

    print_list_chain(dot_file, list, list->first_free, "limegreen");

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
                           "<html>\n");
    fprintf(dump_html, "<iframe src=\"dump.txt\" width=\"100%%\" height=\"300\">\n");
    fprintf(dump_html, "</iframe>\n");

    fprintf(dump_html, "<img src=\"graph.png\" width=\"%d\" height=\"200\">\n", 150 * list->data_size);
    fprintf(dump_html, "</html>\n");

    fclose(dump_html);
}

int file_dump_list(FILE* output_file, LIST* list)
{
    fprintf(output_file, "Main info: head: %d, tail: %d, free: %d, data_size: %d, elem_number: %d\n" ,
          array[0].next, array[0].prev, list->first_free, list->data_size, list->elem_number);
    fprintf(output_file, "LIST DUMP:\n");
    if (list == NULL)
    {
        fprintf(output_file, "List_dump cannot find list <NULL POINTER");
        return -1;
    }
    fprintf(output_file, "Number: |");
    for (int i = 0; i < list->data_size; i++)
        fprintf(output_file, " %11d |", i);
    fprintf(output_file, "\n");

    fprintf(output_file, "Data  : |");
    for (int i = 0; i < list->data_size; i++)
    {
        if (array[i].value != POISON)
            fprintf(output_file, " %11lf |", array[i].value);
        else
            fprintf(output_file, "     Poison  |");
    }
    fprintf(output_file, "\n");
    fprintf(output_file, "Next  : |");
    for (int i = 0; i < list->data_size; i++)
        fprintf(output_file," %11d |", array[i].next);
    fprintf(output_file,"\nPrev  : |");
    for (int i = 0; i < list->data_size; i++)
        fprintf(output_file," %11d |", array[i].prev);
    fprintf(output_file,"\n\n");
    return 0;
}
