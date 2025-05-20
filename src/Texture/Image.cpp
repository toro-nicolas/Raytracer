/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Image class implementation
*/
/**
 * @file Image.cpp
 * @brief The Image class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Image.hpp"

namespace Raytracer {

    Image::Image(const std::string &filename) : _image(filename)
    {}

    Lib::Vector3 Image::value(double u, double v, UNUSED const Lib::Vector3& p) const {
// If we have no texture data, then return solid cyan as a debugging aid.
        if (_image.height() <= 0) return Lib::Vector3(0,1,1);

        // Clamp input texture coordinates to [0,1] x [1,0]
        u = Interval(0,1).clamp(u);
        v = 1.0 - Interval(0,1).clamp(v);  // Flip V to image coordinates

        auto i = int(u * _image.width());
        auto j = int(v * _image.height());
        auto pixel = _image.pixelData(i,j);

        auto color_scale = 1.0 / 255.0;
        return Lib::Vector3(color_scale*pixel[0], color_scale*pixel[1], color_scale*pixel[2]);
    }

    void Image::display(size_t level) const {
        std::string indent = std::string(level * 4, ' ');
        std::cout << "Image texture: " << std::endl;
        std::cout << indent << "- Resolution: " << _image.width() << "x" << _image.height() << std::endl;
    }
}
