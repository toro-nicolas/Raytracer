/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The BVHNode class declaration
*/
/**
 * @file BVHNode.hpp
 * @brief The BVHNode class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef BVHNODE_HPP
    #define BVHNODE_HPP

    #include "Ray.hpp"
    #include "HittableList.hpp"

namespace Raytracer {
    class BvhNode : public Hittable {
        public:
            /* Constructors and destructors */

            /**
             * @brief Destructor for BvhNode
             */
            ~BvhNode() = default;

            /**
             * @brief Constructor from a hittable list
             * @param list The list of hittable objects to organize into a BVH
             */
            BvhNode(HittableList &list);

            /**
             * @brief Constructor from a range of objects
             * @param objects The vector of hittable objects
             * @param start The start index in the objects vector
             * @param end The end index (exclusive) in the objects vector
             */
            BvhNode(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end);



            /* Rendering function */

            /**
             * @brief Check if a ray hits this BVH node
             * @param r The ray to check
             * @param ray_t The interval of valid hit distances
             * @param rec The intersection record to fill if hit
             * @return True if the ray hits, false otherwise
             */
            bool hit(const Ray& r, Interval ray_t, Intersection& rec) const override;

            /**
             * @brief Get the bounding box of this node (const version)
             * @return The axis-aligned bounding box
             */
            const AABB &boundingBox() const override;

            /**
             * @brief Get the bounding box of this node
             * @return The axis-aligned bounding box
             */
            AABB &boundingBox() override;

            /**
             * @brief Compare two objects by their bounding boxes along an axis
             * @param a First object
             * @param b Second object
             * @param axis_index Axis index (0=x, 1=y, 2=z)
             * @return True if a's minimum along the axis is less than b's
             */
            static bool box_compare(const std::shared_ptr<Hittable> a,
                const std::shared_ptr<Hittable> b, int axis_index)
            {
                auto a_axis_interval = a->boundingBox().axis_interval(axis_index);
                auto b_axis_interval = b->boundingBox().axis_interval(axis_index);
                return a_axis_interval.min < b_axis_interval.min;
            }

            /**
             * @brief Compare two objects by their bounding boxes along the x-axis
             * @param a First object
             * @param b Second object
             * @return True if a's minimum along the x-axis is less than b's
             */
            static bool box_x_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
            {
                return box_compare(a, b, 0);
            }

            /**
             * @brief Compare two objects by their bounding boxes along the y-axis
             * @param a First object
             * @param b Second object
             * @return True if a's minimum along the y-axis is less than b's
             */
            static bool box_y_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
            {
                return box_compare(a, b, 1);
            }

            /**
             * @brief Compare two objects by their bounding boxes along the z-axis
             * @param a First object
             * @param b Second object
             * @return True if a's minimum along the z-axis is less than b's
             */
            static bool box_z_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
            {
                return box_compare(a, b, 2);
            }



        private:
            std::shared_ptr<Hittable> left; ///< Left child node
            std::shared_ptr<Hittable> right; ///< Right child node
            AABB bbox; ///< Bounding box containing this node and its children
        };
}

#endif // BVHNODE_HPP