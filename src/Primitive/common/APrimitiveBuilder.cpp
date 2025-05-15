/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The APrimitiveBuilder class implementation
*/
/**
 * @file APrimitiveBuilder.cpp
 * @brief The APrimitiveBuilder class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "APrimitiveBuilder.hpp"

namespace Raytracer {
    APrimitiveBuilder::APrimitiveBuilder(IPrimitive &primitive) : _primitive(primitive)
    {
    }

    IPrimitiveBuilder &APrimitiveBuilder::setPos(const Lib::Vector3 &pos)
    {
        _primitive.setPos(pos);
        return *this;
    }

    IPrimitiveBuilder &APrimitiveBuilder::setMaterial(const std::string &name, std::shared_ptr<IMaterial> &material)
    {
        _primitive.setMaterial(name, material);
        return *this;
    }

    IPrimitiveBuilder &APrimitiveBuilder::setTransformation(const std::string &name, std::shared_ptr<ITransformation> &transformation)
    {
        _primitive.setTransformation(name, transformation);
        return *this;
    }
}