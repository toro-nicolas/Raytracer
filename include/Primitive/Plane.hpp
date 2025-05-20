/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Plane class declaration
*/
/**
 * @file Plane.hpp
 * @brief The Plane class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef PLANE_HPP
    #define PLANE_HPP

    #include "APrimitive.hpp"
    #include "APrimitiveBuilder.hpp"

namespace Raytracer {
    /**
     * @class Plane
     * @brief Represents a plane primitive in 3D space
     */
    class Plane final : public APrimitive {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Plane object
             */
            Plane();

            /**
             * @brief Destroy the Plane object
             */
            ~Plane() final;

            /**
             * @brief Get the builder of the primitive
             * @return A reference to a unique pointer to the primitive builder
             */
            std::unique_ptr<IPrimitiveBuilder> &getBuilder(void) final;


            /* Getter functions */

            /**
             * @brief Get the first side of the plane
             * @return Reference to the first side vector
             */
            Lib::Vector3 &getFirstSide(void);

            /**
             * @brief Get the second side of the plane
             * @return Reference to the second side vector
             */
            Lib::Vector3 &getSecondSide(void);


            /* Display function */

            /**
             * @brief Display the primitive
             */
            void display(size_t level) final;



            /* Rendering function */

            /**
             * @brief Set the bounding box of the primitive
             */
            void setBoundingBox();

            /**
             * @brief Check if the ray intersects with the primitive
             * @param r The ray to check
             * @param ray_t The interval of the ray
             * @param rec The intersection record
             * @return true if the ray intersects, false otherwise
             */
            bool hit(const Ray &r, Interval ray_t, Intersection &rec) const override;

            /**
             * @brief Check if the intersection point is inside the plane
             * @param a The first side of the plane
             * @param b The second side of the plane
             * @param rec The intersection record
             * @return true if the point is inside, false otherwise
             */
            bool isInterior(double a, double b, Intersection& rec) const;



            /* Initialization function */

            /**
             * @brief Initialize the primitive
             * @details This function initializes the primitive and its children
             */
            void init(void) final;



        private:
            Lib::Vector3 _u, _v; ///< The u and v vectors of the plane (first and second side)
            Lib::Vector3 _w; ///< The w vector of the plane
            Lib::Vector3 _normal; ///< The normal vector of the plane
            double D; ///< The distance from the origin to the plane
    };



    /**
     * @class PlaneBuilder
     * @brief Builder for the Plane primitive
     */
    class PlaneBuilder final : public APrimitiveBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the PlaneBuilder
             * @param plane Reference to a Plane to be configured
             */
            PlaneBuilder(Plane &plane);

            /**
             * @brief Destructor of the PlaneBuilder
             */
            ~PlaneBuilder() final;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Plane &_plane; ///< Reference to the plane being configured
    };



    /**
     * @brief Create a new Plane object
     * @return std::shared_ptr<Plane> A shared pointer to the created Plane object
     */
    extern "C" std::shared_ptr<Plane> createPrimitive(void);
}

#endif // PLANE_HPP