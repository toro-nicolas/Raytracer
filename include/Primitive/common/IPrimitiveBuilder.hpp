/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The IPrimitiveBuilder class declaration
*/
/**
 * @file IPrimitiveBuilder.hpp
 * @brief The IPrimitiveBuilder class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef IPRIMITIVEBUILDER_HPP_
    #define IPRIMITIVEBUILDER_HPP_

    #include "IPrimitive.hpp"

namespace Raytracer
{
    /**
     * @class IPrimitiveBuilder
     * @brief Interface for building primitive shapes in the raytracer
     */
    class IPrimitiveBuilder
    {
        public:
            /* Constructors and destructors */

            /**
             * @brief Destructor of the IPrimitiveBuilder
             */
            virtual ~IPrimitiveBuilder() = default;



            /* Setters of the global properties */

            /**
             * @brief Set the position of the primitive
             * @param pos The position vector to set
             * @return Reference to the primitive builder being configured
             */
            virtual IPrimitiveBuilder &setPos(const Lib::Vector3 &pos) = 0;

            /**
             * @brief Set a material of the primitive
             * @param name The name of the material
             * @param material The material to set
             * @return Reference to the primitive builder being configured
             */
            virtual IPrimitiveBuilder &setMaterial(const std::string &name, std::shared_ptr<IMaterial> &material) = 0;

            /**
             * @brief Set a transformation of the primitive
             * @param name The name of the transformation
             * @param transformation The transformation to set
             * @return Reference to the primitive builder being configured
             */
            virtual IPrimitiveBuilder &setTransformation(const std::string &name, std::shared_ptr<ITransformation> &transformation) = 0;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the primitive builder being configured
             */
            virtual IPrimitiveBuilder &set(const std::string &name, const std::vector<std::string> &args) = 0;
    };
}

#endif /* IPRIMITIVEBUILDER_HPP_ */
