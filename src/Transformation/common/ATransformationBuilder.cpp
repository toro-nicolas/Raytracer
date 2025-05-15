/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ATransformationBuilder class declaration
*/
/**
 * @file ATransformationBuilder.cpp
 * @brief The ATransformationBuilder class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "ATransformationBuilder.hpp"

namespace Raytracer {
    ATransformationBuilder::ATransformationBuilder(ITransformation &transformation) : _transformation(transformation)
    {
    }
}