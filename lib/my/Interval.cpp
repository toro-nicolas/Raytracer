/*
** EPITECH PROJECT, 2025
** Interval.cpp
** File description:
** Interval in ~/Documents/EPITECH/TEK2/OOP/BOOP400_raytracer/lib/my
*/

#include "Interval.hpp"
#include <algorithm>

namespace Raytracer {

    Interval::Interval() : min(+infinity), max(-infinity) {}
    Interval::Interval(double min, double max) : min(min), max(max) {}

    Interval::Interval(const Interval& a, const Interval& b)
    {
        // Create the interval tightly enclosing the two input intervals.
        min = a.min <= b.min ? a.min : b.min;
        max = a.max >= b.max ? a.max : b.max;
    }

    double Interval::size() const {
        return max - min;
    }

    bool Interval::contains(double x) const {
        return min <= x && x <= max;
    }

    bool Interval::surrounds(double x) const {
        return min < x && x < max;
    }

    double Interval::clamp(double x) const {
        return std::clamp(x, min, max);
    }

    Interval Interval::expand(double delta) const {
        auto padding = delta/2;
        return Interval(min - padding, max + padding);
    }

}