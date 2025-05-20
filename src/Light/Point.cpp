/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Point class implementation
*/
/**
 * @file Point.cpp
 * @brief The Point class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Point.hpp"

namespace Raytracer {
    Point::Point()
    {
        // DEBUG << "Point constructor";
    }

    Point::~Point()
    {
        // DEBUG << "Point destructor";
    }

    std::unique_ptr<ILightBuilder> &Point::getBuilder(void)
    {
        // DEBUG << "Point getBuilder";
        if (!_builder)
            _builder = std::make_unique<PointBuilder>(*this);
        return _builder;
    }

    void Point::display(size_t level)
    {
        std::string indent(level * 4, ' ');
        std::cout << "Point data:" << std::endl;
        std::cout << indent << "- Position: " << _pos << std::endl;
        std::cout << indent << "- Intensity: " << _intensity * 100 << "%" << std::endl;
    }

    Lib::Vector3 Point::compute(const Lib::Vector3& point, const Lib::Vector3& normal,
                          UNUSED const Lib::Vector3& view_dir) const
    {
        // Calculate light direction (from point to light)
        Lib::Vector3 light_dir = (_pos - point).unit_vector();

        // Calculate distance from point to light
        double distance = (_pos - point).length();

        // Calculate attenuation based on distance
        double attenuation = 1.0 / (1.0 + 0.01 * distance + 0.001 * distance * distance);

        // Calculate how directly the surface is facing the light
        double diffuse_factor = std::max(0.0, normal.dot(light_dir));

        return Lib::Vector3(1.0, 1.0, 1.0) * diffuse_factor * _intensity * attenuation;
    }

    PointBuilder::PointBuilder(Point &point) : ALightBuilder(point), _point(point)
    {
        // DEBUG << "PointBuilder constructor";
    }

    PointBuilder::~PointBuilder()
    {
        // DEBUG << "PointBuilder destructor";
    }

    ILightBuilder &PointBuilder::set(UNUSED const std::string &name, UNUSED const std::vector<std::string> &args)
    {
        DEBUG << "PointBuilder set " << name;
        return *this;
    }

    extern "C" std::shared_ptr<Point> createLight(void)
    {
        return std::make_shared<Point>();
    }
}