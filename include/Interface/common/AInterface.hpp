/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The AInterface class declaration
*/
/**
 * @file AInterface.hpp
 * @brief The AInterface class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef AINTERFACE_HPP_
    #define AINTERFACE_HPP_

    #include "IInterface.hpp"

namespace Raytracer {
    /**
     * @class AInterface
     * @brief Abstract class for all interfaces in the raytracer
     */
    class AInterface : public IInterface {
        public:
            /* Configuration functions */

            /**
             * @brief Set the resolution of the output RtwImage
             * @param resolution The resolution of the RtwImage
             */
            void setResolution(const std::array<int, 2> &resolution) final;

            /**
             * @brief Set the resolution of the output RtwImage
             * @param width The width of the RtwImage
             * @param height The height of the RtwImage
             */
            void setResolution(int width, int height) final;

            /**
             * @brief Set a pixel color to the output format
             * @param x The x coordinate of the pixel
             * @param y The y coordinate of the pixel
             * @param pixel The color of the pixel
             */
            void writeColor(const int x, const int y, Lib::Vector3 pixel) final;

        protected:
            std::array<int, 2> _resolution; ///< Resolution of the output image
            std::vector<std::vector<Lib::Vector3>> _pixels; ///< 2D vector to store pixel colors
    };
}

#endif /* AINTERFACE_HPP_ */