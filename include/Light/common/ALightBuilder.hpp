/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ALightBuilder class declaration
*/
/**
 * @file ALightBuilder.hpp
 * @brief The ALightBuilder class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef ALIGHTBUILDER_HPP_
    #define ALIGHTBUILDER_HPP_

    #include "ILightBuilder.hpp"

namespace Raytracer {
    /**
     * @class ALightBuilder
     * @brief Abstract base class for building light shapes in the raytracer
     */
    class ALightBuilder : public ILightBuilder
    {
        public:

            /* Constructors and destructors */

            /**
             * @brief Constructor of the ALightBuilder
             * @param light Reference to a ILight to be configured
             */
            ALightBuilder(ILight &light);



            /* Setters of the global properties */

            /**
             * @brief Set the position of the light
             * @param pos The position vector to set
             * @return Reference to the light builder being configured
             */
            ILightBuilder &setPos(const Lib::Vector3 &pos) override;

            /**
             * @brief Set the intensity of the light
             * @param intensity The intensity value to set
             * @return Reference to the light builder being configured
             */
            ILightBuilder &setIntensity(double intensity) override;



        protected:
            ILight &_light; ///< Reference to the light being configured
    };
}

#endif /* ALIGHTBUILDER_HPP_ */
