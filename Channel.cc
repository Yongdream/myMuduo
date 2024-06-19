#include "Channel.h"
#include "EventLoop.h"
#include "Logger.h"

#include <sys/epoll.h>  // epoll的表示


// 感兴趣事件类型
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI; // epoll的表示
const int Channel::kWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop)
    , fd_(fd)
    , events_(0)
    , revents_(0)
    , index_(-1)
    , tied_(false)
    {}

Channel::~Channel(){}

// 防止当 channel 被手动 remove，channel还在执行以上的回调操作
void Channel::tie(const std::shared_ptr<void> &obj)
{
    tie_ = obj;
    tied_ = true;
}

// 更新 内部对象调用
/**
 * 改变channel所表示的fd事件后
 * update()负责再poller里面更改fd相应事件的epoll_crl
 * EventLoop 包含ChannelList Poller
*/
void Channel::update()
{
    // 通过channel所属的EventLoop 调用poller的相应方法 注册fd的events事件
    // pending
    // loop_->updateChannel(this);
}

// 在channel所属的EventLoop 把当前的channel删除掉
void Channel:: remove()
{
    // pengding
    // loop_->removeChannel(this);
}

// fd得到poller通知以后 处理事件
void Channel::handleEvent(Timestamp receiveTime)
{
    if(tied_)
    {   
        // 通过调用 lock 方法将 std::weak_ptr 转换为 std::shared_ptr
        // 弱引用转换为强引用
        std::shared_ptr<void> guard = tie_.lock();
        if (guard)
        {
            handleEventWithGuard(receiveTime);
        }
    }
    else
    {
        handleEventWithGuard(receiveTime);
    }
}

/**
 * 根据poller通知的channel发生的具体事件
 * 由channel 负责回调具体的回调操作
*/ 
void Channel::handleEventWithGuard(Timestamp receiveTime)
{  
    LOG_INFO("Channel handleEvent revents:%d\n", revents_);
    
    // 发生异常
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        
        if (closeCallback_)
        {
            closeCallback_();
        }
    }

    // 错误事件
    if (revents_ & EPOLLERR)
    {
        if(errorCallback_)
        {
            errorCallback_();
        }
    }

    // 只读事件
    if (revents_ & (EPOLLIN | EPOLLPRI))
    {
        if (readCallback_)
        {
            readCallback_(receiveTime);
        }
    }

    // 可写事件
    if (revents_ & EPOLLOUT)
    {
        if (writeCallbcak_)
        {
            writeCallbcak_();
        }
    }
}