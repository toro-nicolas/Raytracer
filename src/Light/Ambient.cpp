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
        _intensity = 0.5;
    }

    Ambient::~Ambient()
    {
    }

    std::unique_ptr<ILightBuilder> &Ambient::getBuilder(void)
    {
        if (!_builder)
            _builder = std::make_unique<AmbientBuilder>(*this);
        return _builder;
    }

    void Ambient::display(size_t level)
    {
        std::string indent(level * 4, ' ');
        std::cout << "Ambient Light:" << std::endl;
        std::cout << indent << "- Intensity: " << _intensity * 100 << "%" << std::endl;
    }

    Lib::Vector3 Ambient::compute(UNUSED const Lib::Vector3& point, UNUSED const Lib::Vector3& normal,
                                UNUSED const Lib::Vector3& view_dir) const
    {
        // Ambient light is uniform in all directions and doesn't depend on position
        return Lib::Vector3(1.0, 1.0, 1.0) * _intensity;
    }

    AmbientBuilder::AmbientBuilder(Ambient &ambient) : ALightBuilder(ambient), _ambient(ambient)
    {
    }

    AmbientBuilder::~AmbientBuilder()
    {
    }

    ILightBuilder &AmbientBuilder::set(UNUSED const std::string &name, UNUSED const std::vector<std::string> &args)
    {
        return *this;
    }

    extern "C" std::shared_ptr<Ambient> createLight(void)
    {
        return std::make_shared<Ambient>();
    }
}