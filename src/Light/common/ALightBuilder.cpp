/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ALightBuilder class implementation
*/
/**
 * @file ALightBuilder.cpp
 * @brief The ALightBuilder class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "ALightBuilder.hpp"

namespace Raytracer {
    ALightBuilder::ALightBuilder(ILight &light) : _light(light)
    {
    }

    ILightBuilder &ALightBuilder::setPos(const Lib::Vector3 &pos)
    {
        _light.setPos(pos);
        return *this;
    }

    ILightBuilder &ALightBuilder::setIntensity(double intensity)
    {
        _light.setIntensity(intensity);
        return *this;
    }
}