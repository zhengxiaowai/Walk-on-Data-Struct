#include <string.h>
#include <stdio.h>
#include <time.h>
#include "bitree.h"

void bitree_init(BiTree *tree, void (*destroy)(void *data))
{
    tree->size = 0;
    tree->destroy = destroy;
    tree->root = NULL;
}

void bitree_destroy(BiTree *tree)
{
    bitree_rem_left(tree, NULL);
    memset(tree, 0, sizeof(BiTree));
    return;
}
int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode *new_node, **position;

    if (node == NULL)
    {
        // 插入根节点
        if (bitree_size(tree) > 0)
            return -1;

        position = &(tree->root);
    }
    else
    {
        // 正常插入
        if (bitree_left(node) != NULL)
            return -1;
        position = &(node->left);
    }

    if ((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
        return -1;

    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return 0;
}
int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode *new_node, **position;

    if (node == NULL)
    {
        // 插入根节点
        if (bitree_size(tree) > 0)
            return -1;

        position = &(tree->root);
    }
    else
    {
        // 正常插入
        if (bitree_right(node) != NULL)
            return -1;
        position = &(node->right);
    }

    if ((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
        return -1;

    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return 0;
}
void bitree_rem_left(BiTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;

    // 不能删除空的数
    if (bitree_size(tree) == 0)
        return;

    if (node == NULL)
        position = &(tree->root);
    else
        position = &(node->left);

    if (*position != NULL)
    {
        bitree_rem_left(tree, *position);
        bitree_rem_right(tree, *position);

        if (tree->destroy != NULL)
        {
            tree->destroy((*position)->data);
        }

        free(*position);
        *position = NULL;

        tree->size--;
    }

    return;
}
void bitree_rem_right(BiTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;

    // 不能删除空的数
    if (bitree_size(tree) == 0)
        return;

    if (node == NULL)
        position = &(tree->root);
    else
        position = &(node->right);

    if (*position != NULL)
    {
        bitree_rem_left(tree, *position);
        bitree_rem_right(tree, *position);

        if (tree->destroy != NULL)
        {
            tree->destroy((*position)->data);
        }

        free(*position);
        *position = NULL;

        tree->size--;
    }

    return;
}

int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, void *data)
{
    // 构造根节点
    bitree_init(merge, left->destroy);

    if (bitree_ins_left(merge, NULL, data) != 0)
    {
        bitree_destroy(merge);
        return -1;
    }

    // 合并左右子数
    bitree_root(merge)->left = bitree_root(left);
    bitree_root(merge)->right = bitree_root(right);

    // 合并大小
    merge->size = merge->size + bitree_size(left) + bitree_size(right);

    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;

    return 0;
}

static void preorder(BiTreeNode *node)
{
    if (node)
    {
        printf("%d ", *((int *)bitree_data(node)));
        preorder(node->left);
        preorder(node->right);
    }
}

static void inorder(BiTreeNode *node)
{
    if (node)
    {
        inorder(node->left);
        printf("%d ", *((int *)bitree_data(node)));
        inorder(node->right);
    }
}

static void postorder(BiTreeNode *node)
{
    if (node)
    {
        postorder(node->left);
        postorder(node->right);
        printf("%d ", *((int *)bitree_data(node)));
    }
}

void print_tree(BiTree *tree)
{
    BiTreeNode *root = bitree_root(tree);
    printf("PREORDER: ");
    preorder(root);
    printf("\n");
    printf("INORDER: ");
    inorder(root);
    printf("\n");
    printf("POSTORDER: ");
    postorder(root);
    printf("\n");

    printf("-----END PRINT----\n");
}
int main()
{
    BiTree *tree = (BiTree *)malloc(sizeof(BiTree));

    bitree_init(tree, free);
    print_tree(tree);

    int *root_data = (int *)malloc(sizeof(int));
    *root_data = 1;
    bitree_ins_left(tree, NULL, root_data);
    print_tree(tree);

    srand(time(0));
    int i, *left_node_data, *right_node_data, ins_cnt = 10;

    left_node_data = (int *)malloc(sizeof(int));
    *left_node_data = rand() % 100 + 1;
    bitree_ins_left(tree, bitree_root(tree), left_node_data);

    right_node_data = (int *)malloc(sizeof(int));
    *right_node_data = rand() % 100 + 1;
    bitree_ins_right(tree, bitree_root(tree), right_node_data);
    print_tree(tree);

    bitree_rem_left(tree, bitree_root(tree));
    bitree_rem_right(tree, bitree_root(tree));
    print_tree(tree);

    BiTree *tree2 = (BiTree *)malloc(sizeof(BiTree));
    bitree_init(tree2, free);
    left_node_data = (int *)malloc(sizeof(int));
    *left_node_data = rand() % 100 + 1;
    right_node_data = (int *)malloc(sizeof(int));
    *right_node_data = rand() % 100 + 1;
    bitree_ins_left(tree2, bitree_root(tree), left_node_data);
    bitree_ins_right(tree2, bitree_root(tree), right_node_data);

    BiTree *new_tree = (BiTree *)malloc(sizeof(BiTree));
    bitree_init(new_tree, free);
    int *new_root_data = (int *)malloc(sizeof(int));
    *new_root_data = 6666;
    bitree_merge(new_tree, tree, tree2, new_root_data);
    print_tree(new_tree);

    bitree_destroy(new_tree);
    print_tree(new_tree);
}
