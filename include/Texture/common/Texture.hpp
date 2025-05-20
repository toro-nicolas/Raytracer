/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Texture class declaration
*/
/**
 * @file Texture.hpp
 * @brief The Texture class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef TEXTURE_HPP
    #define TEXTURE_HPP

#include "Lib.hpp"


namespace Raytracer {
    /**
     * @class Texture
     * @brief Abstract base class for all texture types
     */
    class Texture {
        public:
            /* Constructors and destructors */

            /**
             * @brief Virtual destructor for the Texture class
             */
            virtual ~Texture() = default;



            /* Getters and setters */

            /**
             * @brief Get the color value at specified texture coordinates and position
             * @param u The U texture coordinate [0.0-1.0]
             * @param v The V texture coordinate [0.0-1.0]
             * @param p The 3D position where the texture is sampled
             * @return Lib::Vector3 The color at the specified coordinates
             */
            virtual Lib::Vector3 value(double u, double v, const Lib::Vector3& p) const = 0;



            /* Display function */

            /**
             * @brief Display information about the texture
             * @param level The indentation level for display formatting
             */
            virtual void display(size_t level) const = 0;
    };

}

#endif // TEXTURE_HPP