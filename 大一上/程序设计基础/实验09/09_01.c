#include <stdio.h>
#include <malloc.h>
struct cell
{ // 单链表结点结构体定义
    int x;
    struct cell *next;
};
struct cell *build(void)
{ // 新建单链表，并将建好的单链表首结点地址返回
    struct cell *head, *tmp, *p;
    head = tmp = p = NULL;
    head = (struct cell *)malloc(sizeof(struct cell));
    tmp = head;
    int n;
    scanf("%d", &n);
    if(n==0)return NULL;
    while(n)
    {
        p = (struct cell *)malloc(sizeof(struct cell));
        p->x=n;
        p->next=NULL;
        head->next=p;
        head=p;
        scanf("%d", &n);
    }
    head = tmp;
    return head; // 返回单链表头
}
void print(struct cell *head)
{ // 打印整个单链表,head是指向单链表首结点的指针
    if(head==NULL)return;
    struct cell *p;
    p = head->next;
    while(p)
    {
        printf("%d ", p->x);
        p = p->next;
    }
}
void release(struct cell *head)
{ // 释放单链表空间,head是指向单链表首结点的指针
    struct cell *p,*q ;
    p=head;
    while(p)
    {
        q=p;
        p=p->next;
        free(q);
    }
}
int main(void)
{
    struct cell *head;
    head = build();
    if (head != NULL)
        print(head);
    else
        printf("NULL");
    release(head);
    return 0;
}