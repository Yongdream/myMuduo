#pragma once
#include "noncopyable.h"
#include "Timestamp.h"
#include <functional>
#include <memory>   // 包含std::weak_ptr

class EventLoop;    // 只用到类型声明 没有具体实现方法 只需要类型前置声明

/**
 * Channel可以理解成通道
 * 1. 封装sockfd和其他感兴趣的event 例如EPOLLIN EPOLLOUT实践
 * 2. 绑定poller返回额具体事件
*/

class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>;                // 事件回调
    using ReadEventCallback = std::function<void(Timestamp)>;   // 只读事件回调
    Channel(EventLoop *loop, int fd);
    ~Channel( );

    void handleEvent(Timestamp receiveTime);

private:
    // 感兴趣事件类型
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;   // 事件循环
    const int fd_;      // fd，poller监听的对象
    int event_;         // 注册fd感兴趣的对象
    int revent_;        // poller返回具体发生事件
    int index_;
    bool logHup_;

    std::weak_ptr<void> tie_;   // 「weak_ptr」解决共享资源的循环引用问题
    bool tied_;
    bool eventHandling_;
    bool addedToLoop_;

    // Channel通道里面能够获知fd最终发生的具体事件revents
    // 因此，负责回调具体事件的回调操作
    EventCallback writeCallbcak_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
    ReadEventCallback readCallback_;
};

