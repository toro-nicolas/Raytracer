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
    Directional::Directional() : _direction(0, -1, 0), _color(1, 1, 1)
    {
        _intensity = 0.6; // Default intensity
    }

    Directional::~Directional()
    {
    }

    std::unique_ptr<ILightBuilder> &Directional::getBuilder(void)
    {
        if (!_builder)
            _builder = std::make_unique<DirectionalBuilder>(*this);
        return _builder;
    }

    void Directional::display(size_t level)
    {
        std::string indent(level * 4, ' ');
        std::cout << "Directional Light:" << std::endl;
        std::cout << indent << "- Direction: " << _direction << std::endl;
        std::cout << indent << "- Intensity: " << _intensity * 100 << "%" << std::endl;
        std::cout << indent << "- Color: " << _color * 255 << std::endl;
    }

    Lib::Vector3 &Directional::getDirection(void)
    {
        return _direction;
    }

    const Lib::Vector3 &Directional::getDirection(void) const
    {
        return _direction;
    }

    void Directional::setDirection(const Lib::Vector3 &direction)
    {
        _direction = direction.unit_vector();
    }

    Lib::Vector3 &Directional::getColor(void)
    {
        return _color;
    }
    const Lib::Vector3 &Directional::getColor(void) const
    {
        return _color;
    }
    void Directional::setColor(const Lib::Vector3 &color)
    {
        _color = color;
    }

    // This new method computes the directional light contribution
    Lib::Vector3 Directional::compute(UNUSED const Lib::Vector3& point, UNUSED const Lib::Vector3& normal,
                                    UNUSED const Lib::Vector3& view_dir) const
    {
        // Calculate how directly the surface is facing the light
       float dot = normal.dot(-_direction);

        // S'assurer que la valeur est positive (surface face à la lumière)
        dot = std::max(0.0f, dot);

        // Retourner la couleur multipliée par l'intensité et le facteur du produit scalaire
        return _color * _intensity * dot;
    }

    DirectionalBuilder::DirectionalBuilder(Directional &directional)
        : ALightBuilder(directional), _directional(directional)
    {
    }

    DirectionalBuilder::~DirectionalBuilder()
    {
    }

    ILightBuilder &DirectionalBuilder::setDirection(const Lib::Vector3 &direction)
    {
        _directional.setDirection(direction);
        return *this;
    }

    ILightBuilder &DirectionalBuilder::set(const std::string &name, const std::vector<std::string> &args)
    {
        if (name == "direction" && args.size() >= 3) {
            _directional.setDirection(Lib::Vector3(
                std::stof(args[0]),
                std::stof(args[1]),
                std::stof(args[2])
            ));
        } else if (name == "color" && args.size() >= 3) {
            Lib::Vector3 color;
            for (size_t i = 0; i < 3; ++i) {
                std::string arg = args[i];
                float value;
                if (arg.back() == '%') {
                    arg.pop_back();
                    value = std::stof(arg) / 100.0f;
                } else {
                    value = std::stof(arg);
                    // on suppose que c'est une valeur 0-255
                    if (value > 1.0f)
                        value = value / 255.0f;
                }
                color[i] = value;
            }
            _directional.setColor(color);
        } else {
            WARNING << "Unknown property for Directional light: " << name;
        }
        return *this;
    }

    extern "C" std::shared_ptr<Directional> createLight(void)
    {
        return std::make_shared<Directional>();
    }
}