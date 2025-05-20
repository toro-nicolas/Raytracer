/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ASceneLoader class implementation
*/
/**
 * @file ASceneLoader.cpp
 * @brief The ASceneLoader class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "ASceneLoader.hpp"

namespace Raytracer {
    ASceneLoader::ASceneLoader()
    {
        // DEBUG << "ASceneLoader constructor";
    }

    std::shared_ptr<Camera> &ASceneLoader::getCamera()
    {
        return _camera;
    }

    std::vector<std::shared_ptr<IPrimitive>> &ASceneLoader::getPrimitives()
    {
        return _primitives;
    }

    std::vector<std::shared_ptr<ILight>> &ASceneLoader::getLights()
    {
        return _lights;
    }

    void ASceneLoader::displayScene()
    {
        DEBUG << "Display scene";
        std::cout << BOLD << "[SCENE]:" << RESET << std::endl << std::endl;
        std::cout << *_camera << std::endl;
        std::cout << UNDERLINE << "PRIMITIVES:" << RESET << std::endl;

        /* with primitives maps
        for (const auto &pair: _primitives) {
            std::cout << "- " << pair.first << ": (" << pair.second.size() << ")" << std::endl;
            for (const auto &primitive: pair.second) {
                std::cout << "    - ";
                primitive->display();
            }
        }*/
        for (const auto &primitive: _primitives) {
            std::cout << "    - ";
            primitive->display(2);
        }

        std::cout << std::endl << UNDERLINE << "LIGHTS:" << RESET << std::endl;
        /*for (const auto &pair: _lights) {
            std::cout << "- " << pair.first << ": (" << pair.second.size() << ")" << std::endl;
            for (const auto &light: pair.second) {
                std::cout << "    - ";
                light->display();
            }
        }*/
        for (const auto &light: _lights) {
            std::cout << "    - ";
            light->display(2);
        }
    }
}