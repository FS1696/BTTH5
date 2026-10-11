/****************
Ma sinh vien: 202419074
Ho ten: Vũ Thành Lâm
****************/
#include "LabRoom.h"

#include <algorithm>
#include <stdexcept>

namespace {
    bool IsBlankRoomValue(const std::string& value) {
        return value.find_first_not_of(" \t\n\r") == std::string::npos;
    }
}

LabRoom::LabRoom(const std::string& roomId,
                 const std::string& name,
                 std::size_t capacity)
    : roomId_(roomId), name_(name), capacity_(capacity) {
    if (IsBlankRoomValue(roomId_)) {
        throw std::invalid_argument("Room ID must not be empty.");
    }
    if (IsBlankRoomValue(name_)) {
        throw std::invalid_argument("Room name must not be empty.");
    }
    if (capacity_ == 0) {
        throw std::invalid_argument("Room capacity must be greater than 0.");
    }
}

void LabRoom::AddDevice(Device* device) {
    if (device == NULL) {
        throw std::invalid_argument("Cannot add a null device.");
    }
    if (FindDevice(device->GetDeviceId()) != NULL) {
        throw std::logic_error("A device with this ID already exists in the room.");
    }
    if (devices_.size() >= capacity_) {
        throw std::logic_error("The room has reached its capacity.");
    }
    devices_.push_back(device);
}

bool LabRoom::RemoveDevice(const std::string& deviceId) {
    std::vector<Device*>::iterator it = std::find_if(
        devices_.begin(), devices_.end(),
        [&deviceId](Device* device) { return device->GetDeviceId() == deviceId; });
    if (it == devices_.end()) {
        return false;
    }
    devices_.erase(it);
    return true;
}

Device* LabRoom::FindDevice(const std::string& deviceId) const {
    for (std::size_t i = 0; i < devices_.size(); ++i) {
        if (devices_[i]->GetDeviceId() == deviceId) {
            return devices_[i];
        }
    }
    return NULL;
}

double LabRoom::CalculateAnnualMaintenanceCost() const {
    double total = 0;
    // Goi ham ao tren Device*: C++ tu chon ham cua lop thuc te (da hinh).
    for (std::size_t i = 0; i < devices_.size(); ++i) {
        total += devices_[i]->CalculateAnnualMaintenanceCost();
    }
    return total;
}

std::vector<Device*> LabRoom::GetDevicesRequiringMaintenance() const {
    std::vector<Device*> result;
    for (std::size_t i = 0; i < devices_.size(); ++i) {
        if (devices_[i]->RequiresMaintenance()) {
            result.push_back(devices_[i]);
        }
    }
    return result;
}

const std::string& LabRoom::GetRoomId() const { return roomId_; }
const std::string& LabRoom::GetName() const { return name_; }
std::size_t LabRoom::GetCapacity() const { return capacity_; }
const std::vector<Device*>& LabRoom::GetDevices() const { return devices_; }
