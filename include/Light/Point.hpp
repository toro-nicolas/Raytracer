/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Point class declaration
*/
/**
 * @file Point.hpp
 * @brief The Point class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef POINT_HPP
    #define POINT_HPP

    #include "ALight.hpp"
    #include "ALightBuilder.hpp"

namespace Raytracer {
    /**
     * @class Point
     * @brief Represents a point light in 3D space
     */
    class Point final : public ALight {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Point object
             */
            Point();

            /**
             * @brief Destroy the Point object
             */
            ~Point() final;

            /**
             * @brief Get the builder of the light
             * @return A reference to a unique pointer to the light builder
             */
            std::unique_ptr<ILightBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the light
             */
            void display(size_t level) final;

            /**
             * @brief Compute the light contribution at a given point
             * @param point The point in space
             * @param normal The normal vector at the point
             * @param view_dir The view direction vector
             * @return The light contribution as a Vector3
             */
            Lib::Vector3 compute(const Lib::Vector3& point, const Lib::Vector3& normal, const Lib::Vector3& view_dir) const override;

    };



    /**
     * @class PointBuilder
     * @brief Builder for the Point light
     */
    class PointBuilder final : public ALightBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the PointBuilder
             * @param point Reference to a Point to be configured
             */
            PointBuilder(Point &point);

            /**
             * @brief Destructor of the PointBuilder
             */
            ~PointBuilder() final;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the point
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the point builder being configured
             */
            ILightBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Point &_point; ///< Reference to the point being configured
    };



    /**
     * @brief Create a Point object
     * @return std::shared_ptr<Point> A shared pointer to the created Point object
     */
    extern "C" std::shared_ptr<Point> createLight(void);
}

#endif // POINT_HPP