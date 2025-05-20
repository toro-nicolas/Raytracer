/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ATransformation class declaration
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
            void display(size_t level) override;



            /* Getters and setters */

            /**
             * @brief Get the offset vector of the transformation
             * @return A reference to the offset vector
             */
            Lib::Vector3 &getOffset(void) override;
            /**
             * @brief Get the offset vector of the transformation (const version)
             * @return A const reference to the offset vector
             */
            const Lib::Vector3 &getOffset(void) const override;

            /**
             * @brief Set the offset vector of the transformation
             * @param offset The new offset vector
             */
            void setOffset(const Lib::Vector3 &offset) override;



            /* Rendering function */

            /**
             * @brief compute the transformation on a ray
             * @param ray The ray to transform
             * @details This method applies the transformation to the ray's origin and direction.
             */
            void compute(Ray &ray) override;

            /**
             * @brief Reverse the transformation computation on an intersection
             * @param rec The intersection record to modify
             * @details This method applies the inverse transformation to the intersection record.
             */
            void decompute(Intersection &rec) override;

            /**
             * @brief Apply transformation to a bounding box
             * @param bbox The bounding box to transform
             */
            void newBoundingBox(AABB &bbox) override;



        protected:
            Lib::Vector3 _offset; ///< Offset vector for the transformation
            std::unique_ptr<ITransformationBuilder> _builder; ///< Pointer to the transformation builder
    };
}

#endif /* ATRANSFORMATION_HPP_ */
