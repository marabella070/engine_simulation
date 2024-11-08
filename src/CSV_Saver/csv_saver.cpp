#include "csv_saver.h"

void SaveDataToCSV(const std::string& filename, const std::vector<std::pair<phycs_units::Torque, phycs_units::CrankshaftSpeed>>& data) {
    std::ofstream file(filename);
    file << "Torque,Speed\n";
    for (const auto& [torque, speed] : data) {
        file << torque.value_ << "," << speed.value_ << "\n";
    }
    file.close();
}