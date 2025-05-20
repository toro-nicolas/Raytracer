/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Translation class implementation
*/
/**
 * @file Translation.cpp
 * @brief The Translation class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Translation.hpp"

namespace Raytracer {
    Translation::Translation()
    {
        // DEBUG << "Translation constructor";
    }

    Translation::~Translation()
    {
        // DEBUG << "Translation destructor";
    }

    std::unique_ptr<ITransformationBuilder> &Translation::getBuilder(void)
    {
        //DEBUG << "Translation getBuilder";
        if (!_builder)
            _builder = std::make_unique<TranslationBuilder>(*this);
        return _builder;
    }

    void Translation::display(size_t level)
    {
        std::string indent = std::string(level * 4, ' ');
        std::cout << "Translation data:" << std::endl;
        std::cout << indent << "- Offset: " << _offset << std::endl;
    }

    void Translation::compute(Ray &ray)
    {
        ray = Ray(ray.origin() - _offset, ray.direction(), ray.getTime());
    }

    void Translation::decompute(Intersection &rec)
    {
        rec.p = rec.p + _offset;
    }
    void Translation::newBoundingBox(AABB &bbox)
    {
        bbox = bbox + _offset;
    }

    TranslationBuilder::TranslationBuilder(Translation &translation) : ATransformationBuilder(translation), _translation(translation)
    {
        // DEBUG << "TranslationBuilder constructor";
    }

    TranslationBuilder::~TranslationBuilder()
    {
        // DEBUG << "TranslationBuilder destructor";
    }

    ITransformationBuilder &TranslationBuilder::set(const std::string &name, UNUSED const std::vector<std::string> &args)
    {
        DEBUG << "TranslationBuilder set " << name;
        if (name == "offset") {
            if (args.size() != 3)
                return *this;
            float x = std::stof(args[0]);
            float y = std::stof(args[1]);
            float z = std::stof(args[2]);
            _translation.setOffset(Lib::Vector3(x, y, z));
        } else {
            DEBUG << "TranslationBuilder set: unknown property " << name;
        }
        return *this;
    }

    extern "C" std::shared_ptr<Translation> createTransformation(void)
    {
        return std::make_shared<Translation>();
    }
}