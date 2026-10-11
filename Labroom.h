/****************
Ma sinh vien: 202419074
Ho ten: Vũ Thành Lâm
****************/
#ifndef LABROOM_H
#define LABROOM_H

#include "Device.h"
#include <string>
#include <vector>

// Phong chi luu con tro khong so huu den Device: day la quan he ket tap.
class LabRoom {
public:
    LabRoom(const std::string& roomId,
            const std::string& name,
            std::size_t capacity);

    // Nem ngoai le neu con tro null, trung ma hoac phong da day.
    void AddDevice(Device* device);
    bool RemoveDevice(const std::string& deviceId);
    Device* FindDevice(const std::string& deviceId) const;
    double CalculateAnnualMaintenanceCost() const;
    std::vector<Device*> GetDevicesRequiringMaintenance() const;

    const std::string& GetRoomId() const;
    const std::string& GetName() const;
    std::size_t GetCapacity() const;
    const std::vector<Device*>& GetDevices() const;

private:
    std::string roomId_;
    std::string name_;
    std::size_t capacity_;
    std::vector<Device*> devices_; // Con tro khong so huu; khong delete cac Device.
};

#endif // LABROOM_H
