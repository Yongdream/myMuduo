#include<iostream>
#include<string>

#include "Logger.h"

// 获取日志唯一的实例对象
Logger& Logger::instance()
{
    static Logger logger;
    return logger;
}

// 设置日志级别
void Logger::setLogLevel(int level)
{
    LogLevel_ = level;
}

// 写日志 <级别信息> time : msg
void Logger::log(std::string msg)
{
    switch (LogLevel_)
    {
    case INFO:
        std::cout<< "<INFO>";
        break;
    case ERROR:
        std::cout<< "<ERROR>";
        break;
    case FATAL:
        std::cout<< "<FATAL>";
        break;
    case DEBUG:
        std::cout<< "<DEBUG>";
        break;
    // Timestamp
    default:
        break;

    std::cout << "print time" << " : " << msg << std::endl;
    }

}