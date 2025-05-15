/*
** EPITECH PROJECT, 2025
** Checker.hpp
** File description:
** Checker declaration
*/


#ifndef Checker_HPP
    #define Checker_HPP
    #include "Texture.hpp"

namespace Raytracer {
    class Checker : public Texture {
    public:
        Checker(double scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);
        Checker(double scale, const Lib::Vector3& c1, const Lib::Vector3& c2);
        Lib::Vector3 value(double u, double v, const Lib::Vector3& p) const override;
        void display() const override;
  private:
    double inv_scale;
    std::shared_ptr<Texture> even;
    std::shared_ptr<Texture> odd;
};

};

#endif // Checker_HPP