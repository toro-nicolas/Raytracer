/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Checker class implementation
*/
/**
 * @file Checker.cpp
 * @brief The Checker class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Checker.hpp"
#include "SolidColor.hpp"

namespace Raytracer
{
    Checker::Checker(double scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd)
    : inv_scale(1.0 / scale), even(even), odd(odd)
    {}

    Checker::Checker(double scale, const Lib::Vector3& c1, const Lib::Vector3& c2)
    : Checker(scale, std::make_shared<SolidColor>(c1), std::make_shared<SolidColor>(c2))
    {}

    Lib::Vector3 Checker::value(double u, double v, const Lib::Vector3& p) const
    {
        auto xInteger = int(std::floor(inv_scale * p.x));
        auto yInteger = int(std::floor(inv_scale * p.y));
        auto zInteger = int(std::floor(inv_scale * p.z));

        bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

        return isEven ? even->value(u, v, p) : odd->value(u, v, p);
    }

    void Checker::display(size_t level) const
    {
        std::string indent = std::string(level * 4, ' ');
        std::cout << "Checker texture:" << std::endl;
        std::cout << indent << "- Scale: " << 1.0 / inv_scale << std::endl;
        std::cout << indent << "- Even color:" << std::endl;
        std::cout << indent << "    - ";
        even->display(level + 2);
        std::cout << indent << "- Odd color:" << std::endl;
        std::cout << indent << "    - ";
        odd->display(level + 2);
    }
}
