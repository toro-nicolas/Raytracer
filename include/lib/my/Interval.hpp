/*
** EPITECH PROJECT, 2025
** Interval.hpp
** File description:
** Interval declaration
*/


#ifndef INTERVAL_HPP
    #define INTERVAL_HPP
    #include <limits>
    #include <cmath>

namespace Raytracer {
    constexpr double infinity = std::numeric_limits<double>::infinity();

    class Interval {
      public:
        double min, max;

        Interval();
        Interval(double min, double max);
        Interval(const Interval& a, const Interval& b);

        /**
         * @brief Gets the size of the interval
         * @return double The size of the interval
         */
        double size() const;

        /**
         * @brief Checks if a certain value is contained within the interval
         * @param x The value to check
         * @return bool True if the value is contained, false otherwise
         */
        bool contains(double x) const;

        /**
         * @brief Checks if the interval surrounds a certain value
         * @param x The value to check
         * @return bool True if the interval surrounds the value, false otherwise
         */
        bool surrounds(double x) const;

        /**
         * @brief Clamps a value to the interval
         * @param x The value to clamp
         * @return double The clamped value
         */
        double clamp(double x) const;

        Interval expand(double delta) const;

        static const Interval empty, universe;
    };

    // Define static members using the constant
    inline const Interval Interval::empty = Interval(infinity, -infinity);
    inline const Interval Interval::universe = Interval(-infinity, infinity);
}

#endif // INTERVAL_HPP