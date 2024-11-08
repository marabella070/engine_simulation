#pragma once 

#include "../json.hpp"

#include "../PhysicsUnits/physics_units.h"

// Structure for storing engine data
struct EngineConfig {
    phycs_units::InertiaMoment inertia_moment;
    std::vector<std::pair<phycs_units::Torque, phycs_units::CrankshaftSpeed>> torque_curve;
    phycs_units::Temperature overheating_temp;
    double heating_coeff_by_torque;
    double heating_coeff_by_crankshaft_speed;
    double cooling_coeff;
};

// Function for loading configuration from a JSON file
EngineConfig LoadConfig(const std::string& filename);