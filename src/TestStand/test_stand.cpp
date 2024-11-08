#include "test_stand.h"

namespace test_stand {

std::pair<bool, float_second> RunOverheatingTest(Engine& engine) {
    constexpr double epsilon = 1e-3; // Set smallness for temperature change rate
    float_second total_time(0.0);
    float_second dt(0.1);     // Time step (for example, 0.1 sec)

    while (!engine.IsOverheated()) {
        if (engine.GetTemperatureChangeRate().value_ < epsilon) {
            return std::pair{false, total_time};
        }
        engine.Update(dt);  // Updating the engine status
        total_time += dt;
    }
    return std::pair{true, total_time};
}

std::pair<phycs_units::Power, phycs_units::CrankshaftSpeed> RunMaxPowerTest(Engine& engine) {
    constexpr double epsilon = 1e-9; // Set smallness for torque
    float_second dt(0.1);     // Time step (for example, 0.1 sec)

    phycs_units::Power max_power = engine.GetPower();
    phycs_units::CrankshaftSpeed max_speed = engine.GetSpeed();

    if (!engine.GetTorque().value_ && !engine.GetSpeed()) {
        return std::pair{max_power, max_speed};
    }
        
    while (engine.GetTorque().value_ > epsilon) {
        // Update the maximum power and speed if necessary
        auto current_power = engine.GetPower();
        if (current_power > max_power) {
            max_power = current_power;
            max_speed = engine.GetSpeed();
        }
        engine.Update(dt);
    }
    
    return std::pair{max_power, max_speed};
}

std::vector<std::pair<phycs_units::Torque, phycs_units::CrankshaftSpeed>> RunTorqueSpeedDataCollection(Engine& engine) {
    constexpr double epsilon = 1e-9; // Set smallness for torque
    float_second dt(2.1);            // Time step for simulation

    std::vector<std::pair<phycs_units::Torque, phycs_units::CrankshaftSpeed>> data_points;

    if (!engine.GetTorque().value_ && !engine.GetSpeed()) {
        return data_points;
    }

    while (engine.GetTorque().value_ > epsilon) {
        data_points.emplace_back(engine.GetTorque(), engine.GetSpeed());
        engine.Update(dt);
    }

    return data_points;
}

} // test_stand namespace