/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The BVHNode class implementation
*/
/**
 * @file BVHNode.cpp
 * @brief The BVHNode class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "BVHNode.hpp"

namespace Raytracer {
    BvhNode::BvhNode(HittableList& list) : BvhNode(list.getObjects(), 0, list.getObjects().size())
    {
    }

    BvhNode::BvhNode(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end)
    {
        bbox = AABB::empty;
        for (size_t object_index=start; object_index < end; object_index++)
            bbox = AABB(bbox, objects[object_index]->boundingBox());
        int axis = bbox.longestAxis();

        auto comparator = (axis == 0) ? box_x_compare
                        : (axis == 1) ? box_y_compare
                                      : box_z_compare;

        size_t object_span = end - start;

        if (object_span == 1) {
            left = right = objects[start];
        } else if (object_span == 2) {
            left = objects[start];
            right = objects[start+1];
        } else {
            std::sort(std::begin(objects) + start, std::begin(objects) + end, comparator);

            auto mid = start + object_span/2;
            left = make_shared<BvhNode>(objects, start, mid);
            right = make_shared<BvhNode>(objects, mid, end);
        }

        // bbox = AABB(left->boundingBox(), right->boundingBox());
    }

    bool BvhNode::hit(const Ray& r, Interval ray_t, Intersection& rec) const
    {
        if (!bbox.hit(r, ray_t))
            return false;

        bool hit_left = left->hit(r, ray_t, rec);
        bool hit_right = right->hit(r, Interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

        return hit_left || hit_right;
    }

    const AABB &BvhNode::boundingBox() const
    {
        return bbox;
    }

    AABB &BvhNode::boundingBox()
    {
        return bbox;
    }
}