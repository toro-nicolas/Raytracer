/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Cylinder class declaration
*/
/**
 * @file Cylinder.hpp
 * @brief The Cylinder class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef CYLINDER_HPP
    #define CYLINDER_HPP

    #include "APrimitive.hpp"
    #include "APrimitiveBuilder.hpp"

namespace Raytracer {
    /**
     * @class Cylinder
     * @brief Represents a cylinder primitive in 3D space
     */
    class Cylinder final : public APrimitive {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Cylinder object
             */
            Cylinder();

            /**
             * @brief Destroy the Cylinder object
             */
            ~Cylinder() final;

            /**
             * @brief Get the builder of the cylinder
             * @return A reference to a unique pointer to the cylinder builder
             */
            std::unique_ptr<IPrimitiveBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the primitive
             */
            void display(size_t level) final;



            /* Getters and setters */

            /**
             * @brief Get the radius of the cylinder
             * @return float& Reference to the radius value
             */
            float &getRadius(void);

            /**
             * @brief Get the radius of the cylinder (const version)
             * @return const float& Const reference to the radius value
             */
            const float &getRadius(void) const;

            /**
             * @brief Set the radius of the cylinder
             * @param radius The new radius value
             */
            void setRadius(const float &radius);

            /**
             * @brief Get the height of the cylinder
             * @return float& Reference to the height value
             */
            float &getHeight(void);

            /**
             * @brief Get the height of the cylinder (const version)
             * @return const float& Const reference to the height value
             */
            const float &getHeight(void) const;

            /**
             * @brief Set the height of the cylinder
             * @param height The new height value
             */
            void setHeight(const float &height);

            /**
             * @brief Set the axis of the cylinder
             * @param axis The direction vector of the cylinder's axis
             */
            void setAxis(const Lib::Vector3 &axis);

            /**
             * @brief Get the axis of the cylinder
             * @return Lib::Vector3& Reference to the axis vector
             */
            Lib::Vector3 &getAxis(void);

            /**
             * @brief Get the axis of the cylinder (const version)
             * @return const Lib::Vector3& Const reference to the axis vector
             */
            const Lib::Vector3 &getAxis(void) const;



            /* Rendering function */

            /**
             * @brief Check if the ray intersects with the cylinder
             * @param ray The ray to check for intersection
             * @param rayT Valid interval for intersection
             * @param rec Intersection record to fill with details
             * @return true if the ray intersects with the cylinder, false otherwise
             */
            bool hit(const Ray& ray, Interval rayT, Intersection& rec) const override;



            /* Initialization function */

            /**
             * @brief Initialize the cylinder
             */
            void init(void) final;

        private:
            float _radius; ///< The radius of the cylinder
            float _height; ///< The height of the cylinder
            Lib::Vector3 _axis; ///< The axis direction of the cylinder



            /**
             * @brief Compute UV coordinates for a point on the cylinder
             * @param p The point on the cylinder surface
             * @param u Output u coordinate [0,1]
             * @param v Output v coordinate [0,1]
             */
            void getCylinderUV(const Lib::Vector3& p, double& u, double& v) const;

            /**
             * @brief Calculate the bounding box for the cylinder
             */
            void setBoundingBox();
    };



    /**
     * @class CylinderBuilder
     * @brief Builder for the Cylinder primitive
     */
    class CylinderBuilder final : public APrimitiveBuilder {
        public:
            /**
             * @brief Constructor of the CylinderBuilder
             * @param cylinder Reference to a Cylinder to be configured
             */
            CylinderBuilder(Cylinder &cylinder);

            /**
             * @brief Destructor of the CylinderBuilder
             */
            ~CylinderBuilder() final;

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Cylinder &_cylinder; ///< Reference to the cylinder being configured
    };



    /**
     * @brief Create a Cylinder object
     * @return std::shared_ptr<Cylinder> A shared pointer to the created Cylinder object
     */
    extern "C" std::shared_ptr<Cylinder> createPrimitive(void);
}

#endif // CYLINDER_HPP