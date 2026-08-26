class MyCircularQueue
{
public:
    int front;
    int rear;
    int capacity;
    vector<int> elements;
    MyCircularQueue(int k)
    {
        capacity = k+1;
        this->elements = vector<int>(capacity);
        front = rear = 0;
    }

    bool enQueue(int value)
    {
        if (!isFull())
        {
            elements[rear % capacity] = value;
            rear = (rear + 1) % capacity;
            return true;
        }
        return false;
    }

    bool deQueue()
    {
        if (!isEmpty())
        {
            front = (front + 1) % capacity;
            return true;
        }
        return false;
    }

    int Front()
    {
        if (isEmpty())
        {
            return -1;
        }
        return elements[front];
    }

    int Rear()
    {
        if (isEmpty())
        {
            return -1;
        }
        return elements[(rear - 1 + capacity) % capacity];
    }

    bool isEmpty()
    {
        return front == rear;
    }

    bool isFull()
    {
        return front == (rear + 1) % capacity;
    }
};