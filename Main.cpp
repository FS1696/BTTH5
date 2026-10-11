/****************
Ma sinh vien: 202419074
Ho ten: Vũ Thành Lâm
****************/
#include "Computer.h"
#include "LabRoom.h"
#include "NetworkPrinter.h"
#include "Printer.h"
#include "Projector.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// In danh sach thiet bi cua mot phong.
void PrintRoomDevices(const LabRoom& room) {
    std::cout << "\n--- " << room.GetRoomId() << " - " << room.GetName()
              << " (" << room.GetDevices().size() << "/" << room.GetCapacity() << ") ---\n";
    for (std::size_t i = 0; i < room.GetDevices().size(); ++i) {
        std::cout << i + 1 << ". " << room.GetDevices()[i]->ToString() << "\n";
    }
}

void PrintDevicesRequiringMaintenance(const LabRoom& room) {
    const std::vector<Device*> devices = room.GetDevicesRequiringMaintenance();
    std::cout << "\nThiet bi can bao tri tai " << room.GetName() << ":\n";
    if (devices.empty()) {
        std::cout << "  Khong co.\n";
        return;
    }
    for (std::size_t i = 0; i < devices.size(); ++i) {
        std::cout << "  - " << devices[i]->GetDeviceId() << " - "
                  << devices[i]->GetName() << "\n";
    }
}

int main() {
    try {
        // Tao 5 thiet bi theo yeu cau de bai.
        Computer computer1("PC001", "Dell OptiPlex", 2018, 15000000,
                           16, "Intel Core i5", true, DeviceStatus::Active);
        Computer computer2("PC002", "Lenovo ThinkCentre", 2024, 12000000,
                           16, "Intel Core i5", false, DeviceStatus::Active);
        Printer printer1("PR001", "HP Color LaserJet", 2023, 3500000,
                         PrinterType::Laser, 25000, true, DeviceStatus::UnderMaintenance);
        NetworkPrinter printer2("PR002", "Canon Network Inkjet", 2017, 6000000,
                                PrinterType::Inkjet, 120500, true, DeviceStatus::Active);
        Projector projector1("PJ001", "Epson Projector", 2020, 9000000,
                             3600, 3400, DeviceStatus::Active);

        // Hai phong co suc chua toi da 3 thiet bi moi phong.
        LabRoom room1("LAB101", "Phong thuc hanh A", 3);
        LabRoom room2("LAB102", "Phong thuc hanh B", 3);

        room1.AddDevice(&computer1);
        room1.AddDevice(&printer1);
        room1.AddDevice(&projector1);
        room2.AddDevice(&computer2);
        room2.AddDevice(&printer2);

        // Kiem thu: them mot thiet bi co ma trung trong cung phong.
        Computer duplicateComputer("PC001", "May tinh trung ma", 2023, 10000000,
                                   8, "Intel Core i3", false, DeviceStatus::Active);
        std::cout << "=== KIEM THU THEM THIET BI TRUNG MA ===\n";
        try {
            room1.AddDevice(&duplicateComputer);
            std::cout << "LOI: Da them thiet bi trung ma.\n";
        } catch (const std::exception& error) {
            std::cout << "Tu choi dung: " << error.what() << "\n";
        }

        // In danh sach va chi phi bao tri cua tung phong.
        std::cout << "\n=== DANH SACH THIET BI ===\n";
        PrintRoomDevices(room1);
        PrintRoomDevices(room2);

        std::cout << std::fixed << std::setprecision(0);
        std::cout << "\n=== CHI PHI BAO TRI DU KIEN (VND/NAM) ===\n";
        std::cout << room1.GetName() << ": "
                  << room1.CalculateAnnualMaintenanceCost() << " VND\n";
        std::cout << room2.GetName() << ": "
                  << room2.CalculateAnnualMaintenanceCost() << " VND\n";

        // Thiet bi can bao tri: UnderMaintenance hoac da dung tren 5 nam.
        std::cout << "\n=== THIET BI CAN BAO TRI ===\n";
        PrintDevicesRequiringMaintenance(room1);
        PrintDevicesRequiringMaintenance(room2);

        // Duyet thiet bi mang qua interface, khong phu thuoc lop cu the.
        std::cout << "\n=== KET NOI MANG QUA INetworkable ===\n";
        std::vector<LabRoom*> rooms;
        rooms.push_back(&room1);
        rooms.push_back(&room2);
        int host = 10;
        INetworkable* firstNetworkDevice = NULL;
        for (std::size_t r = 0; r < rooms.size(); ++r) {
            const std::vector<Device*>& devices = rooms[r]->GetDevices();
            for (std::size_t d = 0; d < devices.size(); ++d) {
                INetworkable* networkDevice = dynamic_cast<INetworkable*>(devices[d]);
                if (networkDevice != NULL) {
                    const std::string ip = "192.168.1." + std::to_string(host++);
                    networkDevice->Connect(ip);
                    std::cout << devices[d]->GetDeviceId() << " ket noi IP "
                              << networkDevice->GetIpAddress() << "\n";
                    if (firstNetworkDevice == NULL) {
                        firstNetworkDevice = networkDevice;
                    }
                }
            }
        }

        // Kiem thu khong cho ket noi lai khi dang ket noi.
        std::cout << "\n=== KIEM THU TRANG THAI KET NOI ===\n";
        if (firstNetworkDevice != NULL) {
            try {
                firstNetworkDevice->Connect("192.168.1.99");
                std::cout << "LOI: Cho phep ket noi lai.\n";
            } catch (const std::logic_error& error) {
                std::cout << "Tu choi ket noi lai dung: " << error.what() << "\n";
            }
            firstNetworkDevice->Disconnect();
            std::cout << "Sau khi ngat ket noi: IsConnected="
                      << (firstNetworkDevice->IsConnected() ? "true" : "false")
                      << ", IP='" << firstNetworkDevice->GetIpAddress() << "'\n";
        }

        // Kiem tra tim kiem va xoa thiet bi.
        std::cout << "\n=== KIEM THU TIM KIEM / XOA ===\n";
        Device* found = room2.FindDevice("PR002");
        std::cout << "Tim PR002: " << (found != NULL ? "Tim thay" : "Khong thay") << "\n";
        std::cout << "Xoa ma khong ton tai XXX: "
                  << (room2.RemoveDevice("XXX") ? "Thanh cong" : "That bai") << "\n";

    } catch (const std::exception& error) {
        std::cerr << "Loi chuong trinh: " << error.what() << "\n";
        return 1;
    }
    return 0;
}
