/****************
Ma sinh vien: 202419074
Ho ten: Vũ Thành Lâm
****************/
#ifndef PRINTER_H
#define PRINTER_H

#include "Device.h"
#include <string>

enum class PrinterType {
    Laser,
    Inkjet
};

std::string PrinterTypeToString(PrinterType type);

// May in thong thuong khong nhat thiet phai co mang.
class Printer : public Device {
public:
    Printer(const std::string& deviceId,
            const std::string& name,
            int yearPutIntoUse,
            double purchasePrice,
            PrinterType printerType,
            long long pagesPrinted,
            bool isColor,
            DeviceStatus status = DeviceStatus::Active);

    double CalculateAnnualMaintenanceCost() const override;
    std::string ToString() const override;
    virtual bool SupportsNetwork() const;

protected:
    PrinterType printerType_;
    long long pagesPrinted_;
    bool isColor_;
};

#endif // PRINTER_H
