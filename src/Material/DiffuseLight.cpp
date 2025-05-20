/*
** EPITECH PROJECT, 2025
** DiffuseLight.cpp
** File description:
** DiffuseLight material implementation
*/
/**
 * @file DiffuseLight.cpp
 * @brief DiffuseLight material implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "DiffuseLight.hpp"

namespace Raytracer {
    DiffuseLight::DiffuseLight(std::shared_ptr<Texture> tex)
        : tex(std::move(tex))
    {
    }

    DiffuseLight::DiffuseLight(const Lib::Vector3& emit)
        : tex(std::make_shared<SolidColor>(emit))
    {
    }

    Lib::Vector3 DiffuseLight::emitted(double u, double v, const Lib::Vector3& p) const
    {
        return tex->value(u, v, p);
    }

    std::unique_ptr<IMaterialBuilder>& DiffuseLight::getBuilder()
    {
        if (!_builder)
            _builder = std::make_unique<DiffuseLightBuilder>(*this);
        return _builder;
    }

    std::shared_ptr<Texture>& DiffuseLight::getTexture()
    {
        return tex;
    }

    void DiffuseLight::display(size_t level)
    {
        std::string indent = std::string(level * 4, ' ');
        std::cout << "DiffuseLight Material:" << std::endl;
        std::cout << indent << "- Color: " << _color * 255 << std::endl;
        if (tex) {
            std::cout << indent << "- Texture: " << std::endl;
            std::cout << indent << "    - ";
            tex->display(level + 2);
        }
    }

    // DiffuseLightBuilder implementation

    DiffuseLightBuilder::DiffuseLightBuilder(DiffuseLight &diffuse)
        : AMaterialBuilder(diffuse), _diffuse(diffuse)
    {
    }

    DiffuseLightBuilder::~DiffuseLightBuilder() = default;

    IMaterialBuilder& DiffuseLightBuilder::set(const std::string &name, const std::vector<std::string> &args)
    {
        // Handle different property settings
        if (name == "color") {
            if (args.size() != 3) {
                ERROR << "DiffuseLightBuilder set: color requires 3 arguments (r, g, b)" << std::endl;
                return *this;
            }
            Lib::Vector3 color;
            for (size_t i = 0; i < args.size(); ++i) {
                std::string arg = args[i];
                float value;
                if (arg.back() == '%') {
                    arg.pop_back(); // Remove '%' for percentage values
                    value = 255.0f * std::stof(arg) / 100.0f; // Convert percentage to 0-255 range
                } else {
                    value = std::stof(arg);
                }
                color[i] = value;
            }
            _diffuse.getTexture() = std::make_shared<SolidColor>(color);
        } else {
            WARNING << "DiffuseLightBuilder set: unknown property " << name << std::endl;
        }
        // Add other property setters as needed
        return *this;
    }

    std::shared_ptr<DiffuseLight> createMaterial()
    {
        // Create with default white light
        return std::make_shared<DiffuseLight>(Lib::Vector3(1.0, 1.0, 1.0));
    }
}