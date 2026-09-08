#include <iostream>
#include <map>

class B {
public:
    B(int n) : data(n) {}
    int Data() const { return data; }
    void g1() {}
    void g2() {}
    void g3() {}
private:
    const int data;
};

class Action {
public:
    virtual void execute(B& b) = 0;
    virtual ~Action() = default;
};

class ActionCondition1 : public Action {
public:
    void execute(B& b) override { b.g1(); }
};

class ActionCondition5 : public Action {
public:
    void execute(B& b) override { b.g2(); }
};

class ActionCondition9 : public Action {
public:
    void execute(B& b) override { b.g3(); }
};

class ActionCondition100 : public Action {
public:
    void execute(B& b) override {
        b.g1();
        b.g2();
    }
};

class ActionRegistry {
private:
    std::map<int, Action*> actionMap;
public:
    void registerAction(int condition, Action* action) {
        actionMap[condition] = action;
    }

    Action* getAction(int condition) {
        auto it = actionMap.find(condition);
        if (it != actionMap.end()) {
            return it->second;
        }
        return nullptr;
    }
};
ActionRegistry globalRegistry;

void f(B& b) {
    int condition = b.Data();
    Action* action = globalRegistry.getAction(condition);
    if (action != nullptr) {
        action->execute(b);
    }

}

int main() {
    ActionCondition1 a1;
    ActionCondition5 a5;
    ActionCondition9 a9;
    ActionCondition100 a100;

    globalRegistry.registerAction(1, &a1);
    globalRegistry.registerAction(5, &a5);
    globalRegistry.registerAction(9, &a9);
    globalRegistry.registerAction(100, &a100);
    std::cout << "--- 测试 condition 为 1 时 ---" << std::endl;
    B b1(1);
    f(b1);

    std::cout << "--- 测试 condition 为 100 时---" << std::endl;
    B b100(100);
    f(b100);

    return 0;
}