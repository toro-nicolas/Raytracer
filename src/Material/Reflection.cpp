/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Reflection class declaration
*/
/**
 * @file Reflection.cpp
 * @brief Reflection class declaration
 * @author Gianni TUERO
 */

#include "Reflection.hpp"

namespace Raytracer {

    Reflection::Reflection()
    {
        // DEBUG << "Reflection constructor";
    }

    Reflection::~Reflection()
    {
        // DEBUG << "Reflection destructor";
    }

    std::unique_ptr<IMaterialBuilder> &Reflection::getBuilder(void)
    {
        // DEBUG << "Reflection getBuilder";
        if (!_builder)
            _builder = std::make_unique<ReflectionBuilder>(*this);
        return _builder;
    }

    double &Reflection::getFuze(void)
    {
        return _fuze;
    }

    const double &Reflection::getFuze(void) const
    {
        return _fuze;
    }

    void Reflection::setFuze(double fuze)
    {
        _fuze = fuze;
    }

    void Reflection::display(void)
    {
        std::cout << "Reflection data:" << std::endl;
        std::cout << "                - Fuze: " << 100 - (_fuze * 100)  << "%" << std::endl;
    }

    bool Reflection::scatter(const Ray& r_in, const Intersection& rec, UNUSED Lib::Vector3 &attenuation, Ray& scattered) const
    {
        Vector3 reflected = reflect(r_in.direction(), rec.normal);
        reflected = unit_vector(reflected) + (_fuze * random_unit_vector());
        scattered = Ray(rec.p, reflected);
        return (dot(scattered.direction(), rec.normal) > 0);
    }

    IMaterialBuilder &ReflectionBuilder::set(const std::string &name, const std::vector<std::string> &args)
    {
        DEBUG << "ReflectionBuilder set " << name;
        if (name == "reflection") {
            if (args.size() != 1)
                return *this;
            double fuze = (100 - std::stod(args[0])) / 100.0;
            if (fuze < 0.0)
                fuze = 0.0;
            _reflection.setFuze(fuze);
        }
        else {
            WARNING << "ReflectionBuilder set: unknown property " << name;
        }
        return *this;
    }

    ReflectionBuilder::ReflectionBuilder(Reflection &reflection) : AMaterialBuilder(reflection), _reflection(reflection)
    {
        // DEBUG << "ReflectionBuilder constructor";
    }

    ReflectionBuilder::~ReflectionBuilder()
    {
        // DEBUG << "ReflectionBuilder destructor";
    }

    extern "C" std::shared_ptr<Reflection> createMaterial(void)
    {
        return std::make_shared<Reflection>();
    }
}