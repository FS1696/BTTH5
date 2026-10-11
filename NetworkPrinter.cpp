/****************
Ma sinh vien: [DIEN_MSSV]
Ho ten: [DIEN_HO_TEN]
****************/
#include "NetworkPrinter.h"

#include <stdexcept>

NetworkPrinter::NetworkPrinter(const std::string& deviceId,
                               const std::string& name,
                               int yearPutIntoUse,
                               double purchasePrice,
                               PrinterType printerType,
                               long long pagesPrinted,
                               bool isColor,
                               DeviceStatus status)
    : Printer(deviceId, name, yearPutIntoUse, purchasePrice,
              printerType, pagesPrinted, isColor, status),
      ipAddress_(""),
      connected_(false) {}

bool NetworkPrinter::SupportsNetwork() const { return true; }
const std::string& NetworkPrinter::GetIpAddress() const { return ipAddress_; }

void NetworkPrinter::Connect(const std::string& ipAddress) {
    if (ipAddress.find_first_not_of(" \t\n\r") == std::string::npos) {
        throw std::invalid_argument("IP address must not be empty.");
    }
    if (connected_) {
        throw std::logic_error("Device is already connected to the network.");
    }
    ipAddress_ = ipAddress;
    connected_ = true;
}

void NetworkPrinter::Disconnect() {
    connected_ = false;
    ipAddress_.clear();
}

bool NetworkPrinter::IsConnected() const { return connected_; }
