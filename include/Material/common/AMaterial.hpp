/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The AMaterial class declaration
*/
/**
 * @file AMaterial.hpp
 * @brief The AMaterial class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef AMATERIAL_HPP_
    #define AMATERIAL_HPP_

    #include "IMaterial.hpp"

namespace Raytracer {
    /**
     * @class AMaterial
     * @brief Abstract base class for transformations in the raytracer
     */
    class AMaterial : public IMaterial {
        public:
            /* Display function */

            /**
             * @brief Display the material
             */
            void display(void) override;




            /* Rendering function */

            /**
             * @brief Scatter the ray based on the material properties
             * @param r_in The incoming ray
             * @param rec The intersection record
             * @param attenuation The attenuation color
             * @param scattered The scattered ray
             * @return true if the ray is scattered, false otherwise
             */
            bool scatter(const Ray& r_in, const Intersection& rec, Lib::Vector3 &attenuation, Ray& scattered)
            const override;



        protected:
            std::unique_ptr<IMaterialBuilder> _builder; ///< Builder for the material
    };
}

#endif /* AMATERIAL_HPP_ */
