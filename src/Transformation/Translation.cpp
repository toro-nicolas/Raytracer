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

    void Translation::display(void)
    {
        std::cout << "Translation data: No data" << std::endl;
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
        return *this;
    }

    extern "C" std::shared_ptr<Translation> createTransformation(void)
    {
        return std::make_shared<Translation>();
    }
}