#include <iostream>
using namespace std;

struct ListNode
{
    ListNode *next;
    int num;
};

ListNode * Reaverse(ListNode* Head,int k)
{
    ListNode *pre=Head,*tail=Head;
    if(Head==nullptr||k<=1)return Head;
    while(true)
    {
        for(int i=0;i<k;i++)
        {
            tail=tail->next;
            if(tail==nullptr)return Head;
        }
        ListNode *prev,*nextGroup,*first,*cur;
        nextGroup=tail->next;
        first=pre->next;
        cur=first;
        prev=nextGroup;
        while(cur!=nextGroup)
        {
            ListNode * temp=cur->next;
            cur->next=prev;
            prev=cur;
            cur=temp;
        }
        pre->next=tail;
        pre=first;
        tail=pre;
    }
}

int main()
{
    ListNode *head = new ListNode();
    head->next = new ListNode();
    head->next->num = 1;
    head->next->next = new ListNode();
    head->next->next->num = 2;
    head->next->next->next = new ListNode();
    head->next->next->next->num = 3;
    head->next->next->next->next = new ListNode();
    head->next->next->next->next->num = 4;
    head->next->next->next->next->next = nullptr;

    ListNode *newHead = Reaverse(head, 2);
    cout<<"Reversed list: ";
    ListNode *current = newHead;
    while(current != nullptr)
    {
        cout<<current->num<<" ";
        current = current->next;
    }
    cout<<endl;
}