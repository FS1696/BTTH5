/****************
Ma sinh vien: 202419074
Ho ten: Vũ Thành Lâm
****************/
#ifndef INETWORKABLE_H
#define INETWORKABLE_H

#include <string>

// Interface mo ta nang luc ket noi mang, khong phu thuoc vao loai thiet bi.
class INetworkable {
public:
    virtual ~INetworkable() {}
    virtual const std::string& GetIpAddress() const = 0;
    virtual void Connect(const std::string& ipAddress) = 0;
    virtual void Disconnect() = 0;
    virtual bool IsConnected() const = 0;
};

#endif // INETWORKABLE_H
