#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *next;
    int length;
    int data;
} Node;


Node *create_list()
{
    Node *head = NULL;
    head = (Node *)malloc(sizeof(Node));
    head->next = NULL;
    head->length = 0;

    return head;
}

void list_insert(Node *head, int pos, Node *new)
{
    Node *tmp = head;
    if (head == NULL || new == NULL || pos < 1)
    {
        return;
    }

    if (pos > tmp->length + 1)
    {
        return;
    }

    //TODO


}

Node *list_search(Node *head, int pos)
{
    Node *tmp = head;
    
    int key = 0;
    while(tmp != NULL && key != pos)
    {
        tmp = tmp->next;
        key += 1;
    }

    return tmp;

}


// 删除分成两种
// 1. 删除给定元素 O(1)
// 2. 删除关键字元素 O(n)
void list_delete(Node *head, int pos)
{
    if (head == NULL && head->next == NULL) {
        return;
    }
    
    if (pos < 1) {
        return;
    }
    
    Node *tmp = head;
    if (pos == 1) {
        // 直接删除第一个元素
        Node *pos_1 = tmp->next;
        if (pos_1->next != NULL)
        {
            // 存在第二个元素
            tmp->next = pos_1->next;
        }
        free(pos_1);
    }
    else
    {
        Node *pos_prev = list_search(head, pos-1);
        Node *phit = pos_prev->next;

        if (phit->next != NULL)
        {
           pos_prev->next = phit->next; 
        }

        free(phit);
    }
}


int main(int args, char **argv) 
{
    Node *head = create_list();
    printf("%d\n", head->length);
    return 0;

}
