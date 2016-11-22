#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *next;
    int key;
    int length;
    int data;
} Node;


Node *create_list()
{
    Node *head = NULL;
    head = (Node *)malloc(sizeof(Node));
    head->length = 0;
    head->next = NULL;

    return head;
}

void list_insert(Node *head, int key, Node *new)
{
    if (head == NULL || new == NULL)
    {
        return head; 
    }

    if (key > head->length+1 || key == 0)
    {
        return NULL; 
    }



}


int main(int args, char **argv) 
{
    Node *head = create_list();
    printf("%d\n", head->length);
    return 0;

}
