/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ATransformation class declaration
*/
/**
 * @file ATransformation.cpp
 * @brief The ATransformation class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "ATransformation.hpp"
using namespace Lib;

namespace Raytracer {
    void ATransformation::display(size_t level)
    {
        std::string indent(level * 4, ' ');
        std::cout << "Transformation data:" << std::endl;
        std::cout << indent << "No data" << std::endl;
    }

    Lib::Vector3 &ATransformation::getOffset(void)
    {
        return _offset;
    }

    const Lib::Vector3 &ATransformation::getOffset(void) const
    {
        return _offset;
    }

    void ATransformation::setOffset(const Lib::Vector3 &offset)
    {
        _offset = offset;
    }

    void ATransformation::compute(UNUSED Ray &ray)
    {
        // Default implementation, should be overridden
    }

    void ATransformation::decompute(UNUSED Intersection &intersection)
    {
        // Default implementation, should be overridden
    }

    void ATransformation::newBoundingBox(UNUSED AABB &bbox)
    {
    }
}
