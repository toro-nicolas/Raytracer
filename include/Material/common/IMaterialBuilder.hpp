/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The IMaterialBuilder class declaration
*/
/**
 * @file IMaterialBuilder.hpp
 * @brief The IMaterialBuilder class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef IMATERIALBUILDER_HPP_
    #define IMATERIALBUILDER_HPP_

    #include "IMaterial.hpp"

namespace Raytracer
{
    /**
     * @class IMaterialBuilder
     * @brief Interface for building primitive shapes in the raytracer
     */
    class IMaterialBuilder
    {
        public:
            /* Constructors and destructors */

            /**
             * @brief Destructor of the IMaterialBuilder
             */
            virtual ~IMaterialBuilder() = default;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the material
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the material builder being configured
             */
            virtual IMaterialBuilder &set(const std::string &name, const std::vector<std::string> &args) = 0;
    };
}

#endif /* IMATERIALBUILDER_HPP_ */
