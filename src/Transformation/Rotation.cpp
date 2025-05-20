/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Rotation class implementation
*/
/**
 * @file Rotation.cpp
 * @brief The Rotation class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Rotation.hpp"

namespace Raytracer {
    Rotation::Rotation() : _angle(0.0), _sin_theta(0.0), _cos_theta(1.0)
    {
        // Default constructor - no rotation
    }

    Rotation::~Rotation()
    {
        // Destructor
    }

    std::unique_ptr<ITransformationBuilder> &Rotation::getBuilder(void)
    {
        if (!_builder)
            _builder = std::make_unique<RotationBuilder>(*this);
        return _builder;
    }

    void Rotation::display(size_t level)
    {
        std::string indent(level * 4, ' ');
        std::cout << "Rotation data:" << std::endl;
        std::cout << indent << "- Angle: " << _angle << " degrees" << std::endl;
    }

    double Rotation::getAngle() const
    {
        return _angle;
    }

    double Rotation::getSinTheta() const
    {
        return _sin_theta;
    }

    double Rotation::getCosTheta() const
    {
        return _cos_theta;
    }

    void Rotation::setAngle(double angle)
    {
        _angle = angle;

        // Convert angle to radians and precompute sin/cos values
        double radians = angle * M_PI / 180.0;
        _sin_theta = std::sin(radians);
        _cos_theta = std::cos(radians);
    }

    void Rotation::compute(Ray &ray)
    {
        // transform the ray's origin and direction using the rotation matrix
        auto origin = Lib::Vector3(
            (_cos_theta * ray.origin().x) - (_sin_theta * ray.origin().z),
            ray.origin().y,
            (_sin_theta * ray.origin().x) + (_cos_theta * ray.origin().z)
        );

        auto direction = Lib::Vector3(
            (_cos_theta * ray.direction().x) - (_sin_theta * ray.direction().z),
            ray.direction().y,
            (_sin_theta * ray.direction().x) + (_cos_theta * ray.direction().z)
        );

        ray = Ray(origin, direction, ray.getTime());
    }

    void Rotation::decompute(Intersection &rec)
    {
        // transform the intersection point and normal back using the inverse rotation matrix
        rec.p = Lib::Vector3(
            (_cos_theta * rec.p.x) + (_sin_theta * rec.p.z),
            rec.p.y,
            (-_sin_theta * rec.p.x) + (_cos_theta * rec.p.z)
        );

        rec.normal = Lib::Vector3(
            (_cos_theta * rec.normal.x) + (_sin_theta * rec.normal.z),
            rec.normal.y,
            (-_sin_theta * rec.normal.x) + (_cos_theta * rec.normal.z)
        );
    }
    void Rotation::newBoundingBox(AABB &bbox)
    {
        // Compute the new bounding box based on the rotation
        // Create a new bounding box that encompasses the rotated box
        Lib::Vector3 min( std::numeric_limits<float>::infinity(),  std::numeric_limits<float>::infinity(),  std::numeric_limits<float>::infinity());
        Lib::Vector3 max(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    auto x = i * bbox.x.max + (1-i) * bbox.x.min;
                    auto y = j * bbox.y.max + (1-j) * bbox.y.min;
                    auto z = k * bbox.z.max + (1-k) * bbox.z.min;

                    auto newx =  _cos_theta * x + _sin_theta * z;
                    auto newz = -_sin_theta * x + _cos_theta * z;

                    Lib::Vector3 tester(newx, y, newz);

                    min.x = std::fmin(min.x, tester.x);
                    min.y = std::fmin(min.y, tester.y);
                    min.z = std::fmin(min.z, tester.z);
                    max.x = std::fmax(max.x, tester.x);
                    max.y = std::fmax(max.y, tester.y);
                    max.z = std::fmax(max.z, tester.z);
                }
            }
        }
        bbox = AABB(min, max);
    }

    RotationBuilder::RotationBuilder(Rotation &rotation) : ATransformationBuilder(rotation), _rotation(rotation)
    {
        // DEBUG << "RotationBuilder constructor";
    }

    RotationBuilder::~RotationBuilder()
    {
        // DEBUG << "RotationBuilder destructor";
    }

    ITransformationBuilder &RotationBuilder::set(const std::string &name, UNUSED const std::vector<std::string> &args)
    {
        DEBUG << "RotationBuilder set " << name;
        if (name == "angleY") {
            if (args.size() != 1)
                return *this;
            float angle = std::stof(args[0]);
            _rotation.setAngle(angle);
        }
        else {
            DEBUG << "RotationBuilder set: unknown property " << name;
        }
        return *this;
    }


    // Create a factory function for plugins
    extern "C" std::shared_ptr<Rotation> createTransformation(void)
    {
        return std::make_shared<Rotation>();
    }
}