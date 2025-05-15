/*
** EPITECH PROJECT, 2025
** IPrimitive.hpp
** File description:
** The IPrimitive class declaration
*/

/**
 * @file IPrimitive.hpp
 * @brief The IPrimitive class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef IPRIMITIVE_HPP
    #define IPRIMITIVE_HPP

    #include "Lib.hpp"
    #include "IMaterial.hpp"
    #include "ITransformation.hpp"
    #include "Ray.hpp"

namespace Raytracer {
    class IPrimitiveBuilder; ///< Forward declaration of the IPrimitiveBuilder class



    /**
     * @class IPrimitive
     * @brief Interface for all primitive shapes in the raytracer
     */
    class IPrimitive : public Hittable {
        public:
            /**
             * @brief Destructor of the IPrimitive
             */
            virtual ~IPrimitive() = default;

            /**
             * @brief Get the builder of the primitive
             * @return A reference to a unique pointer to the primitive builder
             */
            virtual std::unique_ptr<IPrimitiveBuilder> &getBuilder(void) = 0;



            /* Display function */

            /**
             * @brief Display the primitive
             */
            virtual void display(void) = 0;



            /* Position functions */

            /**
             * @brief Get the position of the primitive
             * @return Reference to the position vector
             */
            virtual Lib::Vector3 &getPos(void) = 0;

            /**
             * @brief Get the position of the primitive (const version)
             * @return Const reference to the position vector
             */
            virtual const Lib::Vector3 &getPos(void) const = 0;

            /**
             * @brief Set the position of the primitive
             * @param pos New position vector
             */
            virtual void setPos(const Lib::Vector3 &pos) = 0;



            /* Material functions */

            /**
             * @brief Get the materials of the primitive
             * @return Reference to the materials
             */
            virtual std::vector<std::pair<std::string, std::shared_ptr<IMaterial>>> &getMaterials(void) = 0;

            /**
             * @brief Get the material of the primitive (const version)
             * @return Const reference to the materials
             */
            virtual const std::vector<std::pair<std::string, std::shared_ptr<IMaterial>>> &getMaterials(void) const = 0;

            /**
             * @brief Set a material of the primitive
             * @param name The name of the material
             * @param material The material to set
             */
            virtual void setMaterial(const std::string &name, std::shared_ptr<IMaterial> &material) = 0;



            /* Transformation functions */

            /**
             * @brief Get the transformations of the primitive
             * @return Reference to the transformations
             */
            virtual std::vector<std::pair<std::string, std::shared_ptr<ITransformation>>> &getTransformations(void) = 0;

            /**
             * @brief Get the transformation of the primitive (const version)
             * @return Const reference to the transformations
             */
            virtual const std::vector<std::pair<std::string, std::shared_ptr<ITransformation>>> &getTransformations(void) const = 0;

            /**
             * @brief Set a transformation of the primitive
             * @param name The name of the transformation
             * @param transformation The transformation to set
             */
            virtual void setTransformation(const std::string &name, std::shared_ptr<ITransformation> &transformation) = 0;
    };

}

#endif // IPRIMITIVE_HPP