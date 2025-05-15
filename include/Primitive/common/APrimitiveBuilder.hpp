/*
** EPITECH PROJECT, 2025
** Project
** File description:
** The APrimitiveBuilder.hpp
*/
/**
 * @file APrimitiveBuilder.hpp
 * @brief The APrimitiveBuilder.hpp
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef APRIMITIVEBUILDER_HPP_
    #define APRIMITIVEBUILDER_HPP_

    #include "IPrimitiveBuilder.hpp"

namespace Raytracer {
    /**
     * @class APrimitiveBuilder
     * @brief Abstract base class for building primitive shapes in the raytracer
     */
    class APrimitiveBuilder : public IPrimitiveBuilder
    {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the APrimitiveBuilder
             * @param primitive Reference to a IPrimitive to be configured
             */
            APrimitiveBuilder(IPrimitive &primitive);



            /* Setters of the global properties */

            /**
             * @brief Set the position of the primitive
             * @param pos The position vector to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &setPos(const Lib::Vector3 &pos) override;

            /**
             * @brief Set a material of the primitive
             * @param name The name of the material
             * @param material The material to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &setMaterial(const std::string &name, std::shared_ptr<IMaterial> &material) override;

            /**
             * @brief Set a transformation of the primitive
             * @param name The name of the transformation
             * @param transformation The transformation to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &setTransformation(const std::string &name, std::shared_ptr<ITransformation> &transformation) override;



        protected:
            IPrimitive &_primitive; ///< Reference to the primitive being configured
    };
}

#endif /* APRIMITIVEBUILDER_HPP_ */
