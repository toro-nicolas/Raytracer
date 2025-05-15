/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Cone class implementation
*/
/**
 * @file Cone.cpp
 * @brief The Cone class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Cone.hpp"

namespace Raytracer {
    Cone::Cone()
    {
        //DEBUG << "Cone constructor";
    }

    Cone::~Cone()
    {
        //DEBUG << "Cone destructor";
    }

    std::unique_ptr<IPrimitiveBuilder> &Cone::getBuilder(void)
    {
        //DEBUG << "Cone getBuilder";
        if (!_builder)
            _builder = std::make_unique<ConeBuilder>(*this);
        return _builder;
    }

    void Cone::display(void)
    {
        std::cout << "Cone data:" << std::endl;
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

    ConeBuilder::ConeBuilder(Cone &cone) : APrimitiveBuilder(cone), _cone(cone)
    {
        //DEBUG << "ConeBuilder constructor";
    }

    ConeBuilder::~ConeBuilder()
    {
        //DEBUG << "ConeBuilder destructor";
    }

    IPrimitiveBuilder &ConeBuilder::set(const std::string &name, UNUSED const std::vector<std::string> &args)
    {
        DEBUG << "ConeBuilder set " << name;
        return *this;
    }

    extern "C" std::shared_ptr<Cone> createPrimitive(void)
    {
        return std::make_shared<Cone>();
    }
}