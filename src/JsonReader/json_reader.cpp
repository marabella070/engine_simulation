#include "../JsonReader/json_reader.h"

#include <fstream>

using json = nlohmann::json;

EngineConfig LoadConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("The configuration file could not be opened");
    }

    json config_json;
    file >> config_json;

    EngineConfig config;

    // Converting data from JSON to units of measurement
    config.inertia_moment = phycs_units::InertiaMoment{config_json.at("inertia_moment").get<double>()};
    config.overheating_temp = phycs_units::Temperature{config_json.at("overheating_temp").get<double>()};
    config.heating_coeff_by_torque = config_json.at("heating_coeff_by_torque").get<double>();
    config.heating_coeff_by_crankshaft_speed = config_json.at("heating_coeff_by_crankshaft_speed").get<double>();
    config.cooling_coeff = config_json.at("cooling_coeff").get<double>();

    for (const auto& point : config_json.at("torque_curve")) {
        phycs_units::Torque torque = phycs_units::Torque{point.at("torque").get<double>()};
        phycs_units::CrankshaftSpeed speed = phycs_units::CrankshaftSpeed{point.at("speed").get<double>()};
        config.torque_curve.emplace_back(torque, speed);
    }

    return config;
}