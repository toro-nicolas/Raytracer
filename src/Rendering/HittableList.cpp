/*
** EPITECH PROJECT, 2025
** HittableList.cpp
** File description:
** HittableList in ~/Documents/EPITECH/TEK2/OOP/BOOP400_raytracer/src/Rendering
*/

#include "HittableList.hpp"

namespace Raytracer {
    HittableList::HittableList()
    {

    }

    HittableList::HittableList(std::shared_ptr<Hittable> object)
    {
        add(object);
    }
    void HittableList::clear()
    {
        _objects.clear();
    }
    void HittableList::add(std::shared_ptr<Hittable> object)
    {
        _objects.push_back(object);
        _worldBox = AABB(_worldBox, object->boundingBox());
    }

    const AABB& HittableList::boundingBox() const
    {
        return _worldBox;
    }

    AABB& HittableList::boundingBox()
    {
        return _worldBox;
    }

    std::vector<std::shared_ptr<Hittable>>& HittableList::getObjects()
    {
        return _objects;
    }

    bool HittableList::hit(const Ray& ray, Interval ray_t, Intersection& rec) const
    {
        Intersection temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object : _objects) {
            if (object->hit(ray, Interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
}