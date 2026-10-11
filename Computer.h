/****************
Ma sinh vien: [DIEN_MSSV]
Ho ten: [DIEN_HO_TEN]
****************/
#ifndef COMPUTER_H
#define COMPUTER_H

#include "Device.h"
#include "INetworkable.h"
#include <string>

// May tinh la Device va luon co kha nang ket noi mang.
class Computer : public Device, public INetworkable {
public:
    Computer(const std::string& deviceId,
             const std::string& name,
             int yearPutIntoUse,
             double purchasePrice,
             int ramGB,
             const std::string& processorType,
             bool hasDedicatedGPU,
             DeviceStatus status = DeviceStatus::Active);

    double CalculateAnnualMaintenanceCost() const override;
    std::string ToString() const override;

    const std::string& GetIpAddress() const override;
    void Connect(const std::string& ipAddress) override;
    void Disconnect() override;
    bool IsConnected() const override;

private:
    int ramGB_;
    std::string processorType_;
    bool hasDedicatedGPU_;
    std::string ipAddress_;
    bool connected_;
};

#endif // COMPUTER_H
