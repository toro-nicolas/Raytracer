/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Torus class implementation
*/
/**
 * @file Torus.cpp
 * @brief The Torus class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Torus.hpp"
using namespace Lib;

namespace Raytracer {
    Torus::Torus()
    {
        // DEBUG << "Torus constructor";
        _majorRadius = 2.0;
        _minorRadius = 0.5;
        _axis = Vector3(0, 1, 0); // Default y-axis aligned
    }

    Torus::~Torus()
    {
        // DEBUG << "Torus destructor";
    }

    std::unique_ptr<IPrimitiveBuilder> &Torus::getBuilder(void)
    {
        // DEBUG << "Torus getBuilder";
        if (!_builder)
            _builder = std::make_unique<TorusBuilder>(*this);
        return _builder;
    }

    void Torus::display(size_t level)
    {
        std::string indent(level * 4, ' ');
        std::cout << "Torus data:" << std::endl;
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
        std::cout << indent << "- Major Radius: " << _majorRadius << std::endl;
        std::cout << indent << "- Minor Radius: " << _minorRadius << std::endl;
        std::cout << indent << "- Axis: " << _axis << std::endl;
    }

    float& Torus::getMajorRadius(void)
    {
        return _majorRadius;
    }

    const float& Torus::getMajorRadius(void) const
    {
        return _majorRadius;
    }

    void Torus::setMajorRadius(const float &radius)
    {
        _majorRadius = radius;
    }

    float& Torus::getMinorRadius(void)
    {
        return _minorRadius;
    }

    const float& Torus::getMinorRadius(void) const
    {
        return _minorRadius;
    }

    void Torus::setMinorRadius(const float &radius)
    {
        _minorRadius = radius;
    }

    void Torus::setAxis(const Vector3 &axis)
    {
        _axis = unit_vector(axis);
    }

    Vector3& Torus::getAxis(void)
    {
        return _axis;
    }

    const Vector3& Torus::getAxis(void) const
    {
        return _axis;
    }

    void Torus::setBoundingBox()
    {
        // The bounding box of a torus is a cube with side length 2*(majorRadius + minorRadius)
        float total_radius = _majorRadius + _minorRadius;
        
        // Create a local coordinate system with _axis as one of the axes
        Vector3 u, v;
        if (std::abs(_axis.x) > 0.9)
            u = Vector3(0, 1, 0);
        else
            u = Vector3(1, 0, 0);
        
        u = unit_vector(u - dot(u, _axis) * _axis);
        v = cross(_axis, u);
        
        // Create the bounding box
        Vector3 min_corner = _pos - u * total_radius - v * total_radius - _axis * _minorRadius;
        Vector3 max_corner = _pos + u * total_radius + v * total_radius + _axis * _minorRadius;
        
        _bbox = AABB(min_corner, max_corner);
        
        // Apply transformations to the bounding box
        for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
            const auto& [type, transfo] = *it;
            transfo->newBoundingBox(_bbox);
        }
    }

    bool Torus::hit(const Ray& ray, Interval rayT, Intersection& rec) const
    {
        // Apply transformations to the ray
        Ray transformed_ray = ray;
        for (const auto &[type, transfo] : _transformations) {
            transfo->compute(transformed_ray);
        }
        
        // Get ray origin and direction
        Vector3 origin = transformed_ray.origin() - _pos;
        Vector3 direction = transformed_ray.direction();
        
        // Create a local coordinate system
        Vector3 w = unit_vector(_axis);
        Vector3 u, v;
        
        if (std::abs(w.x) > 0.9)
            u = Vector3(0, 1, 0);
        else
            u = Vector3(1, 0, 0);
        
        u = unit_vector(u - dot(u, w) * w);
        v = cross(w, u);
        
        // Constants
        double R = _majorRadius;
        double r = _minorRadius;
        double R2 = R * R;
        double r2 = r * r;
        
        // Utiliser une approche de recherche numérique
        // Nous allons échantillonner le rayon à intervalles réguliers pour trouver les intersections
        
        const int MAX_SAMPLES = 100;
        const double t_step = (rayT.max - rayT.min) / MAX_SAMPLES;
        
        double closest_t = rayT.max;
        bool hit_found = false;
        
        // Fonction implicite du tore
        auto torus_func = [&](double t) {
            Vector3 p = origin + t * direction;
            double h = dot(p, w);
            Vector3 planar = p - h * w;
            double planar_dist2 = planar.length_squared();
            
            // f(p) = (|p|^2 + R^2 - r^2)^2 - 4*R^2*(|p_xy|^2)
            return std::pow(p.length_squared() + R2 - r2, 2) - 4.0 * R2 * planar_dist2;
        };
        
        // Recherche d'intersection par échantillonnage
        for (int i = 0; i < MAX_SAMPLES; i++) {
            double t1 = rayT.min + i * t_step;
            double t2 = t1 + t_step;
            
            double f1 = torus_func(t1);
            double f2 = torus_func(t2);
            
            // Si le signe change, nous avons trouvé une intersection
            if (f1 * f2 <= 0) {
                // Affiner par bissection
                for (int j = 0; j < 10; j++) {
                    double t_mid = (t1 + t2) / 2.0;
                    double f_mid = torus_func(t_mid);
                    
                    if (f_mid * f1 <= 0) {
                        t2 = t_mid;
                        f2 = f_mid;
                    } else {
                        t1 = t_mid;
                        f1 = f_mid;
                    }
                }
                
                double t = (t1 + t2) / 2.0;
                if (t < closest_t && t > rayT.min) {
                    closest_t = t;
                    hit_found = true;
                }
            }
        }
        
        if (!hit_found)
            return false;
        
        // Calculate hit point
        Vector3 hit_point = transformed_ray.pointAt(closest_t);
        Vector3 local_hit = hit_point - _pos;
        
        // Project to torus plane
        double height = dot(local_hit, w);
        Vector3 planar = local_hit - height * w;
        double planar_dist = planar.length();
        
        // Get direction to ring center
        Vector3 to_ring_center;
        if (planar_dist > 1e-6) {
            to_ring_center = planar / planar_dist;
        } else {
            to_ring_center = u;
        }
        
        // Normal is from the closest point on the ring axis to the hit point
        Vector3 ring_center = _pos + R * to_ring_center;
        Vector3 outward_normal = unit_vector(hit_point - ring_center);
        
        // Set intersection record
        rec.t = closest_t;
        rec.p = hit_point;
        rec.setFaceNormal(transformed_ray, outward_normal);
        
        // Calculate UV coordinates
        getTorusUV(local_hit, rec.u, rec.v);
        rec.material = _materials;
        
        // Apply inverse transformations
        for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
            const auto& [type, transfo] = *it;
            transfo->decompute(rec);
        }
        
        return true;
    }

    void Torus::getTorusUV(const Vector3& p, double& u, double& v) const
    {
        // Create a local coordinate system
        Vector3 w = _axis;
        Vector3 u_axis, v_axis;
        
        if (std::abs(w.x) > 0.9)
            u_axis = Vector3(0, 1, 0);
        else
            u_axis = Vector3(1, 0, 0);
        
        u_axis = unit_vector(u_axis - dot(u_axis, w) * w);
        v_axis = cross(w, u_axis);
        
        // Project to torus plane
        double height = dot(p, w);
        Vector3 planar = p - height * w;
        double planar_dist = planar.length();
        
        // Calculate phi (angle around the axis)
        double phi = atan2(dot(planar, v_axis), dot(planar, u_axis));
        if (phi < 0) phi += 2 * M_PI;
        
        // Calculate theta (angle around the tube)
        double theta = atan2(height, planar_dist - _majorRadius);
        if (theta < 0) theta += 2 * M_PI;
        
        // Map to [0,1] range
        u = phi / (2 * M_PI);
        v = theta / (2 * M_PI);
    }

    void Torus::init(void)
    {
        // DEBUG << "Torus init";
        setBoundingBox();
    }

    TorusBuilder::TorusBuilder(Torus &torus) : APrimitiveBuilder(torus), _torus(torus)
    {
        // DEBUG << "TorusBuilder constructor";
    }

    TorusBuilder::~TorusBuilder()
    {
        // DEBUG << "TorusBuilder destructor";
    }

    IPrimitiveBuilder &TorusBuilder::set(const std::string &name, const std::vector<std::string> &args)
    {
        DEBUG << "TorusBuilder set " << name;

        if (name == "majorRadius" || name == "R") {
            if (args.size() != 1)
                return *this;
            float radius = std::stof(args[0]);
            _torus.setMajorRadius(radius);
        } else if (name == "minorRadius" || name == "r") {
            if (args.size() != 1)
                return *this;
            float radius = std::stof(args[0]);
            _torus.setMinorRadius(radius);
        } else if (name == "axis" || name == "direction") {
            if (args.size() != 3)
                return *this;
            float x = std::stof(args[0]);
            float y = std::stof(args[1]);
            float z = std::stof(args[2]);
            _torus.setAxis(Vector3(x, y, z));
        } else {
            DEBUG << "TorusBuilder set: unknown property " << name;
        }
        return *this;
    }

    extern "C" std::shared_ptr<Torus> createPrimitive(void)
    {
        return std::make_shared<Torus>();
    }
}