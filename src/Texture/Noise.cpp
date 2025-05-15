/*
** EPITECH PROJECT, 2025
** Noise.cpp
** File description:
** Noise in ~/Documents/EPITECH/TEK2/OOP/BOOP400_raytracer/src/Texture
*/

#include "Noise.hpp"

namespace Raytracer {

    Noise::Noise(double scale)
        : _scale(scale)
    {
        // DEBUG << "Noise constructor";
    }

    Lib::Vector3 Noise::value(UNUSED double u, UNUSED double v, UNUSED const Lib::Vector3& p) const
    {
        // return Lib::Vector3(1, 1, 1) * _noise.turb(p, 7);
        return Lib::Vector3(.5, .5, .5) * (1 + std::sin(_scale * p.z + 10 * _noise.turb(p, 7)));
    }

    void Noise::display(void) const
    {
        std::cout << "Noise" << std::endl;
    }
}