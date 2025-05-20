/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The HittableList class declaration
*/
/**
 * @file HittableList.hpp
 * @brief The HittableList class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */


#ifndef HITTABLELIST_HPP
    #define HITTABLELIST_HPP

    #include "Ray.hpp"

namespace Raytracer {
    /**
     * @class HittableList
     * @brief A collection of hittable objects that can be ray-traced as a group
     */
    class HittableList : public Hittable {
        public:
            /* Constructors and destructors */

            /**
             * @brief Default constructor for HittableList
             */
            HittableList();

            /**
             * @brief Destructor for HittableList
             */
            ~HittableList() = default;

            /**
             * @brief Constructor with a single object
             * @param object The hittable object to add to the list
             */
            HittableList(std::shared_ptr<Hittable> object);



            /* Rendering functions */

            /**
             * @brief Clear all objects from the list
             */
            void clear();

            /**
             * @brief Add an object to the list
             * @param object The hittable object to add
             */
            void add(std::shared_ptr<Hittable> object);

            /**
             * @brief Check if the ray intersects with the primitive
             * @param ray The ray to check
             * @param ray_t The interval of the ray
             * @param rec The intersection record
             * @return true if the ray intersects, false otherwise
             */
            bool hit(const Ray& ray, Interval ray_t, Intersection& rec) const override;

            /**
             * @brief Get the bounding box of the list (const version)
             * @return The axis-aligned bounding box containing all objects
             */
            const AABB& boundingBox() const override;

            /**
             * @brief Get the bounding box of the list
             * @return The axis-aligned bounding box containing all objects
             */
            AABB& boundingBox() override;

            /**
             * @brief Get the list of objects
             * @return Reference to the vector of hittable objects
             */
            std::vector<std::shared_ptr<Hittable>>& getObjects();



        private:
            std::vector<std::shared_ptr<Hittable>> _objects; ///< List of hittable objects
            AABB _worldBox; ///< Bounding box containing all objects in the list
    };
}

#endif // HITTABLELIST_HPP