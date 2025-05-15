/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Factory class implementation
*/
/**
 * @file Factory.cpp
 * @brief The Factory class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Factory.hpp"

namespace Raytracer {
    Factory::Factory()
    {
        // DEBUG << "Factory constructor";
    }

    Factory::Factory(const std::string &path)
    {
        // DEBUG << "Factory constructor with path: " << path;
        loadTypeFromPluginFolder(path);
    }

    Factory::~Factory()
    {
        DEBUG << "Factory destructor";
    }

    void Factory::loadTypeFromPluginFolder(const std::string &path)
    {
        std::filesystem::path plugin_path(path);
        std::string name;

        DEBUG << "Factory loadTypeFromPluginFolder: " << plugin_path;
        for (const auto &entry : std::filesystem::directory_iterator(plugin_path)) {
            if (entry.path().extension() == ".so") {
                if (entry.path().stem().string().rfind("raytracer_primitive_") == 0) {
                    DEBUG_CONCAT << "Found primitive plugin: " << entry.path();
                    name = entry.path().stem().string().substr(20);
                    _plugins[entry.path()] = std::make_unique<PluginLoader>(
                        entry.path());
                    _primitive_map[name] = [this, path = entry.path()]() -> std::shared_ptr<IPrimitive> {
                        return _plugins[path]->find<std::shared_ptr<IPrimitive>>("createPrimitive");
                    };
                } else if (entry.path().stem().string().rfind("raytracer_light_") == 0) {
                    DEBUG_CONCAT << "Found light plugin: " << entry.path();
                    name = entry.path().stem().string().substr(16);
                    _plugins[entry.path()] = std::make_unique<PluginLoader>(
                        entry.path());
                    _light_map[name] = [this, path = entry.path()]() -> std::shared_ptr<ILight> {
                        return _plugins[path]->find<std::shared_ptr<ILight>>("createLight");
                    };
                } else if (entry.path().stem().string().rfind("raytracer_material_") == 0) {
                    DEBUG_CONCAT << "Found material plugin: " << entry.path();
                    name = entry.path().stem().string().substr(19);
                    _plugins[entry.path()] = std::make_unique<PluginLoader>(
                        entry.path());
                    _material_map[name] = [this, path = entry.path()]() -> std::shared_ptr<IMaterial> {
                        return _plugins[path]->find<std::shared_ptr<IMaterial>>("createMaterial");
                    };
                } else if (entry.path().stem().string().rfind("raytracer_transformation_") == 0) {
                    DEBUG_CONCAT << "Found transformation plugin: " << entry.path();
                    name = entry.path().stem().string().substr(25);
                    _plugins[entry.path()] = std::make_unique<PluginLoader>(
                        entry.path());
                    _transformation_map[name] = [this, path = entry.path()]() -> std::shared_ptr<ITransformation> {
                        return _plugins[path]->find<std::shared_ptr<ITransformation>>("createTransformation");
                    };
                }
            }
        }
    }

    template<>
    const std::unordered_map<std::string, std::function<std::shared_ptr<IPrimitive>(void)>>&
    Factory::_getMap<IPrimitive>() const {
        return _primitive_map;
    }

    template<>
    std::unordered_map<std::string, std::function<std::shared_ptr<IPrimitive>(void)>>&
    Factory::_getMap<IPrimitive>() {
        return _primitive_map;
    }

    template<>
    const std::unordered_map<std::string, std::function<std::shared_ptr<ILight>(void)>>&
    Factory::_getMap<ILight>() const {
        return _light_map;
    }

    template<>
    std::unordered_map<std::string, std::function<std::shared_ptr<ILight>(void)>>&
    Factory::_getMap<ILight>() {
        return _light_map;
    }

    template<>
    const std::unordered_map<std::string, std::function<std::shared_ptr<IMaterial>(void)>>&
    Factory::_getMap<IMaterial>() const {
        return _material_map;
    }

    template<>
    std::unordered_map<std::string, std::function<std::shared_ptr<IMaterial>(void)>>&
    Factory::_getMap<IMaterial>() {
        return _material_map;
    }

    template<>
    const std::unordered_map<std::string, std::function<std::shared_ptr<ITransformation>(void)>>&
    Factory::_getMap<ITransformation>() const {
        return _transformation_map;
    }

    template<>
    std::unordered_map<std::string, std::function<std::shared_ptr<ITransformation>(void)>>&
    Factory::_getMap<ITransformation>() {
        return _transformation_map;
    }
}
