/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Checker texture class declaration
*/
/**
 * @file Checker.hpp
 * @brief The Checker texture class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef Checker_HPP
    #define Checker_HPP

    #include "Texture.hpp"

namespace Raytracer {
    /**
     * @class Checker
     * @brief A checkered pattern texture alternating between two textures
     */
    class Checker : public Texture {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Checker texture with two textures
             * @param scale The size of each checker square
             * @param even The texture to use for even squares
             * @param odd The texture to use for odd squares
             */
            Checker(double scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);

            /**
             * @brief Construct a new Checker texture with two colors
             * @param scale The size of each checker square
             * @param c1 The color to use for even squares
             * @param c2 The color to use for odd squares
             */
            Checker(double scale, const Lib::Vector3& c1, const Lib::Vector3& c2);



            /* Getters and setters */

            /**
             * @brief Get the color value at a specific position
             * @param u The u texture coordinate
             * @param v The v texture coordinate
             * @param p The 3D point to get the color at
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
            double inv_scale; ///< Inverse of the checker scale for efficient computation
            std::shared_ptr<Texture> even; ///< Texture used for even squares
            std::shared_ptr<Texture> odd; ///< Texture used for odd squares
};

};

#endif // Checker_HPP