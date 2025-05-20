/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ILight class declaration
*/
/**
 * @file ILight.hpp
 * @brief The ILight class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef ILIGHT_HPP
    #define ILIGHT_HPP

    #include "Lib.hpp"

namespace Raytracer {
    class ILightBuilder; ///< Forward declaration of ILightBuilder

    // TODO: Bah non la team, vous vous croyez où là ?!
    ///// Je peux foutre la ambiant light dans la cam stv
    enum class LightType {
        AMBIENT = 0,
        DIRECTIONAL = 1,
        POINT_LIGHT = 2
    };
    /**
     * @class ILight
     * @brief Interface for all light in the raytracer
     */
    class ILight {

        public:
            /**
             * @brief Destructor of the ILight
             */
            virtual ~ILight() = default;

            /**
             * @brief Get the builder of the light
             * @return A reference to a unique pointer to the light builder
             */
            virtual std::unique_ptr<ILightBuilder> &getBuilder(void) = 0;



            /* Display function */

            /**
             * @brief Display the light
             */
            virtual void display(size_t level) = 0;



            /* Position functions */

            /**
             * @brief Get the position of the light
             * @return Reference to the position vector
             */
            virtual Lib::Vector3 &getPos(void) = 0;

            /**
             * @brief Get the position of the light (const version)
             * @return Const reference to the position vector
             */
            virtual const Lib::Vector3 &getPos(void) const = 0;

            /**
             * @brief Set the position of the light
             * @param pos New position vector
             */
            virtual void setPos(const Lib::Vector3 &pos) = 0;



            /* Intensity functions */

            /**
             * @brief Get the intensity of the light
             * @return Reference to the intensity value
             */
            virtual double &getIntensity(void) = 0;

            /**
             * @brief Get the intensity of the light (const version)
             * @return Const reference to the intensity value
             */
            virtual const double &getIntensity(void) const = 0;

            /**
             * @brief Set the intensity of the light
             * @param intensity New intensity value
             */
            virtual void setIntensity(double intensity) = 0;

            /**
            * @brief Compute the light contribution at a specific point
            * @param point The point to compute the light for
            * @param normal The surface normal at the point
            * @param view_dir The viewing direction
            * @return The computed light contribution as a Vector3
            */
            virtual Lib::Vector3 compute(const Lib::Vector3& point, const Lib::Vector3& normal, const Lib::Vector3& view_dir) const = 0;
    };

}

#endif /* ILIGHT_HPP */