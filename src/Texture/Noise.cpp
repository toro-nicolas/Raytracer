/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Noise class implementation
*/
/**
 * @file Noise.cpp
 * @brief The Noise class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
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

    void Noise::display(size_t level) const
    {
        std::string indent = std::string(level * 4, ' ');
        std::cout << "Noise texture:" << std::endl;
        std::cout << indent << "- Scale: " << _scale << std::endl;
    }
}
