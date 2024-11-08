#pragma once

#include "../PhysicsUnit/physics_unit.h"

namespace phycs_units {

struct InertiaMoment : public PhysicsUnit<InertiaMoment> {
public:
    using PhysicsUnit::PhysicsUnit;
    friend std::istream& operator>>(std::istream& input, InertiaMoment& inertia_moment);
};

struct Torque : public PhysicsUnit<Torque> {
public:
    using PhysicsUnit::PhysicsUnit;
    friend std::istream& operator>>(std::istream& input, Torque& torgue);
};

struct CrankshaftSpeed : public PhysicsUnit<CrankshaftSpeed> {
public:
    using PhysicsUnit::PhysicsUnit;
    friend std::istream& operator>>(std::istream& input, CrankshaftSpeed& crankshaft_speed);
};

struct Temperature : public PhysicsUnit<Temperature> {
public:
    using PhysicsUnit::PhysicsUnit;
    friend std::istream& operator>>(std::istream& input, Temperature& temperature);
};

struct Speed : public PhysicsUnit<Speed> {
public:
    using PhysicsUnit::PhysicsUnit;
    friend std::istream& operator>>(std::istream& input, Speed& speed);
};

struct Power : public PhysicsUnit<Power> {
public:
    using PhysicsUnit::PhysicsUnit;
    friend std::istream& operator>>(std::istream& input, Power& power);
};

// Defining custom literals
InertiaMoment operator""_kg_m_sqr(unsigned long long kg_m_sqr);
Torque operator""_Hm(unsigned long long Hm);
CrankshaftSpeed operator""_rad_per_sec(unsigned long long rad_per_sec);
Temperature operator""_cels(unsigned long long cels);
Speed operator""_m_s(unsigned long long m_s);
Power operator""_watt(unsigned long long watt);

} // physics_units namespace