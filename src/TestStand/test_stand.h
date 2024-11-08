#pragma once

#include "../Engine/engine.h"

#include <optional>

namespace test_stand {
    // 1. Overheating test
    std::pair<bool, float_second> RunOverheatingTest(Engine& engine);

    // 2. Maximum power test
    std::pair<phycs_units::Power, phycs_units::CrankshaftSpeed> RunMaxPowerTest(Engine& engine);

} // test_stand namespace