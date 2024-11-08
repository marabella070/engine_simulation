#include <iostream>

#include "TestStand/test_stand.h"

#include "JsonReader/json_reader.h"

int main() {
    using namespace phycs_units;

    // Start parameters
    EngineConfig engine_config = LoadConfig("config.json");

    Temperature ambient_temp{0.0};

    std::cout << "Enter the ambient temperature: ";
    std::cin >> ambient_temp;
    std::cout << '\n';

    // Launching the test stand

    { // First test:
        Engine engine(engine_config.inertia_moment, 
                      engine_config.torque_curve, 
                      engine_config.overheating_temp, 
                      engine_config.heating_coeff_by_torque, 
                      engine_config.heating_coeff_by_crankshaft_speed, 
                      engine_config.cooling_coeff, 
                      ambient_temp);
                      
        auto over_heating_result = test_stand::RunOverheatingTest(engine);
        if (over_heating_result.first) {
            std::cout << "The engine overheated after " << over_heating_result.second.count() << " seconds from the start.\n";
        } else {
            std::cout << "The engine has not reached the overheating temperature.\n";
        }
    }

    { // Second test:
        Engine engine(engine_config.inertia_moment, 
                    engine_config.torque_curve, 
                    engine_config.overheating_temp, 
                    engine_config.heating_coeff_by_torque, 
                    engine_config.heating_coeff_by_crankshaft_speed, 
                    engine_config.cooling_coeff, 
                    ambient_temp);
        auto result = test_stand::RunMaxPowerTest(engine);
        std::cout << "Max power: " << (result.first / 1000) << " kW\n";
        std::cout << "Crankshaft speed at maximum power: " << result.second << " rad/sec\n";
    }

    return 0;
}