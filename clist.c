#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "clist.h"

void clist_init(CList *list, void (*destroy)(void *data))
{
    // 循环链表不需要 tail
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;

    return;
}
void clist_destroy(CList *list)
{
    void *data;

    while (clist_size(list) > 0)
    {
        if (clist_rem_next(list, list->head, (void **)&data) == 0 && list->destroy != NULL)
            list->destroy(data);
    }

    memset(list, 0, sizeof(CList));
    return;
}
int clist_ins_next(CList *list, CListElmt *element, const void *data)
{
    CListElmt *new_element = (CListElmt *)malloc(sizeof(CListElmt));
    if (new_element == NULL)
        return -1;

    new_element->data = (void *)data;
    if (element == NULL && clist_size(list) == 0)
    {
        list->head = new_element;
        new_element->next = new_element;
    }
    else
    {
        new_element->next = element->next;
        element->next = new_element;
    }

    list->size++;
    return 0;
}
int clist_rem_next(CList *list, CListElmt *element, void **data)
{
    CListElmt *old_element;

    if (clist_size(list) == 0)
        return -1;

    *data = element->next->data;

    if (clist_size(list) == 1)
    {
        // 只有一个元素时候
        // 该元素的 next 指向自己
        old_element = element->next;
        list->head = NULL;
    }
    else
    {
        old_element = element->next;
        element->next = element->next->next;
        if (clist_head(list) == old_element)
            list->head = old_element->next;
    }

    free(old_element);
    list->size--;
    return 0;
}
void list_traverse(CList *list)
{
    if (list == NULL || clist_size(list) == 0)
    {
        printf("\n\n");
        return;
    }
        

    CListElmt *node = list->head;
    do 
    {
        printf("%d ", *((int *)clist_data(node)));
        node = node->next;
    } while ((node != NULL && node != clist_head(list)));

    printf("\n\n");
}

int main()
{
    CList *list = (CList *)malloc(sizeof(CList));

    clist_init(list, free);
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

    clist_ins_next(list, NULL, (void *)p_first_data);
    clist_ins_next(list, list->head, (void *)p_fourth_data);
    clist_ins_next(list, list->head, (void *)p_second_data);
    clist_ins_next(list, list->head->next, (void *)p_third_data);
    printf("list_ins_next: ");
    list_traverse(list);

    clist_destroy(list);
    printf("dlist_destroy: ");
    list_traverse(list);
}