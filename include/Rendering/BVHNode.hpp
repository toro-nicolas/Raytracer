/*
** EPITECH PROJECT, 2025
** BVHNode.hpp
** File description:
** BVHNode declaration
*/


#ifndef BVHNODE_HPP
    #define BVHNODE_HPP
    #include "Ray.hpp"
    #include "HittableList.hpp"

namespace Raytracer {
    class BvhNode : public Hittable {
    public:
        ~BvhNode() = default;
        BvhNode(HittableList &list);
        BvhNode(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end);

        bool hit(const Ray& r, Interval ray_t, Intersection& rec) const override;
        const AABB &boundingBox() const override;
        AABB &boundingBox() override;

        static bool box_compare(const std::shared_ptr<Hittable> a,
            const std::shared_ptr<Hittable> b, int axis_index)
        {
            auto a_axis_interval = a->boundingBox().axis_interval(axis_index);
            auto b_axis_interval = b->boundingBox().axis_interval(axis_index);
            return a_axis_interval.min < b_axis_interval.min;
        }

        static bool box_x_compare (const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
        {
            return box_compare(a, b, 0);
        }

        static bool box_y_compare (const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
        {
            return box_compare(a, b, 1);
        }

        static bool box_z_compare (const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
        {
            return box_compare(a, b, 2);
        }

    private:
        std::shared_ptr<Hittable> left;
        std::shared_ptr<Hittable> right;
        AABB bbox;
    };
}

#endif // BVHNODE_HPP