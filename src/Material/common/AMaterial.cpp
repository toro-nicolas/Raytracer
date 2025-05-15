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
    void AMaterial::display(void)
    {
        std::cout << "Material data: No data" << std::endl;
    }

    bool AMaterial::scatter(UNUSED const Ray& r_in, UNUSED const Intersection& rec,
        UNUSED Lib::Vector3 &attenuation, UNUSED Ray& scattered) const
    {
        return false;
    }
}