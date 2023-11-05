#ifndef LIST_DUMP_H
#define LIST_DUMP_H

#include "list.h"

void print_list_chain(FILE* dot_file, LIST* list, int start_id, const char* color);

void make_nodes_in_raw(FILE* dot_file, size_t data_size);

void print_node(FILE* dot_file, LIST* list, int index);

void print_all_nodes (FILE* dot_file, LIST* list);

void print_main_cells(FILE* dot_file, LIST* list);

void make_dot_dump(FILE* dot_file, LIST* list);

int list_dump_png(LIST* list);

int file_dump_list(FILE* output_stream, LIST* list);


#endif
