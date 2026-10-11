/****************
Ma sinh vien: 202419074
Ho ten: Vũ Thành Lâm
****************/
#ifndef NETWORKPRINTER_H
#define NETWORKPRINTER_H

#include "Printer.h"
#include "INetworkable.h"
#include <string>

// Chi may in duoc cau hinh mang moi thuc thi INetworkable.
class NetworkPrinter : public Printer, public INetworkable {
public:
    NetworkPrinter(const std::string& deviceId,
                   const std::string& name,
                   int yearPutIntoUse,
                   double purchasePrice,
                   PrinterType printerType,
                   long long pagesPrinted,
                   bool isColor,
                   DeviceStatus status = DeviceStatus::Active);

    bool SupportsNetwork() const override;
    const std::string& GetIpAddress() const override;
    void Connect(const std::string& ipAddress) override;
    void Disconnect() override;
    bool IsConnected() const override;

private:
    std::string ipAddress_;
    bool connected_;
};

#endif // NETWORKPRINTER_H
