/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Lib implementation
*/
/**
 * @file Lib.cpp
 * @brief The Lib implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Lib.hpp"

namespace Lib {
    std::vector<std::string> stringToVector(std::string str, std::string separator)
    {
        std::vector<std::string> array;
        size_t pos = str.find_first_not_of(separator, 0);
        while (pos != std::string::npos) {
            size_t i = str.find_first_of(separator, pos);
            if (i == std::string::npos)
                i = str.length();
            array.push_back(str.substr(pos, i - pos));
            pos = str.find_first_not_of(separator, i);
        }
        return array;
    }

    bool delay(int ms_delay, std::chrono::steady_clock::time_point &lastTime)
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration<float>(now - lastTime);
        if (elapsed.count() > ms_delay / 1000.0f) {
            lastTime = now;
            return true;
        }
        return false;
    }
}