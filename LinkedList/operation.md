# 链表的基本操作

链表的搜索、链表的插入、链表的删除是链表的三个基本操作。

以下所用伪函数名和 《 算法导论 》 中相同，
`Node` 代表链表上的某个元素
`Key` 代表 `Node` 上 `key` 的类型。

`Node` j具体可以定义为以下形式：

```c
typedef struct Node
{
  Node *next;
  Node *prev; // 如果存在的话
  Key key;
  Data *data;
}Node;
```

## 链表的搜索

使用 `LIST-SEARCH(L, k)` 来表示链表的搜索过程。

使用基于线性的搜索方法，来查找元素 `key` 为 `k` 的元素，并且返回该元素的指针、元素不存在返回 `NIL`。

所以 `LIST-SEARCH(L, k)` 可以用 C 语言表示成：

```c
Node *list_search(Node *head, Key key)
{
  // 查找一个元素
  // 存在返回该元素指针
  // 不存在返回 Null
}
```

## 链表的插入

使用 `LIST-INSERT(L, k, x)` 来表示链表的插入过程。

插入元素指的是把元素 `x` 插入到链表 `L` 中元素 key 为 `k` 的元素之前的位置。

用 C 语言可以表示成：

```c
void list_insert(Node *head, Key key, Node *x)
{
  // 从 head 开始遍历
  // 找到 key 为 k 的元素
  // 把 x 插入到它前面
}
```

## 链表的删除

使用 `LIST-DELETE(L, k)` 来表示链表的删除过程。

找到该元素，并且释放内存。


用 C 语言可以表示成：

```c
void list_delete(Node *L, Key key)
{
  // 遍历找到 Key 为 k 的元素
  // 重新设置前后指针的指向
  // 释放掉删除元素的内存
}
```
