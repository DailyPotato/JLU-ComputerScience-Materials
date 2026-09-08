#include <iostream>
using namespace std;
class CallBackObject;
class Server
{
public:
    Server(int size) : len(size)
    {
        data = new int[len];
        for (int i = 0; i < len; ++i)
            data[i] = i + 1;
    }
    ~Server() { delete[] data; }
    int Total(CallBackObject &obj);

private:
    int len;
    int *data;
};
class CallBackObject
{
public:
    virtual ~CallBackObject() {}
    virtual int CallBackFunc(int val) = 0;
};
class ClientA : public CallBackObject
{
public:
    virtual ~ClientA() {}
    virtual int CallBackFunc(int val)
    {
        return val;
    }
    void RequestA(Server &srv)
    {
        cout << srv.Total(*this) << endl;
    }
};
int Server::Total(CallBackObject &obj)
{
    int sum = 0;
    for (int i = 0; i < len; ++i)
    {
        sum +=obj.CallBackFunc(data[i]);
    }
    return sum;
}
class ClientB : public CallBackObject
{
public:
    virtual ~ClientB() {}
    virtual int CallBackFunc(int val)
    {
        return val*val;
    }
    void RequestB(Server &srv)
    {
        cout<<"Æ½·½ºÍ=";
        cout<<srv.Total(*this)<<endl;
    }
};

// 2
int main()
{
    Server srv2(2), srv3(3);
    ClientB b;
    b.RequestB(srv2);
    b.RequestB(srv3);
    return 0;
}