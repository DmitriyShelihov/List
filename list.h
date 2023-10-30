#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define RED           "\x1b[31;2m"
#define YELLOW        "\x1b[33;2m"
#define GREEN         "\x1b[32;2m"
#define BLUE          "\x1b[34;2m"
#define END_OF_COLOUR "\x1b[39;49m"

const int SIZE_OF_LIST = 2000;

const double VERY_BIG = DBL_MAX;

const double POISON = DBL_MIN;

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

HTF* data_ctor(ELEM* list);  //создание массива структур в списке(авт.)

int special_list_dump(LIST* list);  //dump для разраба

int list_dump(LIST* list); //dump для юзера

int find_prev_number(LIST* list, int index); //ищет элемент перед данным по индексу(авт.)

int list_insert(LIST* list, int index, double insert_value); //вставка элемента

LIST* list_ctor(int size_of_list); //создание списка

int list_pop(LIST* list, int index); //удаление элеимента по индексу

int list_verify(LIST* list); //проверка списка по всем параметрам

double list_elem(LIST* list, int index); //значение по индексу

int list_len(LIST* list); //длина списка (for user)

int list_pushback(LIST* list, double insert_value); //вставка элемента в конец (удобнее)

int list_dtor(LIST* list); //занулить все ячейки массива и free(htf)

double delete_max(LIST* list); //удаление максимального элемента

double delete_min(LIST* list); //Удаление минимального элемента

int list_pushfront(LIST* list, double insert_value); // вставить в начало списка

#endif
