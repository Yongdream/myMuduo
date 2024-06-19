#include "InetAddress.h"
#include <string.h> // 包含bzero和memset

InetAddress::InetAddress(uint16_t port, std::string ip)
{
    memset(&addr_, 0, sizeof addr_);
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = inet_addr(ip.c_str()); // 转成网络字节
}

// 打印ip地址
std::string InetAddress::toIp() const   
{
    // 网络字节->本地字节
    char buf[64] = {0};
    // 「inet_ntop」是一个将网络地址转换为文本字符串的函数
    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
    return buf;
}

std::string InetAddress::toIpPort() const
{
    // 返回 「ip:port」
    char buf[64] = {0};
    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
    size_t end = strlen(buf);
    uint16_t port = ntohs(addr_.sin_port);
    sprintf(buf+end, ":%u", port);
    return buf;
}

uint16_t InetAddress::toPort() const
{
    // 返回 「port」
    return ntohs(addr_.sin_port);
}

// # include<iostream>
// int main()
// {
//     InetAddress addr(8080);
//     std::cout << addr.toIpPort() << std::endl;
//     return 0;
// }

