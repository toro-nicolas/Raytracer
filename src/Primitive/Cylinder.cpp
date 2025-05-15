/*
** EPITECH PROJECT, 2025
** Cylinder.cpp
** File description:
** The Cylinder class implementation
*/
/**
 * @file Cylinder.cpp
 * @brief The Cylinder class implementation
 * @author Gianni TUERO
 */

#include "Cylinder.hpp"

namespace Raytracer {
    Cylinder::Cylinder()
    {
        //DEBUG << "Cylinder constructor";
    }

    Cylinder::~Cylinder()
    {
        //DEBUG << "Cylinder destructor";
    }

    std::unique_ptr<IPrimitiveBuilder> &Cylinder::getBuilder(void)
    {
        //DEBUG << "Cylinder getBuilder";
        if (!_builder)
            _builder = std::make_unique<CylinderBuilder>(*this);
        return _builder;
    }

    void Cylinder::display(void)
    {
        std::cout << "Cylinder data:" << std::endl;
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

    CylinderBuilder::CylinderBuilder(Cylinder &cylinder) : APrimitiveBuilder(cylinder), _cylinder(cylinder)
    {
        //DEBUG << "CylinderBuilder constructor";
    }

    CylinderBuilder::~CylinderBuilder()
    {
        //DEBUG << "CylinderBuilder destructor";
    }

    IPrimitiveBuilder &CylinderBuilder::set(const std::string &name, UNUSED const std::vector<std::string> &args)
    {
        DEBUG << "CylinderBuilder set " << name;
        return *this;
    }

    extern "C" std::shared_ptr<Cylinder> createPrimitive(void)
    {
        return std::make_shared<Cylinder>();
    }
}