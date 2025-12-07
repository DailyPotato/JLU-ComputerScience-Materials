#include <stdio.h>
#include <malloc.h>

struct cell {
    // 单链表结点结构体定义
    int x;
    struct cell* next;
};

struct cell* build(void) {
    // 新建单链表，并将建好的单链表首结点地址返回
    struct cell* head, * tmp, * p;
    head = tmp = p = NULL;
    int n;
    
    head=(struct cell*)malloc(sizeof(struct cell));
    tmp=head;

    scanf("%d",&n);
    if(!n)return NULL;
    while(n)
    {
        struct cell* p=(struct cell*)malloc(sizeof(struct cell));
        p->x=n;
        p->next=NULL;
        head->next=p;
        head=p;
        scanf("%d",&n);
    }
    head=tmp;
    return head; // 返回单链表头
}

struct cell* back(struct cell* head, int k)
{
    // 求链表倒数第k个结点，head是单链表首结点指针
    struct cell*fast=head,*slow=head;
    for(;k>0;k--)
    {
        fast=fast->next;
    }
    while(fast)
    {
        slow=slow->next;
        fast=fast->next;
    }
    return slow;
}

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

int main(void) {
    struct cell* head, *result;
    int k;
    
    head = build();
    scanf("%d", &k);
    result = back(head, k);
    
    if (result != NULL)
        printf("%d", result->x);
    else
        printf("NULL");
    
    release(head);
}