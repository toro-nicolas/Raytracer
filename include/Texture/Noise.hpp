/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Noise class declaration
*/
/**
 * @file Noise.hpp
 * @brief The Noise class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef NOISE_HPP
    #define NOISE_HPP

    #include "Perlin.hpp"
    #include "Texture.hpp"

namespace Raytracer {
    /**
     * @class Noise
     * @brief A texture that generates procedural Perlin noise
     */
    class Noise : public Texture {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Noise texture
             * @param scale The scale factor for the noise pattern
             */
            Noise(double scale);

            /**
             * @brief Destroy the Noise texture
             */
            ~Noise() = default;



            /* Getters and setters */

            /**
             * @brief Get the color value at a specified point
             * @param u The u texture coordinate (not used for noise)
             * @param v The v texture coordinate (not used for noise)
             * @param p The 3D point where the noise is sampled
             * @return Lib::Vector3 The color at the specified point
             */
            Lib::Vector3 value(double u, double v, const Lib::Vector3& p) const override;



            /* Display function */

            /**
             * @brief Display the texture information
             * @param level The indentation level for display formatting
             */
            void display(size_t level) const override;



        private:
            Perlin _noise; ///< Perlin noise generator
            double _scale; ///< Scale factor for the noise pattern
    };

}

#endif // NOISE_HPP