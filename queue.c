#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

int queue_enqueue(Queue *queue, const void *data)
{
    // list insert a tail node
    return list_ins_next(queue, list_tail(queue), data);
}

int queue_dequeue(Queue *queue, void **data)
{
    // list remove a last node
    return list_rem_next(queue, NULL, data);
}

int main()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    queue_init(queue, free);
    printf("queue_init: ");
    queue_traverse(queue);

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

    queue_enqueue(queue, (void *)p_first_data);
    queue_enqueue(queue, (void *)p_second_data);
    queue_enqueue(queue, (void *)p_third_data);
    queue_enqueue(queue, (void *)p_fourth_data);
    printf("queue_enqueue: ");
    queue_traverse(queue);

    int head_data, *p_head_data;
    int tail_data, *p_tail_data;
    p_head_data = &head_data;
    p_tail_data = &tail_data;
    queue_dequeue(queue, (void **)&p_head_data);
    queue_dequeue(queue, (void **)&p_tail_data);
    printf("remove a node, data is %d\n", *(int *)p_head_data);
    printf("remove a node, data is %d\n", *(int *)p_tail_data);
    printf("queue_dequeue: ");
    queue_traverse(queue);

    void *p_elemt_data = queue_peek(queue);
    int size = queue_size(queue);
    printf("queue_peek: %d\n", *(int *)p_elemt_data);
    printf("queue_size: %d\n", size);

    queue_destroy(queue);
    printf("queue_destroy: ");
    queue_traverse(queue);
}