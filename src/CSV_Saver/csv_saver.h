#pragma once

#include "../PhysicsUnits/physics_units.h"

#include <fstream>
#include <vector>


// Saving data in csv format
void SaveDataToCSV(const std::string& filename, const std::vector<std::pair<phycs_units::Torque, phycs_units::CrankshaftSpeed>>& data);