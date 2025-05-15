/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ATransformationBuilder class declaration
*/
/**
 * @file ATransformationBuilder.hpp
 * @brief The ATransformationBuilder class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef ATRANSFORMATIONBUILDER_HPP_
    #define ATRANSFORMATIONBUILDER_HPP_

    #include "ITransformationBuilder.hpp"

namespace Raytracer {
    /**
     * @class ATransformationBuilder
     * @brief Abstract base class for building transformation in the raytracer
     */
    class ATransformationBuilder : public ITransformationBuilder
    {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the ATransformationBuilder
             * @param transformation Reference to a ITransformation to be configured
             */
            ATransformationBuilder(ITransformation &transformation);



        protected:
            ITransformation &_transformation; ///< Reference to the transformation being configured
    };
}

#endif /* ATRANSFORMATIONBUILDER_HPP_ */
