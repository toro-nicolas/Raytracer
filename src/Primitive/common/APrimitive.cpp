/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The APrimitive class implementation
*/
/**
 * @file APrimitive.cpp
 * @brief The APrimitive class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "APrimitive.hpp"

using namespace Lib;

namespace Raytracer {
    void APrimitive::display(void)
    {
        std::cout << "Primitive data:" << std::endl;
        std::cout << "        - Position: " << _pos << std::endl;
        std::cout << "        - Materials: (" << _materials.size() << ")" << std::endl;
        for (const auto &pair: _materials) {
            std::cout << "            - ";// << pair.first << ": ";
            pair.second->display();
        }
        if (_materials.empty())
            std::cout << std::endl;
        std::cout << "        - Transformations: (" << _transformations.size() << ")" << std::endl;
        for (const auto &pair: _transformations) {
            std::cout << "            - ";// << pair.first << ": ";
            pair.second->display();
        }
    }

    Lib::Vector3& APrimitive::getPos(void)
    {
        return _pos;
    }

    const Lib::Vector3& APrimitive::getPos(void) const
    {
        return _pos;
    }

    void APrimitive::setPos(const Lib::Vector3 &pos)
    {
        _pos = pos;
    }

    std::vector<std::pair<std::string, std::shared_ptr<IMaterial>>>& APrimitive::getMaterials(void)
    {
        return _materials;
    }

    const std::vector<std::pair<std::string, std::shared_ptr<IMaterial>>>& APrimitive::getMaterials(void) const
    {
        return _materials;
    }

    void APrimitive::setMaterial(const std::string &name, std::shared_ptr<IMaterial> &material)
    {
        if (name.empty())
            return;
        for (auto &pair: _materials) {
            if (pair.first == name) {
                pair.second = material;
                return;
            }
        }
        _materials.emplace_back(name, material);
    }

    std::vector<std::pair<std::string, std::shared_ptr<ITransformation>>>& APrimitive::getTransformations(void)
    {
        return _transformations;
    }

    const std::vector<std::pair<std::string, std::shared_ptr<ITransformation>>>& APrimitive::getTransformations(void) const
    {
        return _transformations;
    }

    void APrimitive::setTransformation(const std::string &name, std::shared_ptr<ITransformation> &transformation)
    {
        if (name.empty())
            return;
        for (auto &pair: _transformations) {
            if (pair.first == name) {
                pair.second = transformation;
                return;
            }
        }
        _transformations.emplace_back(name, transformation);
    }

    bool APrimitive::hit(UNUSED const Ray& ray, UNUSED Interval ray_t,
        UNUSED Intersection& rec) const
    {
        return false;
    }

    AABB &APrimitive::boundingBox()
    {
        return _bbox;
    }

    const AABB &APrimitive::boundingBox() const
    {
        return _bbox;
    }
}