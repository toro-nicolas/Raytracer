/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ALight class declaration
*/
/**
 * @file ALight.hpp
 * @brief The ALight class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef ALIGHT_HPP_
    #define ALIGHT_HPP_

    #include "ILight.hpp"

namespace Raytracer {
    /**
     * @class ALight
     * @brief Abstract class for all lights in the raytracer
     */
    class ALight : public ILight {
        public:
            /* Display function */

            /**
             * @brief Display the light
             */
            void display(size_t level) override;

            /* Setters and getters */

            /**
             * @brief Get the builder of the light
             * @return A unique pointer to the light builder
             */
            Lib::Vector3 &getPos(void) override;

            /**
             * @brief Get the position of the light (const version)
             * @return A const reference to the position of the light
             */
            const Lib::Vector3 &getPos(void) const override;

            /**
             * @brief Set the position of the light
             * @param pos The new position of the light
             */
            void setPos(const Lib::Vector3 &pos) override;

            /**
             * @brief Get the intensity of the light
             * @return The intensity of the light
             */
            double &getIntensity(void) override;

            /**
             * @brief Get the intensity of the light
             * @return The intensity of the light
             */
            const double &getIntensity(void) const override;

            /**
             * @brief Set the intensity of the light
             * @param intensity The new intensity of the light
             */
            void setIntensity(double intensity) override;

            /**
             * @brief Default implementation of compute for lights
             */
            virtual Lib::Vector3 compute(const Lib::Vector3& point, const Lib::Vector3& normal,
                                       const Lib::Vector3& view_dir) const override;



        protected:
            std::unique_ptr<ILightBuilder> _builder; ///< Pointer to the light builder
            Lib::Vector3 _pos; ///< Position of the light
            double _intensity; ///< Intensity of the light
    };
}

#endif /* ALIGHT_HPP_ */