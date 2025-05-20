/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The TangleCube class implementation
*/
/**
 * @file TangleCube.cpp
 * @brief The TangleCube class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Tanglecube.hpp"
using namespace Lib;

namespace Raytracer {
    TangleCube::TangleCube()
    {
        // DEBUG << "TangleCube constructor";
        _size = 1.0;
        _power = 4.0; // Default power for a classic tangle cube (Steiner surface)
    }

    TangleCube::~TangleCube()
    {
        // DEBUG << "TangleCube destructor";
    }

    std::unique_ptr<IPrimitiveBuilder> &TangleCube::getBuilder(void)
    {
        // DEBUG << "TangleCube getBuilder";
        if (!_builder)
            _builder = std::make_unique<TangleCubeBuilder>(*this);
        return _builder;
    }

    void TangleCube::display(size_t level)
    {
        std::string indent(level * 4, ' ');
        std::cout << "TangleCube data:" << std::endl;
        std::cout << indent << "- Position: " << _pos << std::endl;
        std::cout << indent << "- Materials: (" << _materials.size() << ")" << std::endl;
        for (const auto &pair: _materials) {
            std::cout << indent << "    - ";
            pair.second->display(level + 2);
        }
        if (_materials.empty())
            std::cout << indent << "    No materials" << std::endl;
        std::cout << indent << "- Transformations: (" << _transformations.size() << ")" << std::endl;
        for (const auto &pair: _transformations) {
            std::cout << indent << "    - ";
            pair.second->display(level + 2);
        }
        if (_transformations.empty())
            std::cout << indent << "    No transformations" << std::endl;
        std::cout << indent << "- Size: " << _size << std::endl;
        std::cout << indent << "- Power: " << _power << std::endl;
    }

    float& TangleCube::getSize(void)
    {
        return _size;
    }

    const float& TangleCube::getSize(void) const
    {
        return _size;
    }

    void TangleCube::setSize(const float &size)
    {
        _size = size;
    }

    float& TangleCube::getPower(void)
    {
        return _power;
    }

    const float& TangleCube::getPower(void) const
    {
        return _power;
    }

    void TangleCube::setPower(const float &power)
    {
        _power = power;
    }

    void TangleCube::setBoundingBox()
    {
        // The bounding box of a tangle cube is approximately a cube with side length 2*size
        float bound = 2.0 * _size;

        Vector3 min_corner = _pos - Vector3(bound, bound, bound);
        Vector3 max_corner = _pos + Vector3(bound, bound, bound);

        _bbox = AABB(min_corner, max_corner);

        // Apply transformations to the bounding box
        for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
            const auto& [type, transfo] = *it;
            transfo->newBoundingBox(_bbox);
        }
    }

    bool TangleCube::hit(const Ray& ray, Interval rayT, Intersection& rec) const
    {
        // Apply transformations to the ray
        Ray transformed_ray = ray;
        for (const auto &[type, transfo] : _transformations) {
            transfo->compute(transformed_ray);
        }

        // Get ray origin and direction
        Vector3 origin = transformed_ray.origin() - _pos;
        Vector3 direction = transformed_ray.direction();

        // Constants
        double s = _size;
        double p = _power; // Usually 4 for a classic tangle cube

        // Fonction implicite simplifiée pour tangle cube
        auto tangle_func = [s, p, &origin, &direction](double t) {
            Vector3 point = origin + t * direction;
            double x = point.x;
            double y = point.y;
            double z = point.z;

            // Plus simple : x^4 + y^4 + z^4 - s^2*(x^2 + y^2 + z^2)
            double x2 = x*x;
            double y2 = y*y;
            double z2 = z*z;

            return pow(x2, p/2) + pow(y2, p/2) + pow(z2, p/2) - pow(s, 2) * (x2 + y2 + z2);
        };

        // Use numerical approach with less samples for testing
        const int MAX_SAMPLES = 50;
        const double t_step = (rayT.max - rayT.min) / MAX_SAMPLES;

        double closest_t = rayT.max;
        bool hit_found = false;

        // Find intersections by sampling
        double prev_f = tangle_func(rayT.min);
        for (int i = 1; i <= MAX_SAMPLES; i++) {
            double t = rayT.min + i * t_step;
            double curr_f = tangle_func(t);

            // Si le signe change, nous avons trouvé une intersection
            if (prev_f * curr_f <= 0) {
                double t1 = t - t_step;
                double t2 = t;

                // Simple bisection
                for (int j = 0; j < 10; j++) {
                    double t_mid = (t1 + t2) / 2.0;
                    double f_mid = tangle_func(t_mid);

                    if (f_mid * prev_f <= 0) {
                        t2 = t_mid;
                    } else {
                        t1 = t_mid;
                        prev_f = f_mid;
                    }
                }

                double t_hit = (t1 + t2) / 2.0;
                if (t_hit < closest_t && t_hit > rayT.min) {
                    closest_t = t_hit;
                    hit_found = true;
                }
            }

            prev_f = curr_f;
        }

        if (!hit_found)
            return false;

        // Calculate hit point
        Vector3 hit_point = transformed_ray.pointAt(closest_t);
        Vector3 local_hit = hit_point - _pos;

        // Simplified normal calculation - using finite differences
        const double h = 0.01 * _size;
        double fx = tangle_func(closest_t + h) - tangle_func(closest_t);
        double fy = tangle_func(closest_t + h) - tangle_func(closest_t);
        double fz = tangle_func(closest_t + h) - tangle_func(closest_t);

        Vector3 normal(fx, fy, fz);
        Vector3 outward_normal = unit_vector(normal);

        // Set intersection record
        rec.t = closest_t;
        rec.p = hit_point;
        rec.setFaceNormal(transformed_ray, outward_normal);

        // Simple UV mapping
        double phi = atan2(local_hit.z, local_hit.x);
        if (phi < 0) phi += 2 * M_PI;

        double theta = acos(std::clamp(local_hit.y / (local_hit.length() + 1e-6), -1.0, 1.0));

        rec.u = phi / (2 * M_PI);
        rec.v = theta / M_PI;
        rec.material = _materials;

        // Apply inverse transformations
        for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
            const auto& [type, transfo] = *it;
            transfo->decompute(rec);
        }
        
        return true;
    }

    void TangleCube::getTangleCubeUV(const Vector3& p, double& u, double& v) const
    {
        // Calculate UV coordinates based on spherical coordinates
        double phi = atan2(p.z, p.x);
        if (phi < 0) phi += 2 * M_PI;

        double theta = acos(p.y / p.length());

        // Map to [0,1] range
        u = phi / (2 * M_PI);
        v = theta / M_PI;
    }

    void TangleCube::init(void)
    {
        // DEBUG << "TangleCube init";
        setBoundingBox();
    }

    TangleCubeBuilder::TangleCubeBuilder(TangleCube &tangleCube) : APrimitiveBuilder(tangleCube), _tangleCube(tangleCube)
    {
        // DEBUG << "TangleCubeBuilder constructor";
    }

    TangleCubeBuilder::~TangleCubeBuilder()
    {
        // DEBUG << "TangleCubeBuilder destructor";
    }

    IPrimitiveBuilder &TangleCubeBuilder::set(const std::string &name, const std::vector<std::string> &args)
    {
        DEBUG << "TangleCubeBuilder set " << name;

        if (name == "size" || name == "s") {
            if (args.size() != 1)
                return *this;
            float size = std::stof(args[0]);
            _tangleCube.setSize(size);
        } else if (name == "power" || name == "p") {
            if (args.size() != 1)
                return *this;
            float power = std::stof(args[0]);
            _tangleCube.setPower(power);
        } else {
            DEBUG << "TangleCubeBuilder set: unknown property " << name;
        }
        return *this;
    }

    extern "C" std::shared_ptr<TangleCube> createPrimitive(void)
    {
        return std::make_shared<TangleCube>();
    }
}