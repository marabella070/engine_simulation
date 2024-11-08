#include "physics_units.h"

namespace phycs_units {

/* ------------------ Class InertiaMoment Implementation ------------------ */
std::istream& operator>>(std::istream& input, InertiaMoment& inertia_moment) {
    input >> inertia_moment.value_;
    return input;
}


/* ---------------------- Class Torque Implementation ---------------------- */
std::istream& operator>>(std::istream& input, Torque& torgue) {
    input >> torgue.value_;
    return input;
}


/* ----------------- Class CrankshaftSpeed Implementation ----------------- */
std::istream& operator>>(std::istream& input, CrankshaftSpeed& crankshaft_speed) {
    input >> crankshaft_speed.value_;
    return input;
}


/* ------------------- Class Temperature Implementation ------------------- */
std::istream& operator>>(std::istream& input, Temperature& temperature) {
    input >> temperature.value_;
    return input;
}

/* ------------------- Class Speed Implementation ------------------- */
std::istream& operator>>(std::istream& input, Speed& speed) {
    input >> speed.value_;
    return input;
}

/* ------------------- Class Power Implementation ------------------- */
std::istream& operator>>(std::istream& input, Power& power) {
    input >> power.value_;
    return input;
}

// Defining custom literals
InertiaMoment operator""_kg_m_sqr(unsigned long long kg_m_sqr) {
    return InertiaMoment(static_cast<double>(kg_m_sqr));
}

Torque operator""_Hm(unsigned long long Hm) {
    return Torque(static_cast<double>(Hm));
}

CrankshaftSpeed operator""_rad_per_sec(unsigned long long rad_per_sec) {
    return CrankshaftSpeed(static_cast<double>(rad_per_sec));
}

Temperature operator""_cels(unsigned long long cels) {
    return Temperature(static_cast<double>(cels));
}

Speed operator""_m_s(unsigned long long m_s) {
    return Speed(static_cast<double>(m_s));
}

Power operator""_watt(unsigned long long watt) {
    return Power(static_cast<double>(watt));
}

} // physics_units namespace