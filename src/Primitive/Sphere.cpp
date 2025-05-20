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

    void Sphere::display(size_t level)
    {
        std::string indent(level * 4, ' ');
        std::cout << "Sphere data:" << std::endl;
        std::cout << indent << "- Position: " << _pos << std::endl;
        std::cout << indent << "- Materials: (" << _materials.size() << ")" << std::endl;
        for (const auto &pair: _materials) {
            std::cout << indent << "    - ";// << pair.first << ": ";
            pair.second->display(level + 2);
        }
        if (_materials.empty())
            std::cout << indent << "    No materials" << std::endl;
        std::cout << indent << "- Transformations: (" << _transformations.size() << ")" << std::endl;
        for (const auto &pair: _transformations) {
            std::cout << indent << "    - ";// << pair.first << ": ";
            pair.second->display(level + 2);
        }
        if (_transformations.empty())
            std::cout << indent << "    No transformations" << std::endl;
        std::cout << indent << "- Radius: " << _radius << std::endl;
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
        // Apply transformations to the ray (same as in BoxPlane::hit)
        Ray transformed_ray = ray;
        for (const auto &[type, transfo] : _transformations) {
            transfo->compute(transformed_ray);
        }

        // Original hit calculation with the transformed ray
        Vector3 current_center = _center.pointAt(transformed_ray.getTime());
        Vector3 oc = current_center - transformed_ray.origin();
        auto a = transformed_ray.direction().length_squared();
        auto h = dot(transformed_ray.direction(), oc);
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

        // Calculate intersection properties
        rec.t = root;
        rec.p = transformed_ray.pointAt(rec.t);
        Vector3 outward_normal = (rec.p - current_center) / _radius;
        rec.setFaceNormal(transformed_ray, outward_normal);
        getSphereUV(outward_normal, rec.u, rec.v);
        rec.material = _materials;

        // Transform the intersection point and normal back to world space
        for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
            const auto& [type, transfo] = *it;
            transfo->decompute(rec);
        }
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

    void Sphere::init(void)
    {
        if (!centerSet) {
            _center = Ray(_pos, Vector3(0, 0, 0));
            auto vrad = Lib::Vector3(_radius, _radius, _radius);
            _bbox = AABB(_pos - vrad, _pos + vrad);

            // Apply transformations to the bounding box (same as in BoxPlane::setBoundingBox)
            for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
                const auto& [type, transfo] = *it;
                transfo->newBoundingBox(_bbox);
            }
        }
    }

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

        if (name == "radius" || name == "r") {
            if (args.size() != 1)
                return *this;
            float radius = std::stof(args[0]);
            _sphere.setRadius(radius);
        } /* else if (name == "translation") {
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
            _sphere.centerSet = true; */
         else {
            DEBUG << "SphereBuilder set: unknown property " << name;
        }
        return *this;
    }

    extern "C" std::shared_ptr<Sphere> createPrimitive(void)
    {
        return std::make_shared<Sphere>();
    }
}