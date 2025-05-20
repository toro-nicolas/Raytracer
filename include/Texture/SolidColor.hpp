/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The SolidColor class declaration
*/
/**
 * @file SolidColor.hpp
 * @brief The SolidColor texture class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef SOLIDCOLOR_HPP
    #define SOLIDCOLOR_HPP

    #include "Texture.hpp"

namespace Raytracer {
    /**
     * @class SolidColor
     * @brief A texture that provides a single solid color
     */
    class SolidColor : public Texture {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new SolidColor texture from a vector color
             * @param color The color to use for this texture
             */
            SolidColor(const Lib::Vector3& color);

            /**
             * @brief Construct a new SolidColor texture from RGB components
             * @param red The red component [0.0-1.0]
             * @param green The green component [0.0-1.0]
             * @param blue The blue component [0.0-1.0]
             */
            SolidColor(double red, double green, double blue);

            /**
             * @brief Destroy the SolidColor texture
             */
            ~SolidColor() override = default;



            /* Getters and setters */

            /**
             * @brief Get the color value at a point
             * @param u The u texture coordinate (not used)
             * @param v The v texture coordinate (not used)
             * @param p The 3D point to get the color at (not used)
             * @return Lib::Vector3 The constant solid color
             */
            Lib::Vector3 value(double u, double v, const Lib::Vector3& p) const override;



            /* Display function */

            /**
             * @brief Display the texture information
             * @param level The indentation level for display formatting
             */
            void display(size_t level) const override;



        private:
            Lib::Vector3 _color; ///< The solid color for this texture
    };

}

#endif // SOLIDCOLOR_HPP