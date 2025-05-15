/*
** EPITECH PROJECT, 2025
** SolidColor.hpp
** File description:
** SolidColor declaration
*/


#ifndef SOLIDCOLOR_HPP
    #define SOLIDCOLOR_HPP

    #include "Texture.hpp"

namespace Raytracer {
    class SolidColor : public Texture {
        public:
            SolidColor(const Lib::Vector3& color);
            SolidColor(double red, double green, double blue);
            ~SolidColor() override = default;

            Lib::Vector3 value(double u, double v, const Lib::Vector3& p) const override;
            void display() const override;
        private:
            Lib::Vector3 _color;
    };

}

#endif // SOLIDCOLOR_HPP