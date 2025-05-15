/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Refraction class declaration
*/
/**
 * @file Refraction.cpp
 * @brief Refraction class declaration
 * @author Gianni TUERO
 */

#include "Refraction.hpp"

namespace Raytracer {

    Refraction::Refraction()
    {
        // DEBUG << "Refraction constructor";
    }

    Refraction::~Refraction()
    {
        // DEBUG << "Refraction destructor";
    }

    std::unique_ptr<IMaterialBuilder> &Refraction::getBuilder(void)
    {
        // DEBUG << "Refraction getBuilder";
        if (!_builder)
            _builder = std::make_unique<RefractionBuilder>(*this);
        return _builder;
    }

    double &Refraction::getFuze(void)
    {
        return _fuze;
    }

    const double &Refraction::getFuze(void) const
    {
        return _fuze;
    }

    void Refraction::setFuze(double fuze)
    {
        _fuze = fuze;
    }

    void Refraction::display(void)
    {
        std::cout << "Refraction data:" << std::endl;
        std::cout << "                - Fuze: " << (_fuze / 2) * 100  << "%" << std::endl;
    }

    double Refraction::reflectance(double cosine, double ref_idx)
    {
        // Use Schlick's approximation for reflectance
        double r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }

    bool Refraction::scatter(const Ray& r_in, const Intersection& rec, UNUSED Lib::Vector3 &attenuation, Ray& scattered) const
    {
        double ri = rec.front_face ? (1.0 / _fuze) : _fuze;
        Lib::Vector3 unit_direction = unit_vector(r_in.direction());

        double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);
        bool cannot_refract = ri * sin_theta > 1.0;
        Lib::Vector3 direction;
        if (cannot_refract || reflectance(cos_theta, ri) > Lib::random_double())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, ri);

        scattered = Ray(rec.p, direction);
        return true;
    }

    IMaterialBuilder &RefractionBuilder::set(const std::string &name, const std::vector<std::string> &args)
    {
        DEBUG << "RefractionBuilder set " << name;
        if (name == "refraction") {
            if (args.size() != 1)
                return *this;
            double refraction = std::stod(args[0]) / 100.0;
            if (refraction > 1.0)
                refraction = 1.0;
            _refraction.setFuze(refraction * 2.0);
        }
        else {
            WARNING << "RefractionBuilder set: unknown property " << name;
        }
        return *this;
    }

    RefractionBuilder::RefractionBuilder(Refraction &refraction) : AMaterialBuilder(refraction), _refraction(refraction)
    {
        // DEBUG << "RefractionBuilder constructor";
    }

    RefractionBuilder::~RefractionBuilder()
    {
        // DEBUG << "RefractionBuilder destructor";
    }

    extern "C" std::shared_ptr<Refraction> createMaterial(void)
    {
        return std::make_shared<Refraction>();
    }
}