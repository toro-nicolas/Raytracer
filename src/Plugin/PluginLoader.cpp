/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The PluginLoader class implementation
*/
/**
 * @file PluginLoader.cpp
 * @brief The PluginLoader class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "PluginLoader.hpp"
#include "Exceptions.hpp"

namespace Raytracer {

    PluginLoader::PluginLoader()
    {
        // DEBUG << "PluginLoader constructor";
        _lib = nullptr;
    }

    PluginLoader::PluginLoader(const std::filesystem::path &fileToLoad)
    {
        // DEBUG << "PluginLoader constructor with " << fileToLoad;
        _lib = dlopen(fileToLoad.c_str(), RTLD_LAZY);
        if (!_lib) {
            throw Lib::Exceptions::Critical("Couldn't load the shared library: "
                 + std::string(dlerror()));
        }
    }

    void PluginLoader::newLib(const std::filesystem::path &fileToLoad)
    {
        //DEBUG << "PluginLoader newLib with " << fileToLoad;
        void *newLib = dlopen(fileToLoad.c_str(), RTLD_LAZY);
        if (!newLib) {
            throw Lib::Exceptions::Critical("Couldn't load the shared library: "
                + std::string(dlerror()));
        }
        if (_lib)
            dlclose(_lib);
        _lib = newLib;
    }

    PluginLoader::~PluginLoader()
    {
        // DEBUG << "PluginLoader destructor";
        if (_lib)
            dlclose(_lib);
    }
}