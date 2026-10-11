/****************
Ma sinh vien: 202419074
Ho ten: Vũ Thành Lâm
****************/
#include "Device.h"

#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace {
    // Kiem tra chuoi co rong hoac chi chua khoang trang khong.
    bool IsBlank(const std::string& value) {
        return value.find_first_not_of(" \t\n\r") == std::string::npos;
    }
}

int GetCurrentYear() {
    const std::time_t now = std::time(NULL);
    const std::tm* localTime = std::localtime(&now);
    return localTime == NULL ? 2026 : localTime->tm_year + 1900;
}

std::string DeviceStatusToString(DeviceStatus status) {
    switch (status) {
        case DeviceStatus::Active:
            return "Active";
        case DeviceStatus::UnderMaintenance:
            return "UnderMaintenance";
        case DeviceStatus::Retired:
            return "Retired";
        default:
            return "Unknown";
    }
}

Device::Device(const std::string& deviceId,
               const std::string& name,
               int yearPutIntoUse,
               double purchasePrice,
               DeviceStatus status)
    : deviceId_(deviceId),
      name_(name),
      yearPutIntoUse_(yearPutIntoUse),
      purchasePrice_(purchasePrice),
      status_(status) {
    if (IsBlank(deviceId_)) {
        throw std::invalid_argument("Device ID must not be empty.");
    }
    if (IsBlank(name_)) {
        throw std::invalid_argument("Device name must not be empty.");
    }
    if (purchasePrice_ <= 0) {
        throw std::invalid_argument("Purchase price must be greater than 0.");
    }
    if (yearPutIntoUse_ <= 0 || yearPutIntoUse_ > GetCurrentYear()) {
        throw std::invalid_argument("Year put into use is invalid.");
    }
}

Device::~Device() {}

const std::string& Device::GetDeviceId() const { return deviceId_; }
const std::string& Device::GetName() const { return name_; }
int Device::GetYearPutIntoUse() const { return yearPutIntoUse_; }
double Device::GetPurchasePrice() const { return purchasePrice_; }
DeviceStatus Device::GetStatus() const { return status_; }
void Device::SetStatus(DeviceStatus status) { status_ = status; }

bool Device::HasBeenUsedMoreThan(int years) const {
    return GetCurrentYear() - yearPutIntoUse_ > years;
}

bool Device::RequiresMaintenance() const {
    return status_ == DeviceStatus::UnderMaintenance || HasBeenUsedMoreThan(5);
}

std::string Device::ToString() const {
    std::ostringstream output;
    output << "ID=" << deviceId_
           << ", Name=" << name_
           << ", Year=" << yearPutIntoUse_
           << ", PurchasePrice=" << std::fixed << std::setprecision(0)
           << purchasePrice_ << " VND"
           << ", Status=" << DeviceStatusToString(status_);
    return output.str();
}
