/****************
Ma sinh vien: [DIEN_MSSV]
Ho ten: [DIEN_HO_TEN]
****************/
#include "Computer.h"

#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace {
    bool IsBlankComputer(const std::string& value) {
        return value.find_first_not_of(" \t\n\r") == std::string::npos;
    }
}

Computer::Computer(const std::string& deviceId,
                   const std::string& name,
                   int yearPutIntoUse,
                   double purchasePrice,
                   int ramGB,
                   const std::string& processorType,
                   bool hasDedicatedGPU,
                   DeviceStatus status)
    : Device(deviceId, name, yearPutIntoUse, purchasePrice, status),
      ramGB_(ramGB),
      processorType_(processorType),
      hasDedicatedGPU_(hasDedicatedGPU),
      ipAddress_(""),
      connected_(false) {
    if (ramGB_ <= 0) {
        throw std::invalid_argument("RAM must be greater than 0.");
    }
    if (IsBlankComputer(processorType_)) {
        throw std::invalid_argument("Processor type must not be empty.");
    }
}

double Computer::CalculateAnnualMaintenanceCost() const {
    double rate = 0.05;
    if (hasDedicatedGPU_) {
        rate += 0.02;
    }
    if (HasBeenUsedMoreThan(5)) {
        rate += 0.01;
    }
    return GetPurchasePrice() * rate;
}

std::string Computer::ToString() const {
    std::ostringstream output;
    output << Device::ToString()
           << ", RAM=" << ramGB_ << " GB"
           << ", CPU=" << processorType_
           << ", DedicatedGPU=" << (hasDedicatedGPU_ ? "Yes" : "No")
           << ", Network=" << (connected_ ? "Connected" : "Disconnected");
    return output.str();
}

const std::string& Computer::GetIpAddress() const { return ipAddress_; }

void Computer::Connect(const std::string& ipAddress) {
    if (ipAddress.find_first_not_of(" \t\n\r") == std::string::npos) {
        throw std::invalid_argument("IP address must not be empty.");
    }
    if (connected_) {
        throw std::logic_error("Device is already connected to the network.");
    }
    ipAddress_ = ipAddress;
    connected_ = true;
}

void Computer::Disconnect() {
    connected_ = false;
    ipAddress_.clear();
}

bool Computer::IsConnected() const { return connected_; }
