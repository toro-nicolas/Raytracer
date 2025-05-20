/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The SolidColor class implementation
*/
/**
 * @file SolidColor.cpp
 * @brief The SolidColor class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "SolidColor.hpp"

namespace Raytracer {

    SolidColor::SolidColor(const Lib::Vector3& color)
        : _color(color)
    {
    }

    SolidColor::SolidColor(double red, double green, double blue)
        : SolidColor(Lib::Vector3(red, green, blue))
    {
    }

    Lib::Vector3 SolidColor::value(UNUSED double u, UNUSED double v, UNUSED const Lib::Vector3& p) const
    {
        return _color;
    }

    void SolidColor::display(size_t level) const
    {
        std::string indent = std::string(level * 4, ' ');
        std::cout << "SolidColor texture: " << std::endl;
        std::cout << indent << "- Color: " << _color << std::endl;
    }
}