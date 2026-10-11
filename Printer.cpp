/****************
Ma sinh vien: 202419074
Ho ten: Vũ Thành Lâm
****************/
#include "Printer.h"

#include <sstream>
#include <stdexcept>

std::string PrinterTypeToString(PrinterType type) {
    switch (type) {
        case PrinterType::Laser:
            return "Laser";
        case PrinterType::Inkjet:
            return "Inkjet";
        default:
            return "Unknown";
    }
}

Printer::Printer(const std::string& deviceId,
                 const std::string& name,
                 int yearPutIntoUse,
                 double purchasePrice,
                 PrinterType printerType,
                 long long pagesPrinted,
                 bool isColor,
                 DeviceStatus status)
    : Device(deviceId, name, yearPutIntoUse, purchasePrice, status),
      printerType_(printerType),
      pagesPrinted_(pagesPrinted),
      isColor_(isColor) {
    if (pagesPrinted_ < 0) {
        throw std::invalid_argument("Printed page count must not be negative.");
    }
}

double Printer::CalculateAnnualMaintenanceCost() const {
    double cost = GetPurchasePrice() * 0.04;
    if (pagesPrinted_ > 100000) {
        cost += 500000;
    }
    if (isColor_) {
        cost += 300000;
    }
    return cost;
}

std::string Printer::ToString() const {
    std::ostringstream output;
    output << Device::ToString()
           << ", PrinterType=" << PrinterTypeToString(printerType_)
           << ", PagesPrinted=" << pagesPrinted_
           << ", Color=" << (isColor_ ? "Yes" : "No")
           << ", NetworkSupported=" << (SupportsNetwork() ? "Yes" : "No");
    return output.str();
}

bool Printer::SupportsNetwork() const { return false; }
