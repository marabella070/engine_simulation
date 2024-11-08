#include "engine.h"

#include <algorithm>

// ----------------------- class Engine Implementation -----------------------
Engine::Engine(phycs_units::InertiaMoment i,
                const std::vector<std::pair<phycs_units::Torque, phycs_units::CrankshaftSpeed>>& torgue_curve,
                phycs_units::Temperature over_temp, 
                double torque_coeff, 
                double crankshaft_coeff, 
                double cool_coeff,
                phycs_units::Temperature amb_temp) 
    : I(i), 
        M_curve(torgue_curve), 
        overheating_temp(over_temp), 
        heating_coeff_by_torque(torque_coeff), 
        heating_coeff_by_crankshaft_speed(crankshaft_coeff),  
        cooling_coeff(cool_coeff), 
        ambient_temp(amb_temp), 
        M(0), 
        V(0), 
        heating_speed(0), 
        cooling_speed(0), 
        current_temp(ambient_temp) {

    if (M_curve.empty()) {
        throw std::invalid_argument("Torque curve cannot be empty.");
    }
    M = M_curve[0].first;
    V = M_curve[0].second;

    heating_speed.value_ = CalculateHeatingSpeed();
    cooling_speed.value_ = CalculateCoolingSpeed();
}

void Engine::Update(float_second dt) {
    // Convert the time `dt` to seconds
    double dt_seconds = dt.count();

    // Step 1: Calculate the acceleration and speed change
    double acceleration = M.value_ / I.value_;
    V.value_ = V.value_ + acceleration * dt_seconds;

    // Update the torque depending on the new speed
    M = CalculateTorqueFromSpeed(V);

    // Step 2: Update Engine Tempreture

    // Calculating new engine temperature speeds
    double d_heat_temp = heating_speed.value_ * dt_seconds;
    double d_cool_temp = cooling_speed.value_ * dt_seconds;

    // update engine tempreture
    current_temp.value_ += d_heat_temp + d_cool_temp;

    // update speeds
    heating_speed.value_ = CalculateHeatingSpeed();
    cooling_speed.value_ = CalculateCoolingSpeed();
}

phycs_units::CrankshaftSpeed Engine::GetSpeed() const { return V; }
phycs_units::Torque Engine::GetTorque() const { return M; }
phycs_units::Power Engine::GetPower() const { return phycs_units::Power{M.value_ * V.value_}; }
phycs_units::Temperature Engine::GetTemperature() const { return current_temp; }
phycs_units::Speed Engine::GetTemperatureChangeRate() const { return heating_speed + cooling_speed; }

bool Engine::IsOverheated() const { return current_temp >= overheating_temp; }

double Engine::CalculateHeatingSpeed() const {
    return (M.value_ * heating_coeff_by_torque) + ((V.value_ * V.value_) * heating_coeff_by_crankshaft_speed);
}

double Engine::CalculateCoolingSpeed() const {
    return cooling_coeff * (ambient_temp.value_ - current_temp.value_);
}

phycs_units::Torque Engine::CalculateTorqueFromSpeed(const phycs_units::CrankshaftSpeed& V) {
    auto it = std::lower_bound(M_curve.begin(), M_curve.end(), V,
                            [](const std::pair<phycs_units::Torque, phycs_units::CrankshaftSpeed>& entry, 
                                const phycs_units::CrankshaftSpeed& speed) {
                                return entry.second < speed;
                            });

    phycs_units::Torque result{0.0};

    if (it == M_curve.begin()) {
        // If the current speed is below the minimum value on the graph
        result = M_curve.front().first;
    } else if (it == M_curve.end()) {
        // If the current speed is higher than the maximum value on the graph
        result = M_curve.back().first;
    } else {
        // Otherwise, we interpolate the moment M by the velocity
        auto [M1, V1] = *(it - 1);
        auto [M2, V2] = *it;
        double t = static_cast<double>(V - V1) / static_cast<double>(V2 - V1);
        result.value_ = M1.value_ + ((M2.value_ - M1.value_) * t);
    }
    return result;
}