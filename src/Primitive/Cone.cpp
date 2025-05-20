/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Cone class implementation
*/
/**
 * @file Cone.cpp
 * @brief Cone class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Cone.hpp"
using namespace Lib;

namespace Raytracer {
    Cone::Cone()
    {
        // DEBUG << "Cone constructor";
        _radius = 1.0;
        _height = 2.0;
        _axis = Vector3(0, 1, 0); // Default y-axis aligned
    }

    Cone::~Cone()
    {
        // DEBUG << "Cone destructor";
    }

    std::unique_ptr<IPrimitiveBuilder> &Cone::getBuilder(void)
    {
        // DEBUG << "Cone getBuilder";
        if (!_builder)
            _builder = std::make_unique<ConeBuilder>(*this);
        return _builder;
    }

    void Cone::display(size_t level)
    {
        std::string indent(level * 4, ' ');
        std::cout << indent << "Cone data:" << std::endl;
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

    float& Cone::getRadius(void)
    {
        return _radius;
    }

    const float& Cone::getRadius(void) const
    {
        return _radius;
    }

    void Cone::setRadius(const float &radius)
    {
        _radius = radius;
    }

    float& Cone::getHeight(void)
    {
        return _height;
    }

    const float& Cone::getHeight(void) const
    {
        return _height;
    }

    void Cone::setHeight(const float &height)
    {
        _height = height;
    }

    void Cone::setAxis(const Vector3 &axis)
    {
        _axis = unit_vector(axis);
    }

    Vector3& Cone::getAxis(void)
    {
        return _axis;
    }

    const Vector3& Cone::getAxis(void) const
    {
        return _axis;
    }

    void Cone::setBoundingBox()
    {
        // Create a local coordinate system with _axis as one of the axes
        Vector3 u, v;
        if (std::abs(_axis.x) > 0.9)
            u = Vector3(0, 1, 0);
        else
            u = Vector3(1, 0, 0);
        
        u = unit_vector(u - dot(u, _axis) * _axis);
        v = cross(_axis, u);
        
        // Create the bounding box
        Vector3 min_corner = _pos - u * _radius - v * _radius;
        Vector3 max_corner = _pos + u * _radius + v * _radius + _axis * _height;
        
        _bbox = AABB(min_corner, max_corner);
        
        // Apply transformations to the bounding box
        for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
            const auto& [type, transfo] = *it;
            transfo->newBoundingBox(_bbox);
        }
    }

    bool Cone::hit(const Ray& ray, Interval rayT, Intersection& rec) const
{
    // Apply transformations to the ray
    Ray transformed_ray = ray;
    for (const auto &[type, transfo] : _transformations) {
        transfo->compute(transformed_ray);
    }
    
    // Setup for computational convenience
    Vector3 origin = transformed_ray.origin();
    Vector3 direction = transformed_ray.direction();
    
    // Apex is at base position + height * axis
    Vector3 apex = _pos + _height * _axis;
    Vector3 base_center = _pos;
    
    // Keep track of the closest intersection
    double closest_t = rayT.max;
    bool hit_anything = false;
    Intersection temp_rec;
    
    // 1. Check intersection with the cone surface
    
    // Calculate slope of the cone (tangent of half-angle)
    double k = _radius / _height;
    double k2 = k * k;
    
    // Vector from apex to ray origin
    Vector3 oc = origin - apex;
    
    // Components for the quadratic equation for cone
    double dot_dir_axis = dot(direction, _axis);
    double dot_oc_axis = dot(oc, _axis);
    
    double a = dot(direction, direction) - (1 + k2) * dot_dir_axis * dot_dir_axis;
    double b = 2 * (dot(oc, direction) - (1 + k2) * dot_oc_axis * dot_dir_axis);
    double c = dot(oc, oc) - (1 + k2) * dot_oc_axis * dot_oc_axis;
    
    // Check if ray might hit the cone
    bool hit_cone_surface = false;
    double t_cone = closest_t;
    
    if (std::abs(a) > 1e-8) {  // Not parallel to cone surface
        double discriminant = b * b - 4 * a * c;
        
        if (discriminant >= 0) {
            double sqrtd = sqrt(discriminant);
            double t0 = (-b - sqrtd) / (2 * a);
            double t1 = (-b + sqrtd) / (2 * a);
            
            if (t0 > t1) std::swap(t0, t1);
            
            // Check both potential intersections
            for (double t : {t0, t1}) {
                if (!rayT.contains(t) || t >= closest_t)
                    continue;
                
                // Hit point
                Vector3 hit_point = transformed_ray.pointAt(t);
                
                // Check if hit is within cone height
                double height_proj = dot(hit_point - apex, -_axis);
                
                if (height_proj < 0 || height_proj > _height)
                    continue;
                
                // Check if the hit point is inside the cone profile
                Vector3 hit_local = hit_point - apex;
                double r_at_height = k * height_proj;
                
                Vector3 axis_proj = height_proj * (-_axis);
                Vector3 radial_vec = hit_local - axis_proj;
                
                if (radial_vec.length_squared() <= r_at_height * r_at_height) {
                    hit_cone_surface = true;
                    t_cone = t;
                    break;  // Found closest valid intersection with cone surface
                }
            }
        }
    }
    
    // If we hit the cone surface
    if (hit_cone_surface) {
        closest_t = t_cone;
        hit_anything = true;
        
        Vector3 hit_point = transformed_ray.pointAt(t_cone);
        
        // Distance from apex along axis direction
        double height_proj = dot(hit_point - apex, -_axis);
        
        // Position on axis at this height
        Vector3 axis_point = apex + height_proj * (-_axis);
        
        // Vector from axis to hit point
        Vector3 axis_to_hit = hit_point - axis_point;
        
        // Normal calculation - perpendicular to both cone slant and circle at hit height
        Vector3 outward_normal;
        
        // Compute the normal using the cone's geometry
        // The normal is perpendicular to both:
        // 1. The circle at the hit point height (cross with axis)
        // 2. And along the cone slant
        
        // First calculate a tangent to the circle
        Vector3 tangent = cross(_axis, axis_to_hit);
        
        // Then calculate normal perpendicular to both tangent and slant
        if (tangent.length_squared() > 1e-8) {
            Vector3 slant_dir = unit_vector(axis_to_hit - k * height_proj * _axis);
            outward_normal = cross(tangent, slant_dir);
            outward_normal = unit_vector(outward_normal);
        } else {
            // Fallback if tangent calculation fails (e.g., hit point on axis)
            outward_normal = unit_vector(axis_to_hit);
        }
        
        temp_rec.t = t_cone;
        temp_rec.p = hit_point;
        temp_rec.setFaceNormal(transformed_ray, outward_normal);
        
        // Calculate UV coordinates
        double angle = atan2(dot(axis_to_hit, cross(_axis, Vector3(1, 0, 0))), 
                             dot(axis_to_hit, Vector3(1, 0, 0)));
        if (angle < 0) angle += 2 * M_PI;
        
        temp_rec.u = angle / (2 * M_PI);
        temp_rec.v = height_proj / _height;
        temp_rec.material = _materials;
    }
    
    // 2. Check intersection with the base circle (at _pos)
    bool hit_base = false;
    double t_base = closest_t;
    
    // If ray direction has non-zero component along axis
    double denom = dot(direction, _axis);
    if (std::abs(denom) > 1e-8) {
        double t = dot(base_center - origin, _axis) / denom;
        
        if (rayT.contains(t) && t < closest_t) {
            Vector3 hit_point = transformed_ray.pointAt(t);
            Vector3 base_to_hit = hit_point - base_center;
            
            // Remove axis component to get projection onto base plane
            Vector3 base_to_hit_proj = base_to_hit - dot(base_to_hit, _axis) * _axis;
            
            // Check if hit point is within base circle radius
            if (base_to_hit_proj.length_squared() <= _radius * _radius) {
                hit_base = true;
                t_base = t;
            }
        }
    }
    
    // If we hit the base and it's closer than any previous hit
    if (hit_base && t_base < closest_t) {
        closest_t = t_base;
        hit_anything = true;
        
        Vector3 hit_point = transformed_ray.pointAt(t_base);
        
        temp_rec.t = t_base;
        temp_rec.p = hit_point;
        temp_rec.setFaceNormal(transformed_ray, -_axis); // Base normal points opposite to axis
        
        // Calculate UV coordinates for the base circle
        Vector3 base_to_hit = hit_point - base_center;
        Vector3 base_to_hit_proj = base_to_hit - dot(base_to_hit, _axis) * _axis;
        
        // Create a consistent local coordinate system
        Vector3 base_u, base_v;
        if (std::abs(_axis.x) > 0.9)
            base_u = Vector3(0, 1, 0);
        else
            base_u = Vector3(1, 0, 0);
        
        base_u = unit_vector(base_u - dot(base_u, _axis) * _axis);
        base_v = cross(_axis, base_u);
        
        // Map to UV coordinates [0,1] x [0,1]
        double x_coord = dot(base_to_hit_proj, base_u);
        double z_coord = dot(base_to_hit_proj, base_v);
        
        temp_rec.u = (x_coord / _radius + 1) * 0.5;
        temp_rec.v = (z_coord / _radius + 1) * 0.5;
        temp_rec.material = _materials;
    }
    
    // If we hit something, set the record and apply inverse transformations
    if (hit_anything) {
        rec = temp_rec;
        
        // Apply inverse transformations
        for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
            const auto& [type, transfo] = *it;
            transfo->decompute(rec);
        }
        return true;
    }
    
    return false;
}

    void Cone::getConeUV(const Vector3& p, double& u, double& v) const
    {
        // Get local coordinates
        Vector3 local_p = p - _pos;
        
        // Project to the plane perpendicular to axis
        Vector3 projected = local_p - dot(local_p, _axis) * _axis;
        
        // Calculate phi angle around axis
        double phi = atan2(dot(projected, cross(_axis, Vector3(1, 0, 0))), dot(projected, Vector3(1, 0, 0)));
        if (phi < 0) phi += 2 * M_PI;
        
        // Calculate height along axis
        double height_proj = dot(local_p, _axis);
        
        u = phi / (2 * M_PI);
        v = height_proj / _height;
    }

    void Cone::init(void)
    {
        // DEBUG << "Cone init";
        setBoundingBox();
    }

    ConeBuilder::ConeBuilder(Cone &cone) : APrimitiveBuilder(cone), _cone(cone)
    {
        // DEBUG << "ConeBuilder constructor";
    }

    ConeBuilder::~ConeBuilder()
    {
        // DEBUG << "ConeBuilder destructor";
    }

    IPrimitiveBuilder &ConeBuilder::set(const std::string &name, const std::vector<std::string> &args)
    {
        DEBUG << "ConeBuilder set " << name;

        if (name == "radius" || name == "r") {
            if (args.size() != 1)
                return *this;
            float radius = std::stof(args[0]);
            _cone.setRadius(radius);
        } else if (name == "height" || name == "h") {
            if (args.size() != 1)
                return *this;
            float height = std::stof(args[0]);
            _cone.setHeight(height);
        } else if (name == "axis" || name == "direction") {
            if (args.size() != 3)
                return *this;
            float x = std::stof(args[0]);
            float y = std::stof(args[1]);
            float z = std::stof(args[2]);
            _cone.setAxis(Vector3(x, y, z));
        } else {
            DEBUG << "ConeBuilder set: unknown property " << name;
        }
        return *this;
    }

    extern "C" std::shared_ptr<Cone> createPrimitive(void)
    {
        return std::make_shared<Cone>();
    }
}