/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Rotation class declaration
*/
/**
 * @file Rotation.hpp
 * @brief The Rotation class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef ROTATION_HPP
    #define ROTATION_HPP

    #include "ATransformation.hpp"
    #include "ATransformationBuilder.hpp"

namespace Raytracer {
    /**
     * @class Rotation
     * @brief Represents a rotation transformation in 3D space
     */
    class Rotation final : public ATransformation {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Rotation object
             */
            Rotation();

            /**
             * @brief Destroy the Rotation object
             */
            ~Rotation() final;

            /**
             * @brief Get the builder of the transformation
             * @return A reference to a unique pointer to the transformation builder
             */
            std::unique_ptr<ITransformationBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the transformation
             */
            void display(size_t level) final;



            /* Getters and setters */

            /**
             * @brief Get the rotation angle in degrees
             * @return The angle in degrees
             */
            double getAngle() const;

            /**
             * @brief Get the sine of the rotation angle
             * @return The sine value of the rotation angle
             */
            double getSinTheta() const;

            /**
             * @brief Get the cosine of the rotation angle
             * @return The cosine value of the rotation angle
             */
            double getCosTheta() const;

            /**
             * @brief Set the rotation angle in degrees
             * @param angle The angle in degrees
             */
            void setAngle(double angle);



            /* Rendering functions */

            /**
             * @brief Apply the rotation transformation to a ray
             * @param ray The ray to transform
             */
            void compute(Ray &ray) final;

            /**
             * @brief Reverse the rotation transformation on an intersection
             * @param rec The intersection record to transform
             */
            void decompute(Intersection &rec) final;

            /**
             * @brief Apply the rotation transformation to a bounding box
             * @param bbox The bounding box to transform
             */
            void newBoundingBox(AABB &bbox) final;



        private:
            double _angle; ///< Rotation angle in degrees
            double _sin_theta; ///< Sine of rotation angle in radians
            double _cos_theta; ///< Cosine of rotation angle in radians
    };



    /**
     * @class RotationBuilder
     * @brief Builder for the Rotation transformation
     */
    class RotationBuilder final : public ATransformationBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the RotationBuilder
             * @param plane Reference to a Rotation to be configured
             */
            RotationBuilder(Rotation &plane);

            /**
             * @brief Destructor of the RotationBuilder
             */
            ~RotationBuilder() final;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the transformation
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the transformation builder being configured
             */
            ITransformationBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Rotation &_rotation; ///< Reference to the Rotation being configured
    };



    /**
     * @brief Create a new Rotation object
     * @return std::shared_ptr<Rotation> A shared pointer to the created Rotation object
     */
    extern "C" std::shared_ptr<Rotation> createTransformation(void);
}

#endif // ROTATION_HPP