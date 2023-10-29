#include "list.h"

int divide(double num1, double num2)
{
    return (num1/num2);
}


HTF* data_ctor(ELEM* data)
{
    HTF* htf = (HTF*)malloc(sizeof(HTF));
    htf->head = 1;
    htf->first_free = -1;
    htf->tail = -1;
    int elem_number = 0;
    data->value = divide(5.0, 0); //POISON
    data->next = 0;
    data->prev = 0;
    data++;
    elem_number++;
    double number = 0;
    int scanf_result = 1;
    while ((scanf_result = scanf_result = scanf("%lf", &number)) != EOF)
    {
        if (elem_number >= SIZE_OF_LIST)
        {
            printf(RED "List overflowing you should increase SIZE_OF_LIST\n" END_OF_COLOUR);
            htf->tail = elem_number;
            return htf;
        }
        data->value = number;
        data->next = elem_number+1;
        data->prev = elem_number-1;
        data++; elem_number++;
    }
    (data-1)->next = 0;
    htf->tail = elem_number - 1;
    int _free = elem_number;
    for (int i = elem_number; i < SIZE_OF_LIST - 1; i++)
    {
        data->value = divide(5.0, 0);
        data->next = i + 1;
        data->prev = -1;
        data++;
    }
    data->value = divide(5.0, 0);
    data->next = 0;
    data->prev = -1;
    htf->first_free = _free;
    return htf;
}

int list_dump(LIST* list)
{
    printf(YELLOW "USER LIST DUMP:\n" END_OF_COLOUR);
    if (list == NULL)
    {
        printf(RED "List_dump cannor find list <NULL POINTER>" END_OF_COLOUR);
        return -1;
    }
    printf(RED "[" END_OF_COLOUR);
    for (int i = list->htf->head; i != list->htf->tail; i = (list->data + i)->next)
    {
        printf(" %11lf " RED "," END_OF_COLOUR, (list->data + i)->value);

    }
    printf(" %11lf " RED "]" END_OF_COLOUR, (list->data + (list->htf->tail))->value);
    printf("\n\n");
}

int special_list_dump(LIST* list)
{
    printf(YELLOW "HTF: head: %d, tail: %d, free: %d\n" END_OF_COLOUR, list->htf->head, list->htf->tail, list->htf->first_free);
    printf(YELLOW "LIST DUMP:\n" END_OF_COLOUR);
    if (list == NULL)
    {
        printf(RED "List_dump cannor find list <NULL POINTER>" END_OF_COLOUR);
        return -1;
    }
    printf("Number: " RED "|" END_OF_COLOUR);
    for (int i = 0; i < SIZE_OF_LIST; i++)
        printf(BLUE " %11d " RED "|" END_OF_COLOUR, i);
    printf("\n");

    printf("Data  : " RED "|" END_OF_COLOUR);
    for (int i = 0; i < SIZE_OF_LIST; i++)
    {
        if (((list->data + i)->value) != divide(5.0, 0))
            printf(" %11lf " RED "|" END_OF_COLOUR, ((list->data + i)->value));
        else
            printf(GREEN"     Poison  " RED "|" END_OF_COLOUR);
    }
    printf("\n");
    printf("Next  : " RED "|" END_OF_COLOUR);
    for (int i = 0; i < SIZE_OF_LIST; i++)
        printf(" %11d " RED "|" END_OF_COLOUR, (list->data + i)->next);
    printf("\n");
    printf("Prev  : " RED "|" END_OF_COLOUR);
    for (int i = 0; i < SIZE_OF_LIST; i++)
        printf(" %11d " RED "|" END_OF_COLOUR, (list->data + i)->prev);
    printf("\n\n");
    return 0;
}

int list_pop(LIST* list, int index)
{
    index++;
    if (index == 1)
    {
        int next_elem = (list->data + (list->htf->head))->next;
        (list->data + next_elem)->prev = 0;
        (list->data + (list->htf->head))->value = divide(5.0, 0);
        (list->data + (list->htf->head))->next = list->htf->first_free;
        (list->data + (list->htf->head))->prev = -1;
        list->htf->first_free = list->htf->head;
        list->htf->head = next_elem;
        return index;
    }
    else if (index == 0)
    {
        printf(RED "You cannot pop the NULL cell\n" END_OF_COLOUR);
        return index;
    }
    else if (index == (list->htf->tail))
    {
        int prev_elem = (list->data + (list->htf->tail))->prev;
        (list->data + prev_elem)->next = 0;
        (list->data + (list->htf->tail))->value = divide(5.0, 0);
        (list->data + (list->htf->tail))->next = list->htf->first_free;
        (list->data + (list->htf->tail))->prev = -1;
        list->htf->first_free = list->htf->tail;
        list->htf->tail = prev_elem;
        return index;
    }
    else if (index >= SIZE_OF_LIST)
    {
        printf(RED "You cannot delete non-existent element" END_OF_COLOUR);
        return -1;
    }
    int prev_number = find_prev_number(list, index);
    int current_number = (list->data + prev_number)->next;
    int next_number = (list->data + current_number)->next;
    (list->data + prev_number)->next = next_number;
    (list->data + next_number)->prev = prev_number;
    (list->data + current_number)->value = divide(5.0, 0);
    (list->data + current_number)->next = list->htf->first_free;
    (list->data + current_number)->prev = -1;
    list->htf->first_free = current_number;
    return index;
}

int find_prev_number(LIST* list, int index)
{
    int current_index = list->htf->head;
    for (int i = 0; i < index - 2; i++)
        current_index = ((list->data) + current_index)->next;
    return current_index;
}

int list_insert(LIST* list, int index, double insert_value)
{
    index++;
    if (index == 0)
    {
        printf(RED "Insert in NULL element\n" END_OF_COLOUR);
        return 0;
    }
    else if (list->htf->first_free == 0)
    {
        printf(RED "first_free = 0 increase SIZE_OF_LIST\n" END_OF_COLOUR);
        return -1;
    }
    else if (index == 1)
    {
        int new_free = (list->data + (list->htf->first_free))->next;
        (list->data + (list->htf->first_free))->value = insert_value;
        (list->data + (list->htf->first_free))->prev = 0;
        (list->data + (list->htf->first_free))->next =  list->htf->head;
        (list->data + (list->htf->head))->prev =  list->htf->first_free;
        list->htf->head = list->htf->first_free;
        (list->htf->first_free) = new_free;
        return 1;
    }
    else if (index == (list->htf->tail + 1))
    {
        int new_free = (list->data + (list->htf->first_free))->next;
        (list->data + (list->htf->first_free))->value = insert_value;
        (list->data + (list->htf->first_free))->prev = list->htf->tail;
        (list->data + (list->htf->first_free))->next = 0;
        (list->data + (list->htf->tail))->next = list->htf->first_free;
        list->htf->tail = list->htf->first_free;
        (list->htf->first_free) = new_free;
        return index;
    }
    else if (index >= SIZE_OF_LIST)
    {
        printf(RED "INDEX > SIZE_OF_LIST you should increase SIZE_OF_LIST\n" END_OF_COLOUR);
        return index;
    }
    int prev_number = find_prev_number(list, index);
    int new_free = (list->data + (list->htf->first_free))->next;
    (list->data + (list->htf->first_free))->value = insert_value;
    (list->data + (list->htf->first_free))->next = (list->data + prev_number)->next;
    (list->data + list->htf->first_free)->prev = prev_number;
    (list->data + prev_number)->next = list->htf->first_free;
    (list->data + ((list->data + list->htf->first_free)->next))->prev = list->htf->first_free;
    list->htf->first_free = new_free;
    return index;
}

LIST* list_ctor(int size_of_list)
{
    ELEM* data = (ELEM*)calloc(SIZE_OF_LIST, sizeof(ELEM));
    HTF* htf = data_ctor(data);
    LIST* List = (LIST*)malloc(sizeof(LIST));
    List->data = data;
    List->htf = htf;
    return List;
}

int main()
{
    LIST* list = list_ctor(10);
    list_dump(list);
    list_pop(list, 2);
    list_dump(list);


    free(list->data);
    free(list);
    return 0;
}

