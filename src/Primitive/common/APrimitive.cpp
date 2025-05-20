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
    void APrimitive::display(size_t level)
    {
        std::string indent(level * 4, ' ');
        std::cout << "Primitive data:" << std::endl;
        std::cout << indent << "- Position: " << _pos << std::endl;
        std::cout << indent << "- Materials: (" << _materials.size() << ")" << std::endl;
        for (const auto &pair: _materials) {
            std::cout << indent <<"    - ";// << pair.first << ": ";
            pair.second->display(level + 2);
        }
        if (_materials.empty())
            std::cout << indent << "    No materials" << std::endl;
        std::cout << indent << "- Transformations: (" << _transformations.size() << ")" << std::endl;
        for (const auto &pair: _transformations) {
            std::cout << indent << "    - ";// << pair.first << ": ";
            pair.second->display(level + 2);
        }
        if (_transformations.empty())
            std::cout << indent << "    No transformations" << std::endl;
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

    std::vector<std::shared_ptr<IPrimitive>> APrimitive::getChildren(void)
    {
        return {};
    }

    void APrimitive::init(void)
    {
        // This function is intentionally left empty.
    }

}