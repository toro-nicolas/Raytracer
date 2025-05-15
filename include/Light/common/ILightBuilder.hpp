/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ILightBuilder class declaration
*/
/**
 * @file ILightBuilder.hpp
 * @brief The ILightBuilder class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef ILIGHTBUILDER_HPP_
    #define ILIGHTBUILDER_HPP_

    #include "ILight.hpp"

namespace Raytracer
{
    /**
     * @class ILightBuilder
     * @brief Interface for building light in the raytracer
     */
    class ILightBuilder
    {
        public:
            /* Constructors and destructors */

            /**
             * @brief Destructor of the ILightBuilder
             */
            virtual ~ILightBuilder() = default;



            /* Setters of the global properties */

            /**
             * @brief Set the position of the light
             * @param pos The position vector to set
             * @return Reference to the primitive builder being configured
             */
            virtual ILightBuilder &setPos(const Lib::Vector3 &pos) = 0;

            /**
             * @brief Set the intensity of the light
             * @param intensity The intensity value to set
             * @return Reference to the primitive builder being configured
             */
            virtual ILightBuilder &setIntensity(double intensity) = 0;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the light
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the light builder being configured
             */
            virtual ILightBuilder &set(const std::string &name, const std::vector<std::string> &args) = 0;



        protected:

        private:
    };
}

#endif /* ILIGHTBUILDER_HPP_ */
