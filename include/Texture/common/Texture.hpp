/*
** EPITECH PROJECT, 2025
** Texture.hpp
** File description:
** Texture declaration
*/


#ifndef TEXTURE_HPP
    #define TEXTURE_HPP

#include "Lib.hpp"


namespace Raytracer {

    class Texture {
        public:
            // Texture();
            virtual ~Texture() = default;

            virtual Lib::Vector3 value(double u, double v, const Lib::Vector3& p) const = 0;

            virtual void display() const = 0;
    };

}

#endif // TEXTURE_HPP