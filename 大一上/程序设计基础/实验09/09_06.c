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

struct cell* sort(struct cell* head) {
    // 递增排序链表，head是单链表首结点指针
    struct cell* p, * pb, * r, * rb, * q;
    p = pb = r = rb = q = NULL;
    pb = head;
    p=pb->next;
    while(p->next)
    {
        rb=pb;
        r=p;
        while(r->next)
        {
            rb=rb->next;
            r=r->next;
            if(r->x<p->x)
            {
                q=r->next;
                pb->next=r;
                r->next=p;
                p->next=q;
                p=pb->next;
                q=r;
                r=rb;
                rb=q;
            }
        }
        p=p->next;
        pb=pb->next;
    }
    
    return head;
} /* sort */

void print(struct cell *head)
{
    // 打印整个单链表,head是指向单链表首结点的指针
    struct cell *p=head->next;
    if(p==NULL)
    {
        printf("NULL");
        return;
    }
    while(p)
    {
        printf("%d ", p->x);
        p=p->next;
    }
}
void release(struct cell *head)
{
    // 释放单链表空间,head是指向单链表首结点的指针
    struct cell *temp;
    while(head)
    {
        temp=head;
        head=head->next;
        free(temp);
    }

}

int main(void) {
    struct cell* head;
    
    head = build();
    
    if (head != NULL) {
        head = sort(head);
        print(head);
    } else {
        printf("NULL");
    }
    
    release(head);
    return 0;
}