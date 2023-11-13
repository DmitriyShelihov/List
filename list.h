#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>

#define RED           "\x1b[31;2m"
#define YELLOW        "\x1b[33;2m"
#define GREEN         "\x1b[32;2m"
#define BLUE          "\x1b[34;2m"
#define END_OF_COLOUR "\x1b[39;49m"

#define ARRAY      (list->data)
#define FIRST_FREE (list->first_free)
#define DATA_SIZE  (list->data_size)

const double VERY_BIG = DBL_MAX;
const double POISON = DBL_MIN;

typedef struct _elem
{
    double value;
    int next;
    int prev;
}ELEM;

typedef struct _list
{
    ELEM* data;
    int first_free;
    size_t data_size;
    size_t elem_number;
}LIST;

int list_insert_before(LIST* list, int index, double insert_value);

int list_insert_after(LIST* list, int index, double insert_value);

LIST* list_ctor(int size_of_list);

int list_dtor(LIST* list);

int list_pop(LIST* list, int index);

int list_verify(LIST* list);

int list_push_back(LIST* list, double insert_value);

int list_push_front(LIST* list, double insert_value);

int list_resize(LIST* list, int new_size);

int list_insert(LIST* list, int index, double insert_value);


#endif
