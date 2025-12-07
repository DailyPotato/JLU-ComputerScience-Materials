#include <malloc.h>
#include <stdio.h>
// 单链表结点结构体定义
struct cell
{
    int x;
    struct cell *next;
};

// 新建单链表，并将建好的单链表首结点地址返回
struct cell *build(void)
{
    struct cell *head, *tmp, *p;
    head = tmp = p = NULL;
    int n;
    head = (struct cell *)malloc(sizeof(struct cell));
    tmp = head;
    scanf("%d", &n);
    if (n == 0)
        return NULL;
    while (n)
    {
        p = (struct cell *)malloc(sizeof(struct cell));
        p->x = n;
        p->next = NULL;
        head->next = p;
        head = p;
        scanf("%d", &n);
    }
    head = tmp;
    return head; // 返回单链表头
}

// 寻找链表中间位置结点地址并返回，head是单链表首结点指针
struct cell *mid(struct cell *head)
{
    struct cell *p1 = head, *p2 = head, *temp;
    while (p2 && p2->next)
    {
        p2 = p2->next->next;
        temp = p1;
        p1 = p1->next;
        free(temp);
    }
    return p1;
}

// 打印整个单链表，head是单链表首结点指针
void print(struct cell *head)
{
    struct cell *p = head;
    if (!p)
    {
        printf("NULL");
        return;
    }
    while (p)
    {
        printf("%d ", p->x);
        p = p->next;
    }
}

// 释放单链表空间，head是单链表首结点指针
void release(struct cell *head)
{
    struct cell *p;
    while (head)
    {
        p = head;
        head = head->next;
        free(p);
    }
}

int main(void)
{
    struct cell *head, *half;

    head = build();
    half = mid(head);

    if (half != NULL)
        print(half);
    else
        printf("NULL");

    release(head);

    return 0;
}