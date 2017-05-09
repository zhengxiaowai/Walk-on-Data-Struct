#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dlist.h"

void dlist_init(DList *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;
}

void dlist_destroy(DList *list)
{
    void *data;

    while (dlist_size(list) > 0)
    {
        if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0 && list->destroy != NULL)
            list->destroy(data);
    }

    memset(list, 0, sizeof(DList));
    return;
}

int dlist_ins_next(DList *list, DListElmt *element, const void *data)
{
    DListElmt *new_element;

    if (element == NULL && dlist_size(list) != 0)
        return -1;

    new_element = (DListElmt *)malloc(sizeof(DListElmt));
    if (new_element == NULL)
        return -1;

    new_element->data = (void *)data;
    // insert a head
    if (dlist_size(list) == 0)
    {
        list->head = new_element;
        list->tail = new_element;
        list->head->next = NULL;
        list->head->prev = NULL;
    }
    else
    {
        new_element->next = element->next;
        new_element->prev = element;

        // element is a tail
        if (element->next == NULL)
            list->tail = new_element;
        else
            element->next->prev = new_element;

        element->next = new_element;
    }

    list->size++;
    return 0;
}

int dlist_ins_prev(DList *list, DListElmt *element, const void *data)
{
    if (element == NULL && dlist_size(list) != 0)
        return -1;

    DListElmt *new_element = (DListElmt *)malloc(sizeof(DListElmt));
    if (new_element == NULL)
        return -1;

    new_element->data = (void *)data;
    if (dlist_size(list) == 0)
    {
        list->head = new_element;
        list->tail = new_element;
        list->head->next = NULL;
        list->head->prev = NULL;
    }
    else
    {
        new_element->next = element;
        new_element->prev = element->prev;

        if (element->prev == NULL)
            list->head = new_element;
        else
            element->prev->next = new_element;

        element->prev = new_element;
    }

    list->size++;
    return 0;
}

int dlist_remove(DList *list, DListElmt *element, void **data)
{
    if (element == NULL || dlist_size(list) == 0)
        return -1;

    *data = element->data;

    if (dlist_is_head(list, element))
    {
        if (dlist_size(list) == 1)
        {
            list->head = NULL;
            list->tail = NULL;
        }
        else
        {
            list->tail = element->next;
            list->head->prev = NULL;
        }
    }
    else
    {
        element->prev->next = element->next;
        // tail element
        if (element->next == NULL)
            list->tail = element->prev;
        else
            element->next->prev = element->prev;
    }

    free(element);
    list->size--;
    return 0;
}

void list_traverse(DList *list)
{
    if (list == NULL)
        return;

    DListElmt *node = list->head;
    while (node != NULL)
    {
        printf("%d ", *((int *)dlist_data(node)));
        node = node->next;
    }
    printf("\n\n");
}

int main()
{
    DList *list = (DList *)malloc(sizeof(DList));

    dlist_init(list, free);
    printf("list_init: ");
    list_traverse(list);

    int first_data = 1, second_data = 2, third_data = 3, fourth_data = 4;
    int *p_first_data, *p_second_data, *p_third_data, *p_fourth_data;
    p_first_data = (int *)malloc(sizeof(int));
    p_second_data = (int *)malloc(sizeof(int));
    p_third_data = (int *)malloc(sizeof(int));
    p_fourth_data = (int *)malloc(sizeof(int));
    *p_first_data = first_data;
    *p_second_data = second_data;
    *p_third_data = third_data;
    *p_fourth_data = fourth_data;

    dlist_ins_next(list, NULL, (void *)p_first_data);
    dlist_ins_next(list, list->head, (void *)p_fourth_data);
    dlist_ins_next(list, list->head, (void *)p_second_data);
    dlist_ins_next(list, list->head->next, (void *)p_third_data);
    printf("list_ins_next: ");
    list_traverse(list);

    dlist_destroy(list);
    printf("dlist_destroy: ");
    list_traverse(list);

    p_first_data = (int *)malloc(sizeof(int));
    p_second_data = (int *)malloc(sizeof(int));
    p_third_data = (int *)malloc(sizeof(int));
    p_fourth_data = (int *)malloc(sizeof(int));
    *p_first_data = first_data;
    *p_second_data = second_data;
    *p_third_data = third_data;
    *p_fourth_data = fourth_data;
    dlist_init(list, free);
    dlist_ins_prev(list, NULL, (void *)p_fourth_data);
    dlist_ins_prev(list, list->head, (void *)p_first_data);
    dlist_ins_prev(list, list->head->next, (void *)p_second_data);
    dlist_ins_prev(list, list->head->next->next, (void *)p_third_data);
    printf("list_ins_prev: ");
    list_traverse(list);

    dlist_destroy(list);
    printf("dlist_destroy: ");
    list_traverse(list);
}