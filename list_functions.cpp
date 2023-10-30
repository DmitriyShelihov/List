#include "list.h"

HTF* data_ctor(ELEM* data)
{
    HTF* htf = (HTF*)malloc(sizeof(HTF));
    htf->head = 1;
    htf->first_free = -1;
    htf->tail = -1;
    int elem_number = 0;
    data->value = POISON;
    data->next = 0;
    data->prev = 0;
    data++;
    elem_number++;
    /*double number = 0;
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
    }*/
    (data - 1)->next = 0;
    htf->tail = elem_number - 1;
    int _free = elem_number;
    for (int i = elem_number; i < SIZE_OF_LIST - 1; i++)
    {
        data->value = POISON;
        data->next = i + 1;
        data->prev = -1;
        data++;
    }
    data->value = POISON;
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
        printf(RED "List_dump cannot find list, <NULL POINTER>" END_OF_COLOUR);
        return -1;
    }
    printf(RED "[" END_OF_COLOUR);
    for (int i = list->htf->head; i != list->htf->tail; i = (list->data + i)->next)
    {
        printf(" %11lf " RED "," END_OF_COLOUR, (list->data + i)->value);

    }
    printf(" %11lf " RED "]" END_OF_COLOUR, (list->data + (list->htf->tail))->value);
    printf("\n\n");
    return 0;
}

int list_len(LIST* list)
{
    if (list == NULL)
    {
        printf(RED "List_len cannot find list, <NULL POINTER>" END_OF_COLOUR);
        return -1;
    }
    int lst_len = 0;
    for (int i = list->htf->head; i != list->htf->tail; i = (list->data + i)->next)
        lst_len ++;
    return lst_len + 1;
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
        if (((list->data + i)->value) != POISON)
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
        (list->data + (list->htf->head))->value = POISON;
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
        (list->data + (list->htf->tail))->value = POISON;
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
    (list->data + current_number)->value = POISON;
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

int list_pushback(LIST* list, double insert_value)
{
    int new_free = (list->data + (list->htf->first_free))->next;
    (list->data + (list->htf->first_free))->value = insert_value;
    (list->data + (list->htf->first_free))->prev = list->htf->tail;
    (list->data + (list->htf->first_free))->next = 0;
    (list->data + (list->htf->tail))->next = list->htf->first_free;
    list->htf->tail = list->htf->first_free;
    (list->htf->first_free) = new_free;
    return (list->htf->tail) + 1;
}

int list_pushfront(LIST* list, double insert_value)
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

LIST* list_ctor(int size_of_list)
{
    ELEM* data = (ELEM*)calloc(SIZE_OF_LIST, sizeof(ELEM));
    HTF* htf = data_ctor(data);
    LIST* List = (LIST*)malloc(sizeof(LIST));
    List->data = data;
    List->htf = htf;
    return List;
}

int list_verify(LIST* list)
{
    printf(YELLOW "LIST VERIFY STARTED:\n" END_OF_COLOUR);
    if (list == NULL || list->data == NULL || list->htf == NULL)
    {
        return - 1;
        printf(RED "Verify: NULL POINTER IN LIST\n" END_OF_COLOUR);
    }
    int error = 0;
    int is_loop = 1;
    for (int i = (list->htf->head); i < SIZE_OF_LIST -1 ; i = (list->data + i)->next)
    {
        if ((list->data + i)->next == 0)
        {
            is_loop = 0;
            printf(GREEN "Verify: CORRECT there is no loops\n" END_OF_COLOUR);
            break;
        }
    }
    if (is_loop == 1)
    {
        printf(RED "Verify: FAULT loop in a list: not found next = 0\n" END_OF_COLOUR);
        error += 10;
    }
    int elem_error = 0;
    for (int i = (list->htf->head); i != (list->htf->tail); i = (list->data + i)->next)
    {
        if (((list->data + ((list->data + i)->next))->prev) != i)
        {
            printf(RED "Verify: FAULT elem %d: prev(next) != elem\n" END_OF_COLOUR, i);
            error += 100;
            elem_error = 1;
            break;
        }
    }
    if (elem_error == 0)
        printf(GREEN "Verify: CORRECT for all elements: prev(next) == elem\n" END_OF_COLOUR);
    int is_free_error = 0;
    for (int i = list->htf->first_free; i < SIZE_OF_LIST && i != 0; i = (list->data + i)->next)
    {
        if ((list->data + i)->prev != -1)
        {
            printf(RED "Verify: FAULT free elem %d has non -1 prev\n" END_OF_COLOUR, i);
            error += 1000;
            is_free_error = 1;
            break;
        }
    }
    if (is_free_error == 0)
        printf(GREEN "Verify: CORRECT all free elem has -1 prev\n" END_OF_COLOUR);
    printf(YELLOW "LIST VERIFY ENDED:\n" END_OF_COLOUR);
    return error;
}

int list_dtor(LIST* list)
{
    if (list == NULL)
    {
        printf(RED "ERROR: list_dtor: Null pointer to list\n" END_OF_COLOUR);
        return -1;
    }
    int i = list->htf->head;
    while (i != list->htf->tail && i != 0)
    {
        int sv = (list->data + i)->next;
        (list->data + i)->value = POISON;
        (list->data + i)->prev = 0;
        (list->data + i)->next = 0;
        i = sv;
    }
    (list->data + i)->value = POISON;
    (list->data + i)->prev = 0;
    (list->data + i)->next = 0;
    int j = list->htf->first_free;
    while (j != 0 && j < SIZE_OF_LIST - 1 && (list->data+j)->next != 0)
    {
        int sv = (list->data + j)->next;
        (list->data + j)->prev = 0;
        (list->data + j)->next = 0;
        j = sv;
    }
    (list->data + j)->prev = 0;
    (list->data)->value = POISON;
    free(list->htf);
    return 0;
}

double list_elem(LIST* list, int index)
{
    int real_index = list->htf->head;
    for (int i = 0; i < index; i++)
        real_index = (list->data + real_index)->next;
    return (list->data + real_index)->value;
}

double delete_max(LIST* list)
{
    double list_max = DBL_MIN;
    int index_max = -1;
    int current_elem = list->htf->head;
    int i = 0;
    int lst_len = list_len(list);
    for (i; i < lst_len - 1; i++)
    {
        if ((list->data + current_elem)->value >= list_max)
        {
            list_max = (list->data + current_elem)->value;
            index_max = i;
        }
        current_elem = (list->data + current_elem)->next;
    }
    if (((list->data + list->htf->tail)->value) >= list_max)
    {
        list_max = ((list->data + list->htf->tail)->value) ;
        index_max = lst_len - 1;
    }
    list_pop(list, index_max);
    return list_max;
}

double delete_min(LIST* list)
{
    double list_min = DBL_MAX;
    int index_min = -1;
    int current_elem = list->htf->head;
    int i = 0;
    int lst_len = list_len(list);
    for (i; i < lst_len - 1; i++)
    {
        if ((list->data + current_elem)->value <= list_min)
        {
            list_min = (list->data + current_elem)->value;
            index_min = i;
        }
        current_elem = (list->data + current_elem)->next;
    }
    if (((list->data + list->htf->tail)->value) <= list_min)
    {
        list_min = ((list->data + list->htf->tail)->value) ;
        index_min = lst_len;
    }
    list_pop(list, index_min);
    return list_min;
}


