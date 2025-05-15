/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ITransformationBuilder class declaration
*/
/**
 * @file ITransformationBuilder.hpp
 * @brief The ITransformationBuilder class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef ITRANSFORMATIONBUILDER_HPP_
    #define ITRANSFORMATIONBUILDER_HPP_

    #include "ITransformation.hpp"

namespace Raytracer
{
    /**
     * @class ITransformationBuilder
     * @brief Interface for building primitive shapes in the raytracer
     */
    class ITransformationBuilder
    {
        public:
            /* Constructors and destructors */

            /**
             * @brief Destructor of the ITransformationBuilder
             */
            virtual ~ITransformationBuilder() = default;
            


            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the primitive builder being configured
             */
            virtual ITransformationBuilder &set(const std::string &name, const std::vector<std::string> &args) = 0;
    };
}

#endif /* ITRANSFORMATIONBUILDER_HPP_ */
