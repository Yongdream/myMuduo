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
    ~Channel();

    // fd得到poller通知以后 处理事件
    void handleEvent(Timestamp receiveTime);

    // 设置回调函数对象
    // 使用 std::move 将参数 cb 转换为右值引用，从而调用移动构造函数或移动赋值运算符
    void setReadCallback(ReadEventCallback cb) {readCallback_ = std::move(cb);}
    void setWriteCallback(EventCallback cb) {writeCallbcak_ = std::move(cb);}
    void setCloseCallback(EventCallback cb) {closeCallback_ = std::move(cb);}
    void setErrorCallback(EventCallback cb) {errorCallback_ = std::move(cb);}

    // 防止当 channel 被手动 remove，channel还在执行以上的回调操作
    void tie(const std::shared_ptr<void> &);

    int fd() const {return fd_;}
    int events() const {return events_;}            // fd感兴趣的事件
    int set_revents(int revt) {revents_ = revt;}    // poller监听事件 设置了channel的fd相应事件
    

    // 设置fd相应的事件状态
    void enableReading() {events_ |= kReadEvent; update();}     // 位赋值 或
    void disableReading() {events_ &= ~kReadEvent; update();}   // 位取消 取反再与
    void enableWriting() {events_ |= kWriteEvent; update();}
    void disableWriting() {events_ &= kWriteEvent; update();}

    // 返回fd当前的事件状态
    bool isNoneEvent() const {return events_ == kNoneEvent;}
    bool isWriting() const {return events_ == kWriteEvent;}
    bool isReading() const {return events_ == kReadEvent;}

    int index() {return index_;}
    void set_index(int idx) {index_ = idx;}

    // one loop per thread
    EventLoop* ownerLoop() {return loop_;}
    
    // 删除channel
    void remove();


private:
    // 更新 内部对象调用
    void update();

    // 处理受保护的处理事件
    void handleEventWithGuard(Timestamp receiveTime);

    // 感兴趣事件类型
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;   // 事件循环
    const int fd_;      // fd，poller监听的对象
    int events_;        // 注册fd感兴趣的对象
    int revents_;        // poller返回具体发生事件
    int index_;
    bool logHup_;

    std::weak_ptr<void> tie_;   // 「weak_ptr」解决共享资源的循环引用问题
    bool tied_;
    bool eventHandling_;
    bool addedToLoop_;

    // 只有Channel通道里面能够获知fd最终发生的具体事件revents
    // 因此，负责回调具体事件的回调操作
    EventCallback writeCallbcak_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
    ReadEventCallback readCallback_;
};

