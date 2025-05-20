/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The IMaterial class declaration
*/
/**
 * @file IMaterial.hpp
 * @brief The IMaterial class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH, Gianni TUERO
 */

#ifndef IMATERIAL_HPP_
    #define IMATERIAL_HPP_

    #include "Lib.hpp"
    #include "Ray.hpp"
    #include "Vector3.hpp"

namespace Raytracer {
    class IMaterialBuilder;

    class IMaterial {
        public:
            /* Constructors and destructors */

            /**
             * @brief Destructor of the IMaterial
             */
            virtual ~IMaterial() = default;

            /**
             * @brief Get the builder of the material
             * @return A reference to a unique pointer to the material builder
             */
            virtual std::unique_ptr<IMaterialBuilder> &getBuilder(void) = 0;



            /* Display function */

            /**
             * @brief Display the material
             */
            virtual void display(size_t level) = 0;



            /* Rendering function */

            /**
             * @brief Scatter the ray based on the material properties
             * @param r_in The incoming ray
             * @param rec The intersection record
             * @param attenuation The attenuation color
             * @param scattered The scattered ray
             * @return true if the ray is scattered, false otherwise
             */
            virtual bool scatter(const Ray& r_in, const Intersection& rec, Lib::Vector3 &attenuation, Ray& scattered) const = 0;

            /**
             * @brief Get the emitted light at a specific point
             * @param u The u texture coordinate
             * @param v The v texture coordinate
             * @param p The point in 3D space where to compute emission
             * @return Lib::Vector3 The emitted color/light at the point
             */
            virtual Lib::Vector3 emitted(double u, double v, const Lib::Vector3& p) const = 0;
    };
}

#endif /* IMATERIAL_HPP_ */
