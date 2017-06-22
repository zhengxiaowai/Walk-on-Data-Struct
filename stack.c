#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

int stack_push(Stack *stack, const void *data)
{
    // list insert a head node
    return list_ins_next(stack, NULL, data);
}

int stack_pop(Stack *stack, void **data)
{
    // list remove a last node
    return list_rem_next(stack, NULL, data);
}

int main()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));

    stack_init(stack, free);
    printf("stack_init: ");
    stack_traverse(stack);

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

    stack_push(stack, (void *)p_first_data);
    stack_push(stack, (void *)p_third_data);
    stack_push(stack, (void *)p_second_data);
    stack_push(stack, (void *)p_fourth_data);
    printf("stack_push: ");
    stack_traverse(stack);

    int head_data, *p_head_data;
    int tail_data, *p_tail_data;
    p_head_data = &head_data;
    p_tail_data = &tail_data;
    stack_pop(stack, (void **)&p_head_data);
    stack_pop(stack, (void **)&p_tail_data);
    printf("remove a node, data is %d\n", *(int *)p_head_data);
    printf("remove a node, data is %d\n", *(int *)p_tail_data);
    printf("stack_pop: ");
    stack_traverse(stack);

    void *p_elemt_data = stack_peek(stack);
    int size = stack_size(stack);
    printf("stack_peek: %d\n", *(int *)p_elemt_data);
    printf("stack_size: %d\n", size);

    stack_destroy(stack);
    printf("stack_destroy: ");
    stack_traverse(stack);
}