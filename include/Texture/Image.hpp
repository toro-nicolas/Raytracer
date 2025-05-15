/*
** EPITECH PROJECT, 2025
** Image.hpp
** File description:
** Image declaration
*/


#ifndef IMAGE_HPP
    #define IMAGE_HPP

#include "Lib.hpp"
#include "RtwImage.hpp"
#include "Texture.hpp"

namespace Raytracer {

    class Image : public Texture {
    public:
        Image(const std::string &filename);
        ~Image() = default;

        Lib::Vector3 value(double u, double v, const Lib::Vector3& p) const override;

        void display() const override;

    private:
        RtwImage _image;
    };

}

#endif // IMAGE_HPP