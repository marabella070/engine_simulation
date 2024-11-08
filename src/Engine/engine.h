#pragma once

#include <chrono>
#include <vector>

#include "../PhysicsUnits/physics_units.h"

using float_second = std::chrono::duration<double>;

// Abstract base class for engines
class BaseEngine {
public:
    virtual ~BaseEngine() = default;

    // Updates the engine status during dt
    virtual void Update(float_second dt) = 0;

    // Getting the current engine characteristics
    virtual phycs_units::CrankshaftSpeed GetSpeed() const = 0;
    virtual phycs_units::Torque GetTorque() const = 0;
    virtual phycs_units::Power GetPower() const = 0;
    virtual phycs_units::Temperature GetTemperature() const = 0;
    virtual phycs_units::Speed GetTemperatureChangeRate() const = 0;

    // Check for overheating
    virtual bool IsOverheated() const = 0;
};

// Four-stroke engine
class Engine : public BaseEngine {
public:
    explicit Engine(phycs_units::InertiaMoment i,
                    const std::vector<std::pair<phycs_units::Torque, phycs_units::CrankshaftSpeed>>& torgue_curve,
                    phycs_units::Temperature over_temp, 
                    double torque_coeff, 
                    double crankshaft_coeff, 
                    double cool_coeff,
                    phycs_units::Temperature amb_temp);

    void Update(float_second dt);
    phycs_units::CrankshaftSpeed GetSpeed() const;
    phycs_units::Torque GetTorque() const;
    phycs_units::Power GetPower() const;
    phycs_units::Temperature GetTemperature() const;
    phycs_units::Speed GetTemperatureChangeRate() const;
    bool IsOverheated() const;

private:
    // Method for calculating the engine heating speed
    double CalculateHeatingSpeed() const;

    // Method for calculating engine cooling speed
    double CalculateCoolingSpeed() const;

    phycs_units::Torque CalculateTorqueFromSpeed(const phycs_units::CrankshaftSpeed& V);

private:
    // Engine Characteristics:
    phycs_units::InertiaMoment I;
    std::vector<std::pair<phycs_units::Torque, phycs_units::CrankshaftSpeed>> M_curve;
    phycs_units::Temperature overheating_temp;
    double heating_coeff_by_torque;
    double heating_coeff_by_crankshaft_speed;
    double cooling_coeff;

    // External Data:
    phycs_units::Temperature ambient_temp;

    // Engine State:
    phycs_units::Torque M;
    phycs_units::CrankshaftSpeed V;
    phycs_units::Speed heating_speed;
    phycs_units::Speed cooling_speed;
    phycs_units::Temperature current_temp;
};