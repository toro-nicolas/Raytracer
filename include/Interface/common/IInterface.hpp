/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The IInterface class declaration
*/
/**
 * @file IInterface.hpp
 * @brief The IInterface class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef IINTERFACE_HPP_
    #define IINTERFACE_HPP_

    #include "Lib.hpp"
    #include "Vector3.hpp"
    #include <vector>

namespace Raytracer {

class IInterface {
public:
    virtual ~IInterface() = default;


    /* Configuration functions */

    /**
     * @brief Set the resolution of the output image
     * @param resolution The resolution of the image
     */
    virtual void setResolution(const std::array<int, 2> &resolution) = 0;

    /**
     * @brief Set the resolution of the output image
     * @param width The width of the image
     * @param height The height of the image
     */
    virtual void setResolution(const int width, const int height) = 0;

    /**
     * @brief Resize the resolution of the output image
     */
    virtual void resize(void) = 0;

    /**
     * @brief Create the output file
     * @param filename The name of the output file
     */
    virtual void setupOutputFile(const std::string &filename) = 0;


    /* Rendering functions */

    /**
     * @brief Write a pixel color to the output format
     * @param x The x coordinate of the pixel
     * @param y The y coordinate of the pixel
     * @param pixel The color of the pixel
     */
    virtual void writeColor(const int x, const int y, Lib::Vector3 pixel) = 0;

    /**
     * @brief Render the image on format of the interface
     */
    virtual void render() = 0;

};

}

#endif /* IINTERFACE_HPP_ */