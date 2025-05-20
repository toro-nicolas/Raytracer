/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Triangle class implementation
*/
/**
 * @file Triangle.cpp
 * @brief The Triangle class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Triangle.hpp"
using namespace Lib;

namespace Raytracer {
    Triangle::Triangle()
    {
        // DEBUG << "Triangle constructor";
        _v1 = Vector3(-1, 0, 0);  // Default triangle in xz plane
        _v2 = Vector3(1, 0, 0);
        _v3 = Vector3(0, 0, 1);
        _normal = Vector3(0, 1, 0);  // Initial normal (will be calculated in init)
    }

    Triangle::~Triangle()
    {
        // DEBUG << "Triangle destructor";
    }

    std::unique_ptr<IPrimitiveBuilder> &Triangle::getBuilder(void)
    {
        // DEBUG << "Triangle getBuilder";
        if (!_builder)
            _builder = std::make_unique<TriangleBuilder>(*this);
        return _builder;
    }

    void Triangle::display(size_t level)
    {
        std::string indent(level * 4, ' ');
        std::cout << "Triangle data:" << std::endl;
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
        std::cout << indent << "- Vertex 1: " << _v1 << std::endl;
        std::cout << indent << "- Vertex 2: " << _v2 << std::endl;
        std::cout << indent << "- Vertex 3: " << _v3 << std::endl;
        std::cout << indent << "- Normal: " << _normal << std::endl;
    }

    Vector3 &Triangle::getVertex1(void)
    {
        return _v1;
    }

    const Vector3 &Triangle::getVertex1(void) const
    {
        return _v1;
    }

    void Triangle::setVertex1(const Vector3 &vertex)
    {
        _v1 = vertex;
    }

    Vector3 &Triangle::getVertex2(void)
    {
        return _v2;
    }

    const Vector3 &Triangle::getVertex2(void) const
    {
        return _v2;
    }

    void Triangle::setVertex2(const Vector3 &vertex)
    {
        _v2 = vertex;
    }

    Vector3 &Triangle::getVertex3(void)
    {
        return _v3;
    }

    const Vector3 &Triangle::getVertex3(void) const
    {
        return _v3;
    }

    void Triangle::setVertex3(const Vector3 &vertex)
    {
        _v3 = vertex;
    }

    void Triangle::setBoundingBox()
    {
        // Calculate the bounding box that encompasses all vertices
        // The vertices are in world space (relative to _pos)
        Vector3 v1 = _pos + _v1;
        Vector3 v2 = _pos + _v2;
        Vector3 v3 = _pos + _v3;
        
        // Find the minimum and maximum coordinates
        float min_x = std::min({v1.x, v2.x, v3.x});
        float min_y = std::min({v1.y, v2.y, v3.y});
        float min_z = std::min({v1.z, v2.z, v3.z});
        
        float max_x = std::max({v1.x, v2.x, v3.x});
        float max_y = std::max({v1.y, v2.y, v3.y});
        float max_z = std::max({v1.z, v2.z, v3.z});
        
        // Create the bounding box with a small padding
        const float padding = 0.001; // Small padding to avoid precision issues
        Vector3 min_corner(min_x - padding, min_y - padding, min_z - padding);
        Vector3 max_corner(max_x + padding, max_y + padding, max_z + padding);
        
        _bbox = AABB(min_corner, max_corner);
        
        // Apply transformations to the bounding box
        for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
            const auto& [type, transfo] = *it;
            transfo->newBoundingBox(_bbox);
        }
    }

    bool Triangle::hit(const Ray& ray, Interval rayT, Intersection& rec) const
    {
        // Apply transformations to the ray
        Ray transformed_ray = ray;
        for (const auto &[type, transfo] : _transformations) {
            transfo->compute(transformed_ray);
        }
        
        // Get ray origin and direction
        Vector3 origin = transformed_ray.origin();
        Vector3 direction = transformed_ray.direction();
        
        // Get triangle vertices in world space
        Vector3 v1 = _pos + _v1;
        Vector3 v2 = _pos + _v2;
        Vector3 v3 = _pos + _v3;
        
        // Implement Möller–Trumbore algorithm for triangle intersection
        Vector3 edge1 = v2 - v1;
        Vector3 edge2 = v3 - v1;
        Vector3 h = cross(direction, edge2);
        float a = dot(edge1, h);
        
        // Check if ray is parallel to triangle
        if (std::abs(a) < 1e-8)
            return false;
        
        float f = 1.0f / a;
        Vector3 s = origin - v1;
        float u = f * dot(s, h);
        
        // Check if intersection is outside the triangle
        if (u < 0.0f || u > 1.0f)
            return false;
        
        Vector3 q = cross(s, edge1);
        float v = f * dot(direction, q);
        
        // Check if intersection is outside the triangle
        if (v < 0.0f || u + v > 1.0f)
            return false;
        
        // Calculate intersection distance
        float t = f * dot(edge2, q);
        
        // Check if intersection is within the valid range
        if (!rayT.contains(t))
            return false;
        
        // Valid intersection found
        rec.t = t;
        rec.p = transformed_ray.pointAt(t);
        
        // Calculate normal (constant for triangles)
        Vector3 outward_normal = unit_vector(cross(edge1, edge2));
        rec.setFaceNormal(transformed_ray, outward_normal);
        
        // Calculate UV coordinates using barycentric coordinates
        rec.u = u;
        rec.v = v;
        rec.material = _materials;
        
        // Apply inverse transformations
        for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
            const auto& [type, transfo] = *it;
            transfo->decompute(rec);
        }
        
        return true;
    }

    void Triangle::getTriangleUV(const Vector3& p, double& u, double& v) const
    {
        // This is not used since UV coordinates are calculated in the hit method
        // using barycentric coordinates
        (void)p;
        u = 0.0;
        v = 0.0;
    }

    void Triangle::init(void)
    {
        // DEBUG << "Triangle init";
        // Calculate normal vector
        Vector3 edge1 = _v2 - _v1;
        Vector3 edge2 = _v3 - _v1;
        _normal = unit_vector(cross(edge1, edge2));
        
        // Set up bounding box
        setBoundingBox();
    }

    TriangleBuilder::TriangleBuilder(Triangle &triangle) : APrimitiveBuilder(triangle), _triangle(triangle)
    {
        // DEBUG << "TriangleBuilder constructor";
    }

    TriangleBuilder::~TriangleBuilder()
    {
        // DEBUG << "TriangleBuilder destructor";
    }

    IPrimitiveBuilder &TriangleBuilder::set(const std::string &name, const std::vector<std::string> &args)
    {
        DEBUG << "TriangleBuilder set " << name;

        if (name == "vertex1" || name == "v1") {
            if (args.size() != 3)
                return *this;
            float x = std::stof(args[0]);
            float y = std::stof(args[1]);
            float z = std::stof(args[2]);
            _triangle.setVertex1(Vector3(x, y, z));
        } else if (name == "vertex2" || name == "v2") {
            if (args.size() != 3)
                return *this;
            float x = std::stof(args[0]);
            float y = std::stof(args[1]);
            float z = std::stof(args[2]);
            _triangle.setVertex2(Vector3(x, y, z));
        } else if (name == "vertex3" || name == "v3") {
            if (args.size() != 3)
                return *this;
            float x = std::stof(args[0]);
            float y = std::stof(args[1]);
            float z = std::stof(args[2]);
            _triangle.setVertex3(Vector3(x, y, z));
        } else {
            DEBUG << "TriangleBuilder set: unknown property " << name;
        }
        return *this;
    }

    extern "C" std::shared_ptr<Triangle> createPrimitive(void)
    {
        return std::make_shared<Triangle>();
    }
}