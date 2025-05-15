/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The AInterface class implementation
*/
/**
 * @file AInterface.cpp
 * @brief The AInterface class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "AInterface.hpp"

namespace Raytracer {
    void AInterface::setResolution(const std::array<int, 2> &resolution)
    {
        _resolution = resolution;
        _pixels.resize(_resolution[1]);
        for (int y = 0; y < _resolution[1]; ++y) {
            _pixels[y].resize(_resolution[0], Lib::Vector3(0, 0, 0));
        }
        resize();
    }

    void AInterface::setResolution(int width, int height)
    {
        _resolution[0] = width;
        _resolution[1] = height;
        _pixels.resize(_resolution[1]);
        for (int y = 0; y < _resolution[1]; ++y) {
            _pixels[y].resize(_resolution[0], Lib::Vector3(0, 0, 0));
        }
        resize();
    }

    void AInterface::writeColor(const int x, const int y, Lib::Vector3 pixel)
    {
        if (x < 0 || x >= _resolution[0] || y < 0 || y >= _resolution[1]) {
            return;
        }
        auto r = pixel.x;
        r = Lib::linearToGamma(r);
        auto g = pixel.y;
        g = Lib::linearToGamma(g);
        auto b = pixel.z;
        b = Lib::linearToGamma(b);

        static const Interval intensity(0.000, 0.999);
        int rbyte = int(256 * intensity.clamp(r));
        int gbyte = int(256 * intensity.clamp(g));
        int bbyte = int(256 * intensity.clamp(b));
        _pixels[y][x] = Lib::Vector3(rbyte, gbyte, bbyte);
    }
}