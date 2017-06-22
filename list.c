#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"

void list_init(List *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;
}

void list_destroy(List *list)
{
    void *data;

    while (list_size(list) > 0)
    {
        if (list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL)
            list->destroy(data);
    }

    memset(list, 0, sizeof(List));
    return;
}

int list_ins_next(List *list, ListElmt *element, const void *data)
{
    ListElmt *new_element;

    //  new element
    if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
        return -1;

    new_element->data = (void *)data;
    if (element == NULL)
    {
        // insert element at head of list
        if (list_size(list) == 0)
            list->tail = new_element;

        new_element->next = list->head;
        list->head = new_element;
    }
    else
    {
        if (element->next == NULL)
            list->tail = new_element;

        new_element->next = element->next;
        element->next = new_element;
    }

    list->size++;

    return 0;
}

int list_rem_next(List *list, ListElmt *element, void **data)
{
    ListElmt *old_element;

    if (list_size(list) == 0)
        return -1;

    if (element == NULL)
    {
        // remove head of list
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;

        if (list_size(list) == 1)
            list->tail = NULL;
    }
    else
    {
        *data = element->next->data;
        old_element = element->next;
        element->next = old_element->next; /* 书中有错 */

        if (element->next == NULL)
            list->tail = element;
    }

    free(old_element);
    list->size--;

    return 0;
}

void list_traverse(List *list)
{
    if (list == NULL)
        return;

    ListElmt *node = list->head;
    while (node != NULL)
    {
        printf("%d ", *((int *)list_data(node)));
        node = node->next;
    }
    printf("\n\n");
}

// unittest
// int main()
// {
//     List *list = (List *)malloc(sizeof(List));
//     if (list == NULL)
//         return -1;

//     list_init(list, free);
//     printf("list_init: ");
//     list_traverse(list);

//     int first_data = 1;
//     int second_data = 2;
//     int third_data = 3;
//     int fourth_data = 4;
//     list_ins_next(list, NULL, (void *)&first_data);
//     list_ins_next(list, list->head, (void *)&third_data);
//     list_ins_next(list, list->head, (void *)&second_data);
//     list_ins_next(list, list->head->next->next, (void *)&fourth_data);
//     printf("list_ins_next: ");
//     list_traverse(list);

//     int head_data, *p_head_data;
//     int tail_data, *p_tail_data;
//     p_head_data = &head_data;
//     p_tail_data = &tail_data;
//     list_rem_next(list, NULL, (void **)&p_head_data);
//     list_rem_next(list, list->head->next, (void **)&p_tail_data);
//     printf("remove head node, data is %d\n", *(int *)p_head_data);
//     printf("remove last node, data is %d\n", *(int *)p_tail_data);
//     printf("list_rem_next: ");
//     list_traverse(list);

//     return 0;
// }