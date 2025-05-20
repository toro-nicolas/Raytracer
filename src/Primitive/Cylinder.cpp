/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Cylinder class implementation
*/
/**
 * @file Cylinder.cpp
 * @brief The Cylinder class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Cylinder.hpp"
using namespace Lib;

namespace Raytracer {
    Cylinder::Cylinder()
    {
        // DEBUG << "Cylinder constructor";
        _radius = 1.0;
        _height = 2.0;
        _axis = Vector3(0, 1, 0); // Default y-axis aligned
    }

    Cylinder::~Cylinder()
    {
        // DEBUG << "Cylinder destructor";
    }

    std::unique_ptr<IPrimitiveBuilder> &Cylinder::getBuilder(void)
    {
        // DEBUG << "Cylinder getBuilder";
        if (!_builder)
            _builder = std::make_unique<CylinderBuilder>(*this);
        return _builder;
    }

    void Cylinder::display(size_t level)
    {
        std::string indent(level * 4, ' ');
        std::cout << indent << "Cylinder data:" << std::endl;
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
        std::cout << indent << "- Radius: " << _radius << std::endl;
        std::cout << indent << "- Height: " << _height << std::endl;
        std::cout << indent << "- Axis: " << _axis << std::endl;
    }

    float& Cylinder::getRadius(void)
    {
        return _radius;
    }

    const float& Cylinder::getRadius(void) const
    {
        return _radius;
    }

    void Cylinder::setRadius(const float &radius)
    {
        _radius = radius;
    }

    float& Cylinder::getHeight(void)
    {
        return _height;
    }

    const float& Cylinder::getHeight(void) const
    {
        return _height;
    }

    void Cylinder::setHeight(const float &height)
    {
        _height = height;
    }

    void Cylinder::setAxis(const Vector3 &axis)
    {
        _axis = unit_vector(axis);
    }

    Vector3& Cylinder::getAxis(void)
    {
        return _axis;
    }

    const Vector3& Cylinder::getAxis(void) const
    {
        return _axis;
    }

    void Cylinder::setBoundingBox()
    {
        // Create a local coordinate system with _axis as one of the axes
        Vector3 u, v;
        if (std::abs(_axis.x) > 0.9)
            u = Vector3(0, 1, 0);
        else
            u = Vector3(1, 0, 0);
        
        u = unit_vector(u - dot(u, _axis) * _axis);
        v = cross(_axis, u);
        
        // Create the bounding box in local space
        Vector3 extents(_radius, _height / 2, _radius);
        Vector3 min_corner = _pos - u * _radius - v * _radius - _axis * (_height / 2);
        Vector3 max_corner = _pos + u * _radius + v * _radius + _axis * (_height / 2);
        
        _bbox = AABB(min_corner, max_corner);
        
        // Apply transformations to the bounding box
        for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
            const auto& [type, transfo] = *it;
            transfo->newBoundingBox(_bbox);
        }
    }

    bool Cylinder::hit(const Ray& ray, Interval rayT, Intersection& rec) const
{
    // Apply transformations to the ray
    Ray transformed_ray = ray;
    for (const auto &[type, transfo] : _transformations) {
        transfo->compute(transformed_ray);
    }
    
    // First, check if ray is parallel to cylinder axis
    double dot_dir_axis = dot(transformed_ray.direction(), _axis);
    Vector3 oc = transformed_ray.origin() - _pos;
    
    // Project ray origin and direction onto plane perpendicular to cylinder axis
    Vector3 oc_perp = oc - dot(oc, _axis) * _axis;
    Vector3 dir_perp = transformed_ray.direction() - dot_dir_axis * _axis;
    
    // Calculate quadratic coefficients
    double a = dir_perp.length_squared();
    double half_b = dot(oc_perp, dir_perp);
    double c = oc_perp.length_squared() - _radius * _radius;
    
    // Check if ray is almost parallel to cylinder and misses it
    if (a < 1e-8)
        return false;
    
    // Calculate discriminant
    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return false;
    
    // Calculate the nearest root that lies in the acceptable range
    double sqrtd = sqrt(discriminant);
    double root = (-half_b - sqrtd) / a;
    
    if (!rayT.contains(root)) {
        root = (-half_b + sqrtd) / a;
        if (!rayT.contains(root))
            return false;
    }
    
    // Calculate the hit point
    Vector3 hit_point = transformed_ray.pointAt(root);
    
    // Calculate height along axis
    double hit_height = dot(hit_point - _pos, _axis);
    
    // Check if hit point is within cylinder height limits
    if (hit_height < 0 || hit_height > _height) {
        // If we've hit the infinite cylinder but outside the height range,
        // we need to check the caps
        
        // Try bottom cap
        if (std::abs(dot_dir_axis) > 1e-8) {  // Not parallel to cap
            double t_bottom = (0 - dot(transformed_ray.origin() - _pos, _axis)) / dot_dir_axis;
            
            if (rayT.contains(t_bottom)) {
                Vector3 p = transformed_ray.pointAt(t_bottom);
                Vector3 v = p - _pos;
                Vector3 v_perp = v - dot(v, _axis) * _axis;
                
                if (v_perp.length_squared() <= _radius * _radius) {
                    // Hit the bottom cap
                    rec.t = t_bottom;
                    rec.p = p;
                    rec.setFaceNormal(transformed_ray, -_axis);
                    getCylinderUV(p, rec.u, rec.v);
                    rec.material = _materials;
                    
                    // Apply inverse transformations
                    for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
                        const auto& [type, transfo] = *it;
                        transfo->decompute(rec);
                    }
                    return true;
                }
            }
        }
        
        // Try top cap
        if (std::abs(dot_dir_axis) > 1e-8) {  // Not parallel to cap
            double t_top = (_height - dot(transformed_ray.origin() - _pos, _axis)) / dot_dir_axis;
            
            if (rayT.contains(t_top)) {
                Vector3 p = transformed_ray.pointAt(t_top);
                Vector3 v = p - (_pos + _height * _axis);
                Vector3 v_perp = v - dot(v, _axis) * _axis;
                
                if (v_perp.length_squared() <= _radius * _radius) {
                    // Hit the top cap
                    rec.t = t_top;
                    rec.p = p;
                    rec.setFaceNormal(transformed_ray, _axis);
                    getCylinderUV(p, rec.u, rec.v);
                    rec.material = _materials;
                    
                    // Apply inverse transformations
                    for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
                        const auto& [type, transfo] = *it;
                        transfo->decompute(rec);
                    }
                    return true;
                }
            }
        }
        
        // Didn't hit caps or body
        return false;
    }
    
    // We've hit the cylinder body within height range
    rec.t = root;
    rec.p = hit_point;
    
    // Calculate the normal (points outward from axis)
    Vector3 outward_normal = hit_point - (_pos + hit_height * _axis);
    outward_normal = unit_vector(outward_normal);
    rec.setFaceNormal(transformed_ray, outward_normal);
    
    // Set UV coordinates
    getCylinderUV(hit_point, rec.u, rec.v);
    rec.material = _materials;
    
    // Apply inverse transformations
    for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
        const auto& [type, transfo] = *it;
        transfo->decompute(rec);
    }
    
    return true;
}

void Cylinder::getCylinderUV(const Vector3& p, double& u, double& v) const
{
    // Get point relative to cylinder base
    Vector3 rel_p = p - _pos;
    
    // Height along cylinder axis (normalized to [0,1])
    v = dot(rel_p, _axis) / _height;
    
    // For u coordinate, we need a consistent reference frame
    Vector3 base_u, base_v;
    if (std::abs(_axis.x) > 0.9)
        base_u = Vector3(0, 1, 0);
    else
        base_u = Vector3(1, 0, 0);
    
    base_u = unit_vector(base_u - dot(base_u, _axis) * _axis);
    base_v = cross(_axis, base_u);
    
    // Project point onto plane perpendicular to axis
    Vector3 planar = rel_p - dot(rel_p, _axis) * _axis;
    
    // Calculate angle around cylinder
    double angle = atan2(dot(planar, base_v), dot(planar, base_u));
    if (angle < 0)
        angle += 2 * M_PI;
    
    u = angle / (2 * M_PI);
}

    void Cylinder::init(void)
    {
        // DEBUG << "Cylinder init";
        setBoundingBox();
    }

    CylinderBuilder::CylinderBuilder(Cylinder &cylinder) : APrimitiveBuilder(cylinder), _cylinder(cylinder)
    {
        // DEBUG << "CylinderBuilder constructor";
    }

    CylinderBuilder::~CylinderBuilder()
    {
        // DEBUG << "CylinderBuilder destructor";
    }

    IPrimitiveBuilder &CylinderBuilder::set(const std::string &name, const std::vector<std::string> &args)
    {
        DEBUG << "CylinderBuilder set " << name;

        if (name == "radius" || name == "r") {
            if (args.size() != 1)
                return *this;
            float radius = std::stof(args[0]);
            _cylinder.setRadius(radius);
        } else if (name == "height" || name == "h") {
            if (args.size() != 1)
                return *this;
            float height = std::stof(args[0]);
            _cylinder.setHeight(height);
        } else if (name == "axis" || name == "direction") {
            if (args.size() != 3)
                return *this;
            float x = std::stof(args[0]);
            float y = std::stof(args[1]);
            float z = std::stof(args[2]);
            _cylinder.setAxis(Vector3(x, y, z));
        } else {
            DEBUG << "CylinderBuilder set: unknown property " << name;
        }
        return *this;
    }

    extern "C" std::shared_ptr<Cylinder> createPrimitive(void)
    {
        return std::make_shared<Cylinder>();
    }
}