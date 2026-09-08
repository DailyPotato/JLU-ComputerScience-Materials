class A
{
private:
    static A count;
public:
    static A& getInstance()
    {
        return count;
    }
}