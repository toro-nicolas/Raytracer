/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Torus class declaration
*/
/**
 * @file Torus.hpp
 * @brief The Torus class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef TORUS_HPP
    #define TORUS_HPP

    #include "APrimitive.hpp"
    #include "APrimitiveBuilder.hpp"

namespace Raytracer {
    /**
     * @class Torus
     * @brief Represents a torus primitive in 3D space
     */
    class Torus final : public APrimitive {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Torus object
             */
            Torus();

            /**
             * @brief Destroy the Torus object
             */
            ~Torus() final;

            /**
             * @brief Get the builder of the torus
             * @return A reference to a unique pointer to the torus builder
             */
            std::unique_ptr<IPrimitiveBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the primitive
             */
            void display(size_t level) final;



            /* Getters and setters */

            /**
             * @brief Get the major radius of the torus (distance from center to ring center)
             * @return float& Reference to the major radius value
             */
            float &getMajorRadius(void);

            /**
             * @brief Get the major radius of the torus (const version)
             * @return const float& Const reference to the major radius value
             */
            const float &getMajorRadius(void) const;

            /**
             * @brief Set the major radius of the torus
             * @param radius The new major radius value
             */
            void setMajorRadius(const float &radius);

            /**
             * @brief Get the minor radius of the torus (thickness of the ring)
             * @return float& Reference to the minor radius value
             */
            float &getMinorRadius(void);

            /**
             * @brief Get the minor radius of the torus (const version)
             * @return const float& Const reference to the minor radius value
             */
            const float &getMinorRadius(void) const;

            /**
             * @brief Set the minor radius of the torus
             * @param radius The new minor radius value
             */
            void setMinorRadius(const float &radius);

            /**
             * @brief Set the axis of the torus
             * @param axis The direction vector of the torus's axis
             */
            void setAxis(const Lib::Vector3 &axis);

            /**
             * @brief Get the axis of the torus
             * @return Lib::Vector3& Reference to the axis vector
             */
            Lib::Vector3 &getAxis(void);

            /**
             * @brief Get the axis of the torus (const version)
             * @return const Lib::Vector3& Const reference to the axis vector
             */
            const Lib::Vector3 &getAxis(void) const;



            /* Rendering function */

            /**
             * @brief Check if the ray intersects with the torus
             * @param ray The ray to check for intersection
             * @param rayT Valid interval for intersection
             * @param rec Intersection record to fill with details
             * @return true if the ray intersects with the torus, false otherwise
             */
            bool hit(const Ray& ray, Interval rayT, Intersection& rec) const override;



            /* Initialization function */

            /**
             * @brief Initialize the torus properties
             */
            void init(void) final;



        private:
            float _majorRadius; ///< The major radius of the torus (distance from center to ring center)
            float _minorRadius; ///< The minor radius of the torus (thickness of the ring)
            Lib::Vector3 _axis; ///< The axis of the torus (perpendicular to the ring)



            /**
             * @brief Compute UV coordinates for a point on the torus
             * @param p The point on the torus surface
             * @param u Output u coordinate [0,1]
             * @param v Output v coordinate [0,1]
             */
            void getTorusUV(const Lib::Vector3& p, double& u, double& v) const;

            /**
             * @brief Calculate the bounding box for the torus
             */
            void setBoundingBox();
    };

    /**
     * @class TorusBuilder
     * @brief Builder for the Torus primitive
     */
    class TorusBuilder final : public APrimitiveBuilder {
        public:
            /**
             * @brief Constructor of the TorusBuilder
             * @param torus Reference to a Torus to be configured
             */
            TorusBuilder(Torus &torus);

            /**
             * @brief Destructor of the TorusBuilder
             */
            ~TorusBuilder() final;

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Torus &_torus; ///< Reference to the torus being configured
    };



    /**
     * @brief Create a Torus object
     * @return std::shared_ptr<Torus> A shared pointer to the created Torus object
     */
    extern "C" std::shared_ptr<Torus> createPrimitive(void);
}

#endif // TORUS_HPP