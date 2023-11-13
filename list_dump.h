#ifndef LIST_DUMP_H
#define LIST_DUMP_H

#include "list.h"

int list_dump_png(LIST* list);                      //dump в файл + graph viz

int file_dump_list(FILE* output_stream, LIST* list);   //dump в файл

int list_dump(LIST* list); //печатает в порядке связей элементов. head -> elem1->elem2 ...-> tail

void list_dump_verbose(LIST* list); //цветная распечатка в консоль


#endif
