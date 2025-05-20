/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The RtwImage class declaration
*/
/**
 * @file RtwImage.hpp
 * @brief The RtwImage class declaration for image loading and handling
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef RTWIMAGE_HPP
    #define RTWIMAGE_HPP

    #include "Lib.hpp"

namespace Raytracer {
    /**
     * @class RtwImage
     * @brief Class for loading and managing image data for texture mapping
     */
    class RtwImage {
        public:
            /* Constructors and destructors */

            /**
             * @brief Default constructor for RtwImage
             */
            explicit RtwImage() = default;

            /**
             * @brief Construct a new RtwImage from a file
             * @param filename Path to the image file to load
             */
            explicit RtwImage(const std::string& filename);

            /**
             * @brief Destroy the RtwImage and free memory
             */
            ~RtwImage();



            /* Getters and setters */

            /**
             * @brief Get the width of the image
             * @return int The width in pixels
             */
            int width() const;

            /**
             * @brief Get the height of the image
             * @return int The height in pixels
             */
            int height() const;

            /**
             * @brief Get the pixel data at a specific coordinate
             * @param x The x coordinate
             * @param y The y coordinate
             * @return const unsigned char* Pointer to the RGB data for the pixel
             */
            const unsigned char* pixelData(int x, int y) const;



        private:
            static constexpr int m_bytesPerPixel = 3; ///< Number of bytes per pixel (RGB)

            int m_width = 0; ///< Image width in pixels
            int m_height = 0; ///< Image height in pixels
            int m_bytesPerScanline = 0; ///< Bytes per row of pixels

            float* m_floatData = nullptr; ///< Float representation of image data
            std::unique_ptr<unsigned char[]> m_byteData; ///< Byte representation of image data



            /**
             * @brief Clamp an integer value between a low and high bound
             * @param x The value to clamp
             * @param low The lower bound
             * @param high The upper bound
             * @return int The clamped value
             */
            static int clamp(int x, int low, int high);

            /**
             * @brief Convert a float value [0.0-1.0] to a byte [0-255]
             * @param value The float value to convert
             * @return unsigned char The converted byte value
             */
            static unsigned char floatToByte(float value);

            /**
             * @brief Load image data from a file
             * @param filename Path to the image file to load
             * @return bool True if loading was successful, false otherwise
             */
            bool loadFromFile(const std::string& filename);

            /**
             * @brief Convert float image data to byte representation
             */
            void convertToBytes();
    };
}

#endif // RTWIMAGE_HPP
