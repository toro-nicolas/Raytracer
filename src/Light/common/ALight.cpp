/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ALight class implementation
*/
/**
 * @file ALight.cpp
 * @brief The ALight class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "ALight.hpp"
using namespace Lib;

namespace Raytracer {
    void ALight::display(void)
    {
        std::cout << "Light data:" << std::endl;
        std::cout << "        - Position: " << _pos << std::endl;
        std::cout << "        - Intensity: " << _intensity << std::endl;
    }

    Lib::Vector3 &ALight::getPos()
    {
        return _pos;
    }

    const Lib::Vector3 &ALight::getPos() const
    {
        return _pos;
    }

    void ALight::setPos(const Lib::Vector3 &pos)
    {
        _pos = pos;
    }

    double &ALight::getIntensity()
    {
        return _intensity;
    }

    const double &ALight::getIntensity() const
    {
        return _intensity;
    }

    void ALight::setIntensity(double intensity)
    {
        _intensity = intensity;
    }
}