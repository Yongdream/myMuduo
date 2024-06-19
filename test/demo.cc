#include <iostream>
#include <string>

class Person {
public:
    // 构造函数，使用成员「初始化列表」初始化 name 和 age
    explicit Person(const std::string &name, int age)
        : name_(name), age_(age) {}

    // 打印 Person 的信息
    void print() const {
        std::cout << "Name: " << name_ << ", Age: " << age_ << std::endl;
    }

private:
    std::string name_;
    int age_;
};

int main() {
    // 创建一个 Person 对象，并初始化 name 和 age
    Person person("Alice", 30);
    
    // 打印 Person 的信息
    person.print();

    return 0;
}
