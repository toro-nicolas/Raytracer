/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Lib declaration
*/
/**
 * @file Lib.hpp
 * @brief Lib declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
*/

#ifndef LIB_HPP
    #define LIB_HPP

    #include "Exceptions.hpp"
    #include "Interval.hpp"
    #include "Logs.hpp"
    #include "Vector3.hpp"
    #include <random>


namespace Lib {
    /**
     * @brief Splits a string into a vector of strings based on a separator
     * @param str The string to split
     * @param separator The separator to split the string with
     * @return std::vector<std::string> Vector containing the split string parts
     */
    std::vector<std::string> stringToVector(std::string str, std::string separator);

    /**
     * @brief Checks if a certain amount of time has passed since the last check
     * @param ms_delay The delay in milliseconds to check against
     * @param lastTime Reference to the time point of the last check
     * @return bool True if the delay has passed, false otherwise
     */
    bool delay(int ms_delay, std::chrono::steady_clock::time_point &lastTime);

    /**
     * @brief Generates a random double between 0 and 1
     * @return double Random double between 0 and 1
     */
    inline double random_double()
    {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    /**
     * @brief Generates a random double between min and max
     * @param min The minimum value
     * @param max The maximum value
     * @return double Random double between min and max
     */
    inline double random_double(double min, double max)
    {
        return min + (max - min) * random_double();
    }

    inline int random_int(int min, int max)
    {
        // Returns a random integer in [min,max].
        return int(random_double(min, max+1));
    }

    /**
     * @brief Converts degrees to radians
     * @param degrees The angle in degrees
     * @return double The angle in radians
     */
    inline double degToRad(double degrees)
    {
        return degrees * M_PI / 180.0;
    }

    inline double linearToGamma(double comp)
    {
        if (comp > 0)
            return std::sqrt(comp);
        return 0;
    }

}


#endif // LIB_HPP
