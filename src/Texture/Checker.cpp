/*
** EPITECH PROJECT, 2025
** Checker.cpp
** File description:
** Checker in ~/Documents/EPITECH/TEK2/OOP/BOOP400_raytracer/src/Texture/common
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

    void Checker::display() const
    {
        std::cout << "\t\tChecker: scale = " << 1.0 / inv_scale << std::endl;
        std::cout << "\t\tChecker: even color =" << std::endl;
        even->display();
        std::cout << "\t\tChecker: odd color =" << std::endl;
        odd->display();
    }
} // namespace Raytracer

