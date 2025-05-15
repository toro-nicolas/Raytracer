/*
** EPITECH PROJECT, 2025
** Noise.hpp
** File description:
** Noise declaration
*/


#ifndef NOISE_HPP
    #define NOISE_HPP


#include "Perlin.hpp"
#include "Texture.hpp"
#include "Vector3.hpp"
namespace Raytracer {

    class Noise : public Texture {
    public:
        Noise(double scale);
        ~Noise() = default;

        Lib::Vector3 value(double u, double v, const Lib::Vector3& p) const override;
        void display(void) const override;
    private:
        Perlin _noise;
        double _scale;
};

}

#endif // NOISE_HPP