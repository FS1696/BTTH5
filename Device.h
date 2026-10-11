/****************
Ma sinh vien: 202419074
Ho ten: Vũ Thành Lâm
****************/
#ifndef DEVICE_H
#define DEVICE_H

#include <string>

// Trang thai hien tai cua thiet bi.
enum class DeviceStatus {
    Active,
    UnderMaintenance,
    Retired
};

// Chuyen trang thai thanh chuoi de hien thi.
std::string DeviceStatusToString(DeviceStatus status);

// Tra ve nam hien tai cua he thong.
int GetCurrentYear();

// Lop co so truu tuong cho moi loai thiet bi.
class Device {
public:
    Device(const std::string& deviceId,
           const std::string& name,
           int yearPutIntoUse,
           double purchasePrice,
           DeviceStatus status = DeviceStatus::Active);
    virtual ~Device();

    const std::string& GetDeviceId() const;
    const std::string& GetName() const;
    int GetYearPutIntoUse() const;
    double GetPurchasePrice() const;
    DeviceStatus GetStatus() const;
    void SetStatus(DeviceStatus status);

    // Thoi gian su dung lon hon so nam truyen vao hay khong.
    bool HasBeenUsedMoreThan(int years) const;

    // Can bao tri neu dang bao tri hoac da su dung tren 5 nam.
    bool RequiresMaintenance() const;

    // Moi lop con phai tu cai dat cach tinh chi phi bao tri.
    virtual double CalculateAnnualMaintenanceCost() const = 0;

    // Ham ao de cac lop con bo sung thong tin rieng.
    virtual std::string ToString() const;

protected:
    // const dam bao ma thiet bi khong the thay doi sau khi khoi tao.
    const std::string deviceId_;
    std::string name_;
    int yearPutIntoUse_;
    double purchasePrice_;
    DeviceStatus status_;
};

#endif // DEVICE_H
