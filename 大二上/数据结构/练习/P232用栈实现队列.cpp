#include<iostream>
#include<stack>
using namespace std;

class MyQueue {
public:
stack<int>* stk1;
stack<int>* stk2;
    MyQueue() {
        stk1=new stack<int>;
        stk2=new stack<int>;
    }
    
    void push(int x) {
        stk2->push(x);
        int size=stk1->size();
        while(size--)
        {
            stk2->push(stk1->top());
            stk1->pop();
        }
        stack<int>* temp=stk1;
        stk1=stk2;
        stk2=temp;
    }
    
    int pop() {
        int val=stk1->top();
        stk1->pop();
        return val;
    }
    
    int peek() {
        return stk1->top();
    }
    
    bool empty() {
        return stk1->empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */