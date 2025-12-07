#include <stdio.h>
#include <malloc.h>

struct cell
{
    // 单链表结点结构体定义
    int x;
    struct cell *next;
};
struct cell *build(void)
{ // 新建单链表，并将建好的单链表首结点地址返回
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
    return head;
    // 返回单链表头
}
struct cell *del2one(struct cell *head)
{
    // 删除重复结点只保留一个，head是单链表首结点指针
    struct cell *p = head->next, *s, *temp;
    while (p)
    {
        s = p;
        while (s->next)
        {
            if (s->next->x == p->x)
            {
                temp = s->next;
                s->next = s->next->next;
                free(temp);
            }
            else
                s = s->next;
        }
        p = p->next;
    }
    return head; // 返回删除重复结点的单链表头
}
void print(struct cell *head)
{
    // 打印整个单链表,head是指向单链表首结点的指针
    struct cell *p = head->next;
    if (p == NULL)
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
void release(struct cell *head)
{
    // 释放单链表空间,head是指向单链表首结点的指针
    struct cell *temp;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
int main(void)
{
    struct cell *head;
    head = build();
    head = del2one(head);
    if (head != NULL)
        print(head);
    else
        printf("NULL");
    release(head);
}
