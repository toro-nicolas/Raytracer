/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The AMaterial class implementation
*/
/**
 * @file AMaterial.cpp
 * @brief The AMaterial class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "AMaterial.hpp"
#include "Logs.hpp"
using namespace Lib;

namespace Raytracer {
    void AMaterial::display(size_t level)
    {
        std::string indent = std::string(level * 4, ' ');
        std::cout << "Material data:" << std::endl;
        std::cout << indent << "No data" << std::endl;
    }

    bool AMaterial::scatter(UNUSED const Ray& r_in, UNUSED const Intersection& rec,
        UNUSED Lib::Vector3 &attenuation, UNUSED Ray& scattered) const
    {
        return false;
    }
    Lib::Vector3 AMaterial::emitted(UNUSED double u, UNUSED double v, UNUSED const Lib::Vector3& p) const
    {
        return Lib::Vector3(0,0,0);
    }
}