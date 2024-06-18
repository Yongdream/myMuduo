#pragma once
#include "noncopyable.h"

// 定义日志级别 INFO ERROR FATAL DEBUG
enum LogLevel
{
    INFO,   // 普通信息
    ERROR,  // 错误信息
    FATAL,  // 致命信息
    DEBUG,  // 调试信息
};

// 输出一个日志类
class Logger : noncopyable
{
public:
    // 获取日志唯一的实例对象
    static Logger* instance();
    // 设置日志级别

private:
    Logger(){}
    
};
