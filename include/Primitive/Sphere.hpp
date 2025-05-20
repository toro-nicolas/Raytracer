/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Sphere class declaration
*/
/**
 * @file Raytracer
 * @brief The Sphere class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef SPHERE_HPP
    #define SPHERE_HPP

    #include "APrimitive.hpp"
    #include "APrimitiveBuilder.hpp"

namespace Raytracer {
    /**
     * @class Sphere
     * @brief Represents a sphere primitive in 3D space
     */
    class Sphere final : public APrimitive {
        public:
            /**
             * @brief Construct a new Sphere object
             */
            Sphere();

            /**
             * @brief Destroy the Sphere object
             */
            ~Sphere() final;

            /**
             * @brief Get the builder of the sphere
             * @return A reference to a unique pointer to the sphere builder
             */
            std::unique_ptr<IPrimitiveBuilder> &getBuilder(void) final;


            /* Display function */

            /**
             * @brief Display the primitive
             */
            void display(size_t level) final;


            /* Radius function */

            /**
             * @brief Get the radius of the sphere
             * @return float& Reference to the radius value
             */
            float &getRadius(void);

            /**
             * @brief Get the radius of the sphere (const version)
             * @return const float& Const reference to the radius value
             */
            const float &getRadius(void) const;

            /**
             * @brief Set the radius of the sphere
             * @param radius The new radius value
             */
            void setRadius(const float &radius);

            /**
             * @brief Set the center of the sphere
             * @param center The new center ray
             */
            void setCenter(const Ray &center);

            /**
             * @brief Get the center of the sphere
             * @return const Ray& Const reference to the center ray
             */
            const Ray &getCenter(void) const;
            /**
             * @brief Get the center of the sphere
             * @return Ray& Reference to the center ray
             */
            Ray &getCenter(void);



            /* Rendering function */

            /**
             * @brief Check if the ray intersects with the sphere
             * @param ray The ray to check for intersection
             * @param t_min Minimum distance for intersection
             * @param t_max Maximum distance for intersection
             * @param rec Intersection record to fill with details
             * @return true if the ray intersects with the sphere, false otherwise
             */
            bool hit(const Ray& ray, Interval ray_t, Intersection& rec) const override;



            /* Initialization function */

            /**
             * @brief Initialize the sphere
             */
            void init(void) final;



            bool centerSet; ///< Flag to indicate if the center is set
        private:
            float _radius; ///< The radius of the sphere
            Ray _center; ///< The center of the sphere



            /**
             * @brief Get the UV coordinates of a point on the sphere
             * @param p The point on the sphere
             * @param u The u coordinate
             * @param v The v coordinate
             */
            void getSphereUV(const Lib::Vector3& p, double& u, double& v) const;
    };



    /**
     * @class SphereBuilder
     * @brief Builder for the Sphere primitive
     */
    class SphereBuilder final : public APrimitiveBuilder {
        public:
            /**
             * @brief Constructor of the SphereBuilder
             * @param sphere Reference to a Sphere to be configured
             */
            SphereBuilder(Sphere &sphere);

            /**
             * @brief Destructor of the SphereBuilder
             */
            ~SphereBuilder() final;

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Sphere &_sphere; ///< Reference to the sphere being configured
    };



    /**
     * @brief Create a Sphere object
     * @return std::shared_ptr<Sphere> A shared pointer to the created Sphere object
     */
    extern "C" std::shared_ptr<Sphere> createPrimitive(void);
}

#endif // SPHERE_HPP