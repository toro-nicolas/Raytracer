/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Ambient class declaration
*/
/**
 * @file Ambient.cpp
 * @brief The Ambient class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Ambient.hpp"

namespace Raytracer {
    Ambient::Ambient()
    {
        // DEBUG << "Ambient constructor";
    }

    Ambient::~Ambient()
    {
        // DEBUG << "Ambient destructor";
    }

    std::unique_ptr<ILightBuilder> &Ambient::getBuilder(void)
    {
        // DEBUG << "Ambient getBuilder";
        if (!_builder)
            _builder = std::make_unique<AmbientBuilder>(*this);
        return _builder;
    }

    void Ambient::display(void)
    {
        std::cout << "Ambient data:" << std::endl;
        //std::cout << "        - Position: " << _pos << std::endl;
        std::cout << "        - Intensity: " << _intensity << std::endl;
    }

    AmbientBuilder::AmbientBuilder(Ambient &ambient) : ALightBuilder(ambient), _ambient(ambient)
    {
        // DEBUG << "AmbientBuilder constructor";
    }

    AmbientBuilder::~AmbientBuilder()
    {
        // DEBUG << "AmbientBuilder destructor";
    }

    ILightBuilder &AmbientBuilder::set(UNUSED const std::string &name, UNUSED const std::vector<std::string> &args)
    {
        DEBUG << "AmbientBuilder set " << name;
        return *this;
    }

    extern "C" std::shared_ptr<Ambient> createLight(void)
    {
        return std::make_shared<Ambient>();
    }
}