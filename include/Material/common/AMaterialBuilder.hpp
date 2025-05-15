/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The AMaterialBuilder class declaration
*/
/**
 * @file AMaterialBuilder.hpp
 * @brief The AMaterialBuilder class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef AMATERIALBUILDER_HPP_
    #define AMATERIALBUILDER_HPP_

    #include "IMaterialBuilder.hpp"

namespace Raytracer {
    /**
     * @class AMaterialBuilder
     * @brief Abstract base class for building material shapes in the raytracer
     */
    class AMaterialBuilder : public IMaterialBuilder
    {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the AMaterialBuilder
             * @param material Reference to a IMaterial to be configured
             */
            AMaterialBuilder(IMaterial &material);



        protected:
            IMaterial &_material; ///< Reference to the material being configured
    };
}

#endif /* AMATERIALBUILDER_HPP_ */
