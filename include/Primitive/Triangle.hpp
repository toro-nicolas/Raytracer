/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Triangle class declaration
*/
/**
 * @file Triangle.hpp
 * @brief The Triangle class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef TRIANGLE_HPP
    #define TRIANGLE_HPP

    #include "APrimitive.hpp"
    #include "APrimitiveBuilder.hpp"

namespace Raytracer {
    /**
     * @class Triangle
     * @brief Represents a triangle primitive in 3D space
     */
    class Triangle final : public APrimitive {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Triangle object
             */
            Triangle();

            /**
             * @brief Destroy the Triangle object
             */
            ~Triangle() final;

            /**
             * @brief Get the builder of the triangle
             * @return A reference to a unique pointer to the triangle builder
             */
            std::unique_ptr<IPrimitiveBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the primitive
             */
            void display(size_t level) final;



            /* Getters and setters */

            /**
             * @brief Get the first vertex of the triangle
             * @return Lib::Vector3& Reference to the vertex position
             */
            Lib::Vector3 &getVertex1(void);

            /**
             * @brief Get the first vertex of the triangle (const version)
             * @return const Lib::Vector3& Const reference to the vertex position
             */
            const Lib::Vector3 &getVertex1(void) const;

            /**
             * @brief Set the first vertex of the triangle
             * @param vertex The new vertex position
             */
            void setVertex1(const Lib::Vector3 &vertex);

            /**
             * @brief Get the second vertex of the triangle
             * @return Lib::Vector3& Reference to the vertex position
             */
            Lib::Vector3 &getVertex2(void);

            /**
             * @brief Get the second vertex of the triangle (const version)
             * @return const Lib::Vector3& Const reference to the vertex position
             */
            const Lib::Vector3 &getVertex2(void) const;

            /**
             * @brief Set the second vertex of the triangle
             * @param vertex The new vertex position
             */
            void setVertex2(const Lib::Vector3 &vertex);

            /**
             * @brief Get the third vertex of the triangle
             * @return Lib::Vector3& Reference to the vertex position
             */
            Lib::Vector3 &getVertex3(void);

            /**
             * @brief Get the third vertex of the triangle (const version)
             * @return const Lib::Vector3& Const reference to the vertex position
             */
            const Lib::Vector3 &getVertex3(void) const;

            /**
             * @brief Set the third vertex of the triangle
             * @param vertex The new vertex position
             */
            void setVertex3(const Lib::Vector3 &vertex);



            /* Rendering function */

            /**
             * @brief Check if the ray intersects with the triangle
             * @param ray The ray to check for intersection
             * @param rayT Valid interval for intersection
             * @param rec Intersection record to fill with details
             * @return true if the ray intersects with the triangle, false otherwise
             */
            bool hit(const Ray& ray, Interval rayT, Intersection& rec) const override;



            /* Initialization function */

            /**
             * @brief Initialize the triangle properties
             */
            void init(void) final;



        private:
            Lib::Vector3 _v1; ///< First vertex of the triangle
            Lib::Vector3 _v2; ///< Second vertex of the triangle
            Lib::Vector3 _v3; ///< Third vertex of the triangle
            Lib::Vector3 _normal; ///< Normal vector of the triangle



            /**
             * @brief Calculate the bounding box for the triangle
             */
            void setBoundingBox();

            /**
             * @brief Compute the barycentric coordinates for a point
             * @param p The point
             * @param u Output u coordinate
             * @param v Output v coordinate
             */
            void getTriangleUV(const Lib::Vector3& p, double& u, double& v) const;
    };



    /**
     * @class TriangleBuilder
     * @brief Builder for the Triangle primitive
     */
    class TriangleBuilder final : public APrimitiveBuilder {
        public:
            /**
             * @brief Constructor of the TriangleBuilder
             * @param triangle Reference to a Triangle to be configured
             */
            TriangleBuilder(Triangle &triangle);

            /**
             * @brief Destructor of the TriangleBuilder
             */
            ~TriangleBuilder() final;

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Triangle &_triangle; ///< Reference to the triangle being configured
    };



    /**
     * @brief Create a Triangle object
     * @return std::shared_ptr<Triangle> A shared pointer to the created Triangle object
     */
    extern "C" std::shared_ptr<Triangle> createPrimitive(void);
}

#endif // TRIANGLE_HPP