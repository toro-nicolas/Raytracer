/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Point.cpp
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

    void Point::display(void)
    {
        std::cout << "Point data:" << std::endl;
        std::cout << "        - Position: " << _pos << std::endl;
        std::cout << "        - Intensity: " << _intensity << std::endl;
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