/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The AMaterialBuilder class implementation
*/
/**
 * @file AMaterialBuilder.cpp
 * @brief The AMaterialBuilder class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "AMaterialBuilder.hpp"

namespace Raytracer {
    AMaterialBuilder::AMaterialBuilder(IMaterial &material) : _material(material)
    {
    }
}