/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Directional class implementation
*/
/**
 * @file Directional.cpp
 * @brief The Directional class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Directional.hpp"

namespace Raytracer {
    Directional::Directional()
    {
        // DEBUG << "Directional constructor";
    }

    Directional::~Directional()
    {
        // DEBUG << "Directional destructor";
    }

    std::unique_ptr<ILightBuilder> &Directional::getBuilder(void)
    {
        // DEBUG << "Directional getBuilder";
        if (!_builder)
            _builder = std::make_unique<DirectionalBuilder>(*this);
        return _builder;
    }

    void Directional::display(void)
    {
        std::cout << "Directional data:" << std::endl;
        std::cout << "        - Position: " << _pos << std::endl;
        std::cout << "        - Intensity: " << _intensity << std::endl;
        std::cout << "        - Direction: " << _direction << std::endl;
    }

    Lib::Vector3 &Directional::getDirection()
    {
        return _direction;
    }

    const Lib::Vector3 &Directional::getDirection() const
    {
        return _direction;
    }

    void Directional::setDirection(const Lib::Vector3 &direction)
    {
        _direction = direction;
    }

    DirectionalBuilder::DirectionalBuilder(Directional &directional) : ALightBuilder(directional), _directional(directional)
    {
        // DEBUG << "DirectionalBuilder constructor";
    }

    DirectionalBuilder::~DirectionalBuilder()
    {
        // DEBUG << "DirectionalBuilder destructor";
    }

    ILightBuilder &DirectionalBuilder::set(UNUSED const std::string &name, UNUSED const std::vector<std::string> &args)
    {
        DEBUG << "DirectionalBuilder set " << name;
        if (name == "direction") {
            if (args.size() != 3) {
                return *this;
            }
            _directional.setDirection(Lib::Vector3(std::stof(args[0]), std::stof(args[1]), std::stof(args[2])));
        }
        return *this;
    }

    extern "C" std::shared_ptr<Directional> createLight(void)
    {
        return std::make_shared<Directional>();
    }
}