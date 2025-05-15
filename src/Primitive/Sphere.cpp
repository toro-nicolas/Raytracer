/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Sphere class implementation
*/
/**
 * @file Sphere.cpp
 * @brief Sphere class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Sphere.hpp"
#include "Vector3.hpp"
using namespace Lib;

namespace Raytracer {
    Sphere::Sphere()
    {
        // DEBUG << "Sphere constructor";
        _radius = 0;
        centerSet = false;
        // _center = Ray(_pos, Vector3(0, 0, 0));
    }

    Sphere::~Sphere()
    {
        // DEBUG << "Sphere destructor";
    }

    std::unique_ptr<IPrimitiveBuilder> &Sphere::getBuilder(void)
    {
        // DEBUG << "Sphere getBuilder";
        if (!_builder)
            _builder = std::make_unique<SphereBuilder>(*this);
        return _builder;
    }

    void Sphere::display(void)
    {
        std::cout << "Sphere data:" << std::endl;
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
        std::cout << "        - Radius: " << _radius << std::endl;
    }

    float& Sphere::getRadius(void)
    {
        return _radius;
    }

    const float& Sphere::getRadius(void) const
    {
        return _radius;
    }

    void Sphere::setRadius(const float &radius)
    {
        _radius = radius;
    }

    void Sphere::setCenter(const Ray &center)
    {
        _center = center;
        // _pos = center.origin();
    }
    const Ray& Sphere::getCenter(void) const
    {
        return _center;
    }
    Ray& Sphere::getCenter(void)
    {
        return _center;
    }

    ////////////////////////////////////// INTERSECTION //////////////////////////////////////
    bool Sphere::hit(const Ray& ray, Interval rayT, Intersection& rec) const
    {
        Vector3 current_center = _center.pointAt(ray.getTime());
        Vector3 oc = current_center - ray.origin();
        auto a = ray.direction().length_squared();
        auto h = dot(ray.direction(), oc);
        auto c = oc.length_squared() - _radius*_radius;

        auto discriminant = h*h - a*c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (!rayT.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!rayT.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = ray.pointAt(rec.t);
        Vector3 outward_normal = (rec.p - current_center) / _radius;
        rec.setFaceNormal(ray, outward_normal);
        // Only one material
        getSphereUV(outward_normal, rec.u, rec.v);
        rec.material = _materials;
        return true;
    }

    void Sphere::getSphereUV(const Lib::Vector3& p, double& u, double& v) const
    {
            // p: a given point on the sphere of radius one, centered at the origin.
            // u: returned value [0,1] of angle around the Y axis from X=-1.
            // v: returned value [0,1] of angle from Y=-1 to Y=+1.
            //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
            //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
            //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

            auto theta = std::acos(-p.y);
            auto phi = std::atan2(-p.z, p.x) + M_PI;

            u = phi / (2*M_PI);
            v = theta / M_PI;
    }

}

namespace Raytracer {

    SphereBuilder::SphereBuilder(Sphere &sphere) : APrimitiveBuilder(sphere), _sphere(sphere)
    {
        // DEBUG << "SphereBuilder constructor";
    }

    SphereBuilder::~SphereBuilder()
    {
        // DEBUG << "SphereBuilder destructor";
    }

    IPrimitiveBuilder &SphereBuilder::set(const std::string &name, const std::vector<std::string> &args)
    {
        DEBUG << "SphereBuilder set " << name;
        if (!_sphere.centerSet) {
            _sphere.setCenter(Ray(_sphere.getPos(), Vector3(0, 0, 0)));
            auto vrad = Lib::Vector3(_sphere.getRadius(), _sphere.getRadius(), _sphere.getRadius());
            _sphere.boundingBox() = AABB(_sphere.getPos() - vrad, _sphere.getPos() + vrad);
        }
        if (name == "radius" || name == "r") {
            if (args.size() != 1)
                return *this;
            float radius = std::stof(args[0]);
            _sphere.setRadius(radius);
        } else if (name == "translation") {
            if (args.size() != 3)
                return *this;
            float x = std::stof(args[0]);
            float y = std::stof(args[1]);
            float z = std::stof(args[2]);

            // for the center
            auto center = Ray(_sphere.getPos(), Vector3(x, y, z) - _sphere.getPos());
            _sphere.setCenter(center);

            // for the bounding box
            auto rvec = Vector3(_sphere.getRadius(), _sphere.getRadius(), _sphere.getRadius());
            AABB box1(_sphere.getCenter().pointAt(0) - rvec, _sphere.getCenter().pointAt(0) + rvec);
            AABB box2(_sphere.getCenter().pointAt(1) - rvec, _sphere.getCenter().pointAt(1) + rvec);
            _sphere.boundingBox() = AABB(box1, box2);
            _sphere.centerSet = true;
        } else {
            DEBUG << "SphereBuilder set: unknown property " << name;
        }
        return *this;
    }



    extern "C" std::shared_ptr<Sphere> createPrimitive(void)
    {
        return std::make_shared<Sphere>();
    }
}