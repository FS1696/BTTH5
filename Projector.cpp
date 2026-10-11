/****************
Ma sinh vien: 202419074
Ho ten: Vũ Thành Lâm
****************/
#include "Projector.h"

#include <sstream>
#include <stdexcept>

Projector::Projector(const std::string& deviceId,
                     const std::string& name,
                     int yearPutIntoUse,
                     double purchasePrice,
                     int brightnessLumens,
                     long long lampHoursUsed,
                     DeviceStatus status)
    : Device(deviceId, name, yearPutIntoUse, purchasePrice, status),
      brightnessLumens_(brightnessLumens),
      lampHoursUsed_(lampHoursUsed) {
    if (brightnessLumens_ <= 0) {
        throw std::invalid_argument("Projector brightness must be greater than 0.");
    }
    if (lampHoursUsed_ < 0) {
        throw std::invalid_argument("Lamp usage hours must not be negative.");
    }
}

double Projector::CalculateAnnualMaintenanceCost() const {
    double cost = GetPurchasePrice() * 0.03;
    if (lampHoursUsed_ > 3000) {
        cost += 1500000;
    }
    return cost;
}

std::string Projector::ToString() const {
    std::ostringstream output;
    output << Device::ToString()
           << ", Brightness=" << brightnessLumens_ << " lumens"
           << ", LampHours=" << lampHoursUsed_;
    return output.str();
