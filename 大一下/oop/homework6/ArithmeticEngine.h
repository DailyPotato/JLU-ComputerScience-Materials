#ifndef ARITHMETIC_ENGINE_H
#define ARITHMETIC_ENGINE_H

// 运算引擎类：无状态工具类，只负责原有算术运算和旧版几何面积计算。
class ArithmeticEngine {
public:
    static const int MAX_VALUE;

    ArithmeticEngine();
    ~ArithmeticEngine();

    // 拷贝控制：无状态工具类，拷贝无业务意义，因此禁止拷贝。
    // 若基类允许拷贝，派生类应在初始化列表中显式调用基类拷贝构造，
    // 在赋值运算符中先调用基类赋值；本类不是继承基类，所以直接删除即可。
    ArithmeticEngine(const ArithmeticEngine&) = delete; // 无状态工具类不需要复制对象。
    ArithmeticEngine& operator=(const ArithmeticEngine&) = delete; // 禁止赋值避免误以为有独立状态。

    int add(int a, int b) const;
    int subtract(int a, int b) const;
    int multiply(int a, int b) const;
    int divide(int a, int b) const;
    int mod(int a, int b) const;

    double rectangleArea(double length, double width) const;
    double triangleArea(double base, double height) const;

    static void printLimits();
};

#endif
