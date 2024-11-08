#pragma once

#include "../Engine/engine.h"

#include <optional>

namespace test_stand {
    // 1. Overheating test
    std::pair<bool, float_second> RunOverheatingTest(Engine& engine);

    // 2. Maximum power test
    std::pair<phycs_units::Power, phycs_units::CrankshaftSpeed> RunMaxPowerTest(Engine& engine);

    // 3. // Function collects the values of M and V at each step of the simulation and stores them in an array:
    std::vector<std::pair<phycs_units::Torque, phycs_units::CrankshaftSpeed>> RunTorqueSpeedDataCollection(Engine& engine);

} // test_stand namespace