/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Cone class declaration
*/
/**
 * @file Cone.hpp
 * @brief The Cone class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef CONE_HPP
    #define CONE_HPP

    #include "APrimitive.hpp"
    #include "APrimitiveBuilder.hpp"

namespace Raytracer {
    /**
     * @class Cone
     * @brief Represents a cone primitive in 3D space
     */
    class Cone final : public APrimitive {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Cone object
             */
            Cone();

            /**
             * @brief Destroy the Cone object
             */
            ~Cone() final;

            /**
             * @brief Get the builder of the cone
             * @return A reference to a unique pointer to the cone builder
             */
            std::unique_ptr<IPrimitiveBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the primitive
             */
            void display(size_t level) final;



            /* Getters and setters */

            /**
             * @brief Get the radius of the cone base
             * @return float& Reference to the radius value
             */
            float &getRadius(void);

            /**
             * @brief Get the radius of the cone base (const version)
             * @return const float& Const reference to the radius value
             */
            const float &getRadius(void) const;

            /**
             * @brief Set the radius of the cone base
             * @param radius The new radius value
             */
            void setRadius(const float &radius);

            /**
             * @brief Get the height of the cone
             * @return float& Reference to the height value
             */
            float &getHeight(void);

            /**
             * @brief Get the height of the cone (const version)
             * @return const float& Const reference to the height value
             */
            const float &getHeight(void) const;

            /**
             * @brief Set the height of the cone
             * @param height The new height value
             */
            void setHeight(const float &height);

            /**
             * @brief Set the axis of the cone
             * @param axis The direction vector of the cone's axis
             */
            void setAxis(const Lib::Vector3 &axis);

            /**
             * @brief Get the axis of the cone
             * @return Lib::Vector3& Reference to the axis vector
             */
            Lib::Vector3 &getAxis(void);

            /**
             * @brief Get the axis of the cone (const version)
             * @return const Lib::Vector3& Const reference to the axis vector
             */
            const Lib::Vector3 &getAxis(void) const;



            /* Rendering function */

            /**
             * @brief Check if the ray intersects with the cone
             * @param ray The ray to check for intersection
             * @param rayT Valid interval for intersection
             * @param rec Intersection record to fill with details
             * @return true if the ray intersects with the cone, false otherwise
             */
            bool hit(const Ray& ray, Interval rayT, Intersection& rec) const override;



            /* Initialization function */

            /**
             * @brief Initialize the cone
             */
            void init(void) final;



        private:
            float _radius; ///< The radius of the cone base
            float _height; ///< The height of the cone
            Lib::Vector3 _axis; ///< The axis direction of the cone



            /**
             * @brief Compute UV coordinates for a point on the cone
             * @param p The point on the cone surface
             * @param u Output u coordinate [0,1]
             * @param v Output v coordinate [0,1]
             */
            void getConeUV(const Lib::Vector3& p, double& u, double& v) const;

            /**
             * @brief Calculate the bounding box for the cone
             */
            void setBoundingBox();
    };



    /**
     * @class ConeBuilder
     * @brief Builder for the Cone primitive
     */
    class ConeBuilder final : public APrimitiveBuilder {
        public:
            /**
             * @brief Constructor of the ConeBuilder
             * @param cone Reference to a Cone to be configured
             */
            ConeBuilder(Cone &cone);

            /**
             * @brief Destructor of the ConeBuilder
             */
            ~ConeBuilder() final;

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Cone &_cone; ///< Reference to the cone being configured
    };



    /**
     * @brief Create a Cone object
     * @return std::shared_ptr<Cone> A shared pointer to the created Cone object
     */
    extern "C" std::shared_ptr<Cone> createPrimitive(void);
}

#endif // CONE_HPP