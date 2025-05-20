/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Image class declaration
*/
/**
 * @file Image.hpp
 * @brief The Image class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef IMAGE_HPP
    #define IMAGE_HPP

    #include "RtwImage.hpp"
    #include "Texture.hpp"

namespace Raytracer {
    /**
     * @class Image
     * @brief A texture that wraps an image file
     */
    class Image : public Texture {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Image texture from a file
             * @param filename Path to the image file to load
             */
            Image(const std::string &filename);

            /**
             * @brief Destroy the Image texture
             */
            ~Image() = default;



            /* Getters and setters */

            /**
             * @brief Get the color value at the specified texture coordinates
             * @param u The u texture coordinate [0.0-1.0]
             * @param v The v texture coordinate [0.0-1.0]
             * @param p The 3D point (not used for image textures)
             * @return Lib::Vector3 The color at the specified texture coordinates
             */
            Lib::Vector3 value(double u, double v, const Lib::Vector3& p) const override;



            /* Display function */

            /**
             * @brief Display the texture information
             * @param level The indentation level for display formatting
             */
            void display(size_t level) const override;



        private:
            RtwImage _image; ///< The loaded image data
    };
}

#endif // IMAGE_HPP