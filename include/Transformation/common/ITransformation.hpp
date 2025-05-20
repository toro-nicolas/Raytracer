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

    #include "Ray.hpp"

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



            /* Getters and setters */

            /**
             * @brief Get the offset vector of the transformation
             * @return A reference to the offset vector
             */
            virtual Lib::Vector3 &getOffset(void) = 0;

            /**
             * @brief Get the offset vector of the transformation (const version)
             * @return A const reference to the offset vector
             */
            virtual const Lib::Vector3 &getOffset(void) const = 0;

            /**
             * @brief Set the offset vector of the transformation
             * @param offset The new offset vector
             */
            virtual void setOffset(const Lib::Vector3 &offset) = 0;



            /* Display function */

            /**
             * @brief Display the primitive
             */
            virtual void display(size_t level) = 0;



            /* Rendering function */

            /**
             * @brief Compute the transformation on a ray
             * @param ray The ray to transform
             */
            virtual void compute(Ray &ray) = 0;

            /**
             * @brief Reverse the transformation computation on an intersection
             * @param intersection The intersection record to modify
             */
            virtual void decompute(Intersection &intersection) = 0;

            /**
             * @brief Apply transformation to a bounding box
             * @param bbox The bounding box to transform
             */
            virtual void newBoundingBox(AABB &bbox) = 0;
    };

}

#endif /* ITRANSFORMATION_HPP */