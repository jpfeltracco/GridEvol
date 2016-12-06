#include "Normalizable.h"

Normalizable::Normalizable(double min, double max) : min(min), max(max) {};

double Normalizable::actual() {
    return min + (max - min) * (normed + 1.0f) / 2.0f;
}

double Normalizable::normalized() {
    return normed;
}

void Normalizable::set_actual(double value) {
    normed = ((value - min) / (max - min)) * 2.0f - 1.0f;
}

void Normalizable::set_normalized(double value) {
    normed = value;
}
