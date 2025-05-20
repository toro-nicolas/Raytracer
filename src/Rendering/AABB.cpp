/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The AABB class implementation
*/
/**
 * @file AABB.cpp
 * @brief The AABB class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Ray.hpp"

namespace Raytracer {

    AABB::AABB() : x(), y(), z()
    {
    }

    AABB::AABB(const Interval& x, const Interval& y, const Interval& z) : x(x), y(y), z(z)
    {
        padToMinimum();
    }

    AABB::AABB(const Lib::Vector3& a, const Lib::Vector3& b) {
        x = (a.x <= b.x) ? Interval(a.x, b.x) : Interval(b.x, a.x);
        y = (a.y <= b.y) ? Interval(a.y, b.y) : Interval(b.y, a.y);
        z = (a.z <= b.z) ? Interval(a.z, b.z) : Interval(b.z, a.z);

        padToMinimum();
    }

    AABB::AABB(const AABB& box0, const AABB& box1) {
        x = Interval(box0.x, box1.x);
        y = Interval(box0.y, box1.y);
        z = Interval(box0.z, box1.z);
    }

    AABB::~AABB() = default;

    const Interval& AABB::axis_interval(int n) const {
        if (n == 1) return y;
        if (n == 2) return z;
        return x;
    }

    bool AABB::hit(const Ray& r, Interval& ray_t) const {
        const Lib::Vector3& ray_orig = r.origin();
        const Lib::Vector3& ray_dir  = r.direction();

        for (int axis = 0; axis < 3; axis++) {
            const Interval& ax = axis_interval(axis);
            const double adinv = 1.0 / ray_dir[axis];

            auto t0 = (ax.min - ray_orig[axis]) * adinv;
            auto t1 = (ax.max - ray_orig[axis]) * adinv;

            if (t0 < t1) {
                if (t0 > ray_t.min) ray_t.min = t0;
                if (t1 < ray_t.max) ray_t.max = t1;
            } else {
                if (t1 > ray_t.min) ray_t.min = t1;
                if (t0 < ray_t.max) ray_t.max = t0;
            }

            if (ray_t.max <= ray_t.min)
                return false;
        }
        return true;
    }

    int AABB::longestAxis() const
    {
        // Returns the index of the longest axis of the bounding box.
        if (x.size() > y.size())
            return x.size() > z.size() ? 0 : 2;
        else
            return y.size() > z.size() ? 1 : 2;
    }

    const AABB AABB::empty    = AABB(Interval::empty,    Interval::empty,    Interval::empty);
    const AABB AABB::universe = AABB(Interval::universe, Interval::universe, Interval::universe);

    void AABB::padToMinimum()
    {
        // Adjust the AABB so that no side is narrower than some delta, padding if necessary.
        double delta = 0.0001;
        if (x.size() < delta) x = x.expand(delta);
        if (y.size() < delta) y = y.expand(delta);
        if (z.size() < delta) z = z.expand(delta);
    }
    AABB operator+(const AABB& bbox, const Lib::Vector3& offset) {
    return AABB(bbox.x + offset.x, bbox.y + offset.y, bbox.z + offset.z);
    }

    AABB operator+(const Lib::Vector3& offset, const AABB& bbox) {
        return bbox + offset;
    }

}

