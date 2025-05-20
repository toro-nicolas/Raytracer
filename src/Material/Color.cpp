/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Color class implementation
*/
/**
 * @file Color.cpp
 * @brief The Color class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Color.hpp"
#include "Checker.hpp"
#include "Image.hpp"
#include "Noise.hpp"
#include "SolidColor.hpp"

namespace Raytracer {
    Color::Color(uint8_t r, uint8_t g, uint8_t b)
    {
        // DEBUG << "Color constructor";
        _color.x = r / 255.0f;
        _color.y = g / 255.0f;
        _color.z = b / 255.0f;
        _texture = nullptr;
        // _texture = std::make_shared<SolidColor>(Lib::Vector3(_color.x, _color.y, _color.z));
    }

    Color::Color(std::shared_ptr<Texture> texture)
    {
        // DEBUG << "Color constructor";
        _texture = texture;
        _color.x = 0;
        _color.y = 0;
        _color.z = 0;
    }

    Color::~Color()
    {
        // DEBUG << "Color destructor";
    }

    std::unique_ptr<IMaterialBuilder> &Color::getBuilder(void)
    {
        // DEBUG << "Color getBuilder";
        if (!_builder)
            _builder = std::make_unique<ColorBuilder>(*this);
        return _builder;
    }

    std::shared_ptr<Texture> &Color::getTexture(void)
    {
        return _texture;
    }

    void Color::display(size_t level)
    {
        std::string indent = std::string(level * 4, ' ');
        std::cout << "Color data:" << std::endl;
        std::cout << indent << "- R: " << 255 * _color.x << std::endl;
        std::cout << indent << "- G: " << 255 * _color.y << std::endl;
        std::cout << indent << "- B: " << 255 * _color.z << std::endl;
        if (_texture != nullptr) {
            std::cout << indent << "- Texture: " << std::endl;
            std::cout << indent << "    - ";
            _texture->display(level + 2);
        }
    }
    
    bool Color::scatter(UNUSED const Ray& r_in, const Intersection& rec, Lib::Vector3 &attenuation, Ray& scattered) const
    {
        auto scatter_direction = rec.normal + Lib::random_unit_vector();
        if (scatter_direction.nearZero())
            scatter_direction = rec.normal;

        scattered = Ray(rec.p, scatter_direction, r_in.getTime());
        if (_texture == nullptr)
            attenuation = _color;
        else
            attenuation = _texture->value(rec.u, rec.v, rec.p);
        return true;
    }

    Lib::Vector3 &Color::getColor(void)
    {
        return _color;
    }

    const Lib::Vector3 &Color::getColor(void) const
    {
        return _color;
    }

    void Color::setColor(const Lib::Vector3 &color)
    {
        _color = color;
    }

    ColorBuilder::ColorBuilder(Color &color) : AMaterialBuilder(color), _color(color)
    {
        // DEBUG << "ColorBuilder constructor";
    }

    ColorBuilder::~ColorBuilder()
    {
        // DEBUG << "ColorBuilder destructor";
    }

    IMaterialBuilder &ColorBuilder::setTexture(const std::string &texture_name, const std::vector<std::string> &args)
    {
        if (texture_name == "solid") {
                if (args.size() != 3)
                    return *this;
                float r = std::stof(args[0]);
                float g = std::stof(args[1]);
                float b = std::stof(args[2]);
                _color.getTexture() = std::make_shared<SolidColor>(Lib::Vector3(r, g, b));
        } else if (texture_name == "checker") {
                if (args.size() != 7)
                    return *this;
                float scale = std::stof(args[0]);
                float r1 = std::stof(args[1]);
                float g1 = std::stof(args[2]);
                float b1 = std::stof(args[3]);
                float r2 = std::stof(args[4]);
                float g2 = std::stof(args[5]);
                float b2 = std::stof(args[6]);
                DEBUG_CONCAT << "ColorBuilder set: checker scale = " << scale;
                DEBUG_CONCAT << "ColorBuilder set: checker color1 = " << r1 << ", " << g1 << ", " << b1;
                DEBUG_CONCAT << "ColorBuilder set: checker color2 = " << r2 << ", " << g2 << ", " << b2;
                _color.getTexture() = std::make_shared<Checker>(scale, Lib::Vector3(r1, g1, b1), Lib::Vector3(r2, g2, b2));
        } else if (texture_name == "image") {
            if (args.size() != 1)
                return *this;
            std::string filename = args[0];
            DEBUG_CONCAT << "ColorBuilder set: image filename = " << filename;
            _color.getTexture() = std::make_shared<Image>(filename);
        } else if (texture_name == "perlin") {
            if (args.size() != 1)
                return *this;
            DEBUG_CONCAT << "ColorBuilder set: noise";
            double scale = std::stof(args[0]);
            _color.getTexture() = std::make_shared<Noise>(scale);
        } else {
            WARNING << "ColorBuilder set: unknown texture " << texture_name;
        }
        return *this;
    }

    IMaterialBuilder &ColorBuilder::set(const std::string &name, const std::vector<std::string> &args)
    {
        DEBUG << "ColorBuilder set " << name;
        if (name == "r") {
            if (args.size() != 1)
                return *this;
            if (args[0].back() == '%') {
                float r = std::stof(args[0]);
                _color.getColor().x = r / 100.0f;
                DEBUG_CONCAT << "ColorBuilder set: r = " << r << "%";
            } else {
                float r = std::stof(args[0]);
                _color.getColor().x = r / 255.0f;
                DEBUG_CONCAT << "ColorBuilder set: r = " << r;
            }
        } else if (name == "g") {
            if (args.size() != 1)
                return *this;
            if (args[0].back() == '%') {
                float g = std::stof(args[0]);
                _color.getColor().y = g / 100.0f;
                DEBUG_CONCAT << "ColorBuilder set: g = " << g << "%";
            } else {
                float g = std::stof(args[0]);
                _color.getColor().y = g / 255.0f;
                DEBUG_CONCAT << "ColorBuilder set: g = " << g;
            }
        } else if (name == "b") {
            if (args.size() != 1)
                return *this;
            if (args[0].back() == '%') {
                float b = std::stof(args[0]);
                _color.getColor().z = b / 100.0f;
                DEBUG_CONCAT << "ColorBuilder set: b = " << b << "%";
            } else {
                float b = std::stof(args[0]);
                _color.getColor().z = b / 255.0f;
                DEBUG_CONCAT << "ColorBuilder set: b = " << b;
            }
        } else if (name == "texture") {
            if (args.size() < 1)
                return *this;
            std::string texture_name = args[0];
            auto suite = args;
            suite.erase(suite.begin());
            for (const auto &arg : suite)
                DEBUG_CONCAT << "ColorBuilder set: texture arg = " << arg;
            return setTexture(texture_name, suite);
        } else {
            WARNING << "ColorBuilder set: unknown property " << name;
        }
        return *this;
    }

    extern "C" std::shared_ptr<Color> createMaterial(void)
    {
        return std::make_shared<Color>();
    }
}