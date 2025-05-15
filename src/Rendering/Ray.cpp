/*
** EPITECH PROJECT, 2025
** Ray.cpp
** File description:
** Ray in ~/Documents/EPITECH/TEK2/OOP/BOOP400_raytracer/src/Rendering
*/

/**
 * @file Ray.cpp
 * @brief Ray class implementation
 * @author Gianni TUERO
 */
#include "Ray.hpp"
#include "Lib.hpp"

namespace Raytracer
{
    Ray::Ray(const Lib::Vector3 &origin, const Lib::Vector3 &direction, double t)
        : _origin(origin), _direction(direction), _t(t)
    {
    }

    Ray::Ray(const Lib::Vector3 &origin, const Lib::Vector3 &direction)
        : Ray(origin, direction, 0.0)
    {
    }

    Ray::~Ray()
    {
    }

    Ray::Ray(const Ray &other)
        : _origin(other._origin), _direction(other._direction), _t(other._t)
    {
    }

    Ray &Ray::operator=(const Ray &other)
    {
        if (this != &other) {
            _origin = other._origin;
            _direction = other._direction;
        }
        return *this;
    }


    Lib::Vector3 Ray::getColor(void) const
    {
        Lib::Vector3 unit_direction = unit_vector(direction());
        auto a = 0.5 * (unit_direction.y + 1.0);
        return (1.0 - a) * Lib::Vector3(1.0, 1.0, 1.0) + a * Lib::Vector3(0.5, 0.7, 1.0);
    }

    Lib::Vector3 Ray::pointAt(float t) const
    {
        return _origin + _direction * t;
    }

    const Lib::Vector3 &Ray::direction(void) const
    {
        return _direction;
    }

    const Lib::Vector3 &Ray::origin(void) const
    {
        return _origin;
    }

    double &Ray::getTime(void)
    {
        return _t;
    }

    const double &Ray::getTime(void) const
    {
        return _t;
    }

    ////////////////////////////////////// INTERSECTION //////////////////////////////////////
    void Intersection::setFaceNormal(const Ray &r, const Vector3 &outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
}