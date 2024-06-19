#pragma once

/**
 * noncopyable被继承以后  派生类对象可以进行正常的构造&析构
 * 但是派生类无法进行拷贝和赋值操作
*/
class noncopyable
{
public:
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable) = delete;
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};