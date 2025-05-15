/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ATransformation declaration
*/
/**
 * @file ATransformation.hpp
 * @brief The ATransformation class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef ATRANSFORMATION_HPP_
    #define ATRANSFORMATION_HPP_

    #include "ITransformation.hpp"

namespace Raytracer {
    /**
     * @class ATransformation
     * @brief Abstract base class for transformations in the raytracer
     */
    class ATransformation : public ITransformation {
        public:
            /* Display function */

            /**
             * @brief Display the transformation
             */
            void display(void) override;



        protected:
            std::unique_ptr<ITransformationBuilder> _builder; ///< Pointer to the transformation builder
    };
}

#endif /* ATRANSFORMATION_HPP_ */
