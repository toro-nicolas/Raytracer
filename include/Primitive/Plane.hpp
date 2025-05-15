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
#include "Vector3.hpp"

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
            Lib::Vector3 &getFirstSide(void);
            Lib::Vector3 &getSecondSide(void);


            /* Display function */

            /**
             * @brief Display the primitive
             */
            void display(void) final;



            /* Intersection function */

            virtual void setBoundingBox();
            bool hit(const Ray &r, Interval ray_t, Intersection &rec) const override;
            virtual bool isInterior(double a, double b, Intersection& rec) const;




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