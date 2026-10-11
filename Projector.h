/****************
Ma sinh vien: [DIEN_MSSV]
Ho ten: [DIEN_HO_TEN]
****************/
#ifndef PROJECTOR_H
#define PROJECTOR_H

#include "Device.h"

// May chieu khong thuc thi INetworkable trong phien ban bai tap nay.
class Projector : public Device {
public:
    Projector(const std::string& deviceId,
              const std::string& name,
              int yearPutIntoUse,
              double purchasePrice,
              int brightnessLumens,
              long long lampHoursUsed,
              DeviceStatus status = DeviceStatus::Active);

    double CalculateAnnualMaintenanceCost() const override;
    std::string ToString() const override;

private:
    int brightnessLumens_;
    long long lampHoursUsed_;
};

#endif // PROJECTOR_H
