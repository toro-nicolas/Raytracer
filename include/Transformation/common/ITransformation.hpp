/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ITransformation class declaration
*/
/**
 * @file ITransformation.hpp
 * @brief The ITransformation class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef ITRANSFORMATION_HPP
    #define ITRANSFORMATION_HPP

    #include "Lib.hpp"

namespace Raytracer {
    class ITransformationBuilder; ///< Forward declaration of the ITransformationBuilder class



    /**
     * @class ITransformation
     * @brief Interface for all primitive shapes in the raytracer
     */
    class ITransformation {
        public:
            /**
             * @brief Destructor of the ITransformation
             */
            virtual ~ITransformation() = default;

            /**
             * @brief Get the builder of the primitive
             * @return A reference to a unique pointer to the primitive builder
             */
            virtual std::unique_ptr<ITransformationBuilder> &getBuilder(void) = 0;



            /* Display function */

            /**
             * @brief Display the primitive
             */
            virtual void display(void) = 0;
    };

}

#endif /* ITRANSFORMATION_HPP */