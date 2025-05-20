/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Interval class implementation
*/
/**
 * @file Interval.cpp
 * @brief The Interval class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Interval.hpp"

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

    Interval operator+(const Interval& ival, double displacement) {
        return Interval(ival.min + displacement, ival.max + displacement);
    }

    Interval operator+(double displacement, const Interval& ival) {
        return ival + displacement;
    }
}