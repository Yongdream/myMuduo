#pragma once

#include<iostream>

class Timestamp
{
public:
    Timestamp();
    // 带参数的构造加explicit 防止隐式转换
    explicit Timestamp(int64_t microSecondsSinceEpoch);
    
    static Timestamp now();
    std::string toString() const;
private:
    int64_t microSecondsSinceEpoch_;
};
