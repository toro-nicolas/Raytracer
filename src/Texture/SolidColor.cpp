/*
** EPITECH PROJECT, 2025
** SolidColor.cpp
** File description:
** SolidColor in ~/Documents/EPITECH/TEK2/OOP/BOOP400_raytracer/src/Texture
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

    void SolidColor::display() const
    {
        std::cout << "\t\t\tSolidColor: (" << _color.x << ", " << _color.y << ", " << _color.z << ")" << std::endl;
    }
}