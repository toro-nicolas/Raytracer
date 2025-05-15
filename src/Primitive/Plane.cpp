/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Plane class declaration
*/
/**
 * @file Plane.cpp
 * @brief The Plane class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Plane.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

namespace Raytracer {
    Plane::Plane()
    {
        // DEBUG << "Plane constructor";
        _u = Lib::Vector3(0, 0, 0);
        _v = Lib::Vector3(0, 0, 0);
    }

    Plane::~Plane()
    {
        // DEBUG << "Plane destructor";
    }

    std::unique_ptr<IPrimitiveBuilder> &Plane::getBuilder(void)
    {
        // DEBUG << "Plane getBuilder";
        if (!_builder)
            _builder = std::make_unique<PlaneBuilder>(*this);
        return _builder;
    }

    Lib::Vector3 &Plane::getFirstSide(void)
    {
        return _u;
    }
    Lib::Vector3 &Plane::getSecondSide(void)
    {
        return _v;
    }

    void Plane::display(void)
    {
        // calling setBoundingBox() in this function because user
        // can enter only the position of the plane and it should work too
        setBoundingBox();
        std::cout << "Plane data:" << std::endl;
        std::cout << "        - Position: " << _pos << std::endl;
        std::cout << "        - Materials: (" << _materials.size() << ")" << std::endl;
        for (const auto &pair: _materials) {
            std::cout << "            - ";// << pair.first << ": ";
            pair.second->display();
        }
        if (_materials.empty())
            std::cout << std::endl;
        std::cout << "        - Transformations: (" << _transformations.size() << ")" << std::endl;
        for (const auto &pair: _transformations) {
            std::cout << "            - ";// << pair.first << ": ";
            pair.second->display();
        }
        std::cout << "        - First side (u): " << _u << std::endl;
        std::cout << "        - Second side (v): " << _v << std::endl;
        std::cout << "        - Normal: " << _normal << std::endl;
        std::cout << "        - D: " << D << std::endl;
    }

    void Plane::setBoundingBox()
    {
        auto n = cross(_u, _v);
        _normal = unit_vector(n);
        D = dot(_normal, _pos);
        _w = n / dot(n,n);

        auto bbox_diagonal1 = AABB(_pos, _pos + _u + _v);
        auto bbox_diagonal2 = AABB(_pos + _u, _pos + _v);
        _bbox = AABB(bbox_diagonal1, bbox_diagonal2);
    }

    bool Plane::hit(const Ray& ray, Interval rayT, Intersection& rec) const
    {
        auto denom = dot(_normal, ray.direction());
        // No hit if the ray is parallel to the plane.
        if (std::fabs(denom) < 1e-8)
            return false;
        // Return false if the hit point parameter t is outside the ray interval.
        auto t = (D - dot(_normal, ray.origin())) / denom;
        if (!rayT.contains(t))
            return false;

        auto intersection = ray.pointAt(t);
        Lib::Vector3 planar_hitpt_vector = intersection - _pos;
        auto alpha = dot(_w, cross(planar_hitpt_vector, _v));
        auto beta = dot(_w, cross(_u, planar_hitpt_vector));
        if (!isInterior(alpha, beta, rec))
            return false;

        rec.t = t;
        rec.p = intersection;
        rec.material = _materials;
        rec.setFaceNormal(ray, _normal);
        return true;
    }

    bool Plane::isInterior(double a, double b, Intersection& rec) const
    {
        Interval unit_interval = Interval(0, 1);
        // Given the hit point in plane coordinates, return false if it is outside the
        // primitive, otherwise set the hit record UV coordinates and return true.
        if (!unit_interval.contains(a) || !unit_interval.contains(b))
            return false;

        rec.u = a;
        rec.v = b;
        return true;
    }

};

namespace Raytracer {
    PlaneBuilder::PlaneBuilder(Plane &plane) : APrimitiveBuilder(plane), _plane(plane)
    {
        // DEBUG << "PlaneBuilder constructor";
    }

    PlaneBuilder::~PlaneBuilder()
    {
        // DEBUG << "PlaneBuilder destructor";
    }

    IPrimitiveBuilder &PlaneBuilder::set(const std::string &name, UNUSED const std::vector<std::string> &args)
    {
        DEBUG << "PlaneBuilder set " << name;
        if (name == "direction") {
            if (args.size() != 6)
                return *this;
            // first side
            float xu = std::stof(args[0]);
            float yu = std::stof(args[1]);
            float zu = std::stof(args[2]);
            // second side
            float xv = std::stof(args[3]);
            float yv = std::stof(args[4]);
            float zv = std::stof(args[5]);
            _plane.getFirstSide() = Lib::Vector3(xu, yu, zu);
            _plane.getSecondSide() = Lib::Vector3(xv, yv, zv);
            _plane.setBoundingBox();
        }
        return *this;
    }

    extern "C" std::shared_ptr<Plane> createPrimitive(void)
    {
        return std::make_shared<Plane>();
    }
}