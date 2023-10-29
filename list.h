#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RED           "\x1b[31;2m"
#define YELLOW        "\x1b[33;2m"
#define GREEN         "\x1b[32;2m"
#define BLUE          "\x1b[34;2m"
#define END_OF_COLOUR "\x1b[39;49m"

const int SIZE_OF_LIST = 10;

typedef struct _elem
{
    double value;
    int next;
    int prev;
}ELEM;

typedef struct _HTF
{
    int head;
    int tail;
    int first_free;
}HTF;

typedef struct _list
{
    ELEM* data;
    HTF* htf;
}LIST;

int divide(double num1, double num2);

HTF* data_ctor(ELEM* list);

int special_list_dump(LIST* list);

int list_dump(LIST* list);

int find_prev_number(LIST* list, int index);

int list_insert(LIST* list, int index, double insert_value);

LIST* list_ctor(int size_of_list);

int list_pop(LIST* list, int index);

#endif
