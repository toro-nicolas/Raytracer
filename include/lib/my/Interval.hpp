/*
** EPITECH PROJECT, 2025
** Interval.hpp
** File description:
** Interval declaration
*/
/**
 * @file Interval.hpp
 * @brief The Interval class declaration
 * @author Gianni TUERO
 */

#ifndef INTERVAL_HPP
    #define INTERVAL_HPP

    #include <limits>
    #include <cmath>
    #include <algorithm>

namespace Raytracer {
    /**
     * @brief Infinity constant for interval boundaries
     */
    constexpr double infinity = std::numeric_limits<double>::infinity();

    /**
     * @class Interval
     * @brief A class representing a range between two values
     */
    class Interval {
      public:
        double min; ///< The minimum value of the interval
        double max; ///< The maximum value of the interval

        /**
         * @brief Default constructor for Interval
         */
        Interval();

        /**
         * @brief Constructor for Interval with specific min and max values
         * @param min The minimum value of the interval
         * @param max The maximum value of the interval
         */
        Interval(double min, double max);

        /**
         * @brief Constructor for Interval from two other intervals
         * @param a The first interval
         * @param b The second interval
         */
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

        /**
         * @brief Expands the interval by a delta amount
         * @param delta The amount to expand the interval by
         * @return Interval The expanded interval
         */
        Interval expand(double delta) const;

        static const Interval empty; ///< An empty interval (min > max)
        static const Interval universe; ///< An interval covering all possible values
    };

    // Define static members using the constant
    inline const Interval Interval::empty = Interval(infinity, -infinity);
    inline const Interval Interval::universe = Interval(-infinity, infinity);

    /**
     * @brief Adds a displacement to an interval
     * @param ival The interval to displace
     * @param displacement The displacement value
     * @return Interval The displaced interval
     */
    Interval operator+(const Interval& ival, double displacement);

    /**
     * @brief Adds a displacement to an interval
     * @param displacement The displacement value
     * @param ival The interval to displace
     * @return Interval The displaced interval
     */
    Interval operator+(double displacement, const Interval& ival);

}

#endif // INTERVAL_HPP