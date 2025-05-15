/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Core class implementation
*/
/**
 * @file Core.cpp
 * @brief The Core class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Core.hpp"

namespace Raytracer {
    void Core::_parseArgs(int ac, char **av)
    {
        for (std::size_t index = 1; index < ac; index++) {
            if (std::string(av[index]) == "-h" || std::string(av[index]) == "--help") {
                throw Lib::Exceptions::Help("");
            }
            if (std::string(av[index]) == "-v" || std::string(av[index]) == "--version") {
                std::cout << "Raytracer version 1.0 | Version date: " __DATE__ " " __TIME__ << std::endl;
                continue;
            }
            if (std::string(av[index]) == "-o" || std::string(av[index]) == "--output") {
                if (index + 1 < ac) {
                    _outputFilePath = av[index + 1];
                    index++;
                } else {
                    throw Lib::Exceptions::Critical("Missing argument for --output");
                }
                continue;
            }
            if (std::string(av[index]) == "-c" || std::string(av[index]) == "--config") {
                if (index + 1 < ac) {
                    _configFilePath = av[index + 1];
                    index++;
                } else {
                    throw Lib::Exceptions::Critical("Missing argument for --config");
                }
                continue;
            }
            if (!_inputFilePath.empty())
                throw Lib::Exceptions::Critical("Multiple input files provided");
            _inputFilePath = av[index];
        }
    }


    void Core::_loadConfigFile()
    {
        std::ifstream file(_configFilePath);
        std::string content;
        std::size_t line_index = 1;

        if (!file.is_open()) {
            throw Lib::Exceptions::Critical("Couldn't open the configuration file");
        }
        while (std::getline(file, content)) {
            if (content.empty() || content[0] == '#')
                continue;
            std::vector<std::string> line = Lib::stringToVector(content, "=");
            if (line.size() != 2) {
                throw Lib::Exceptions::Critical("Invalid configuration file: line " +
                    std::to_string(line_index) + ": " + content);
            }
            _config[line[0]] = line[1];
            line_index++;
        }
    }

    void Core::_setOutputFilePath()
    {
        std::time_t now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm* tm = std::localtime(&now_time);
        std::string folder;
        std::stringstream ss;

        if (_config.find("screenshots_folder") != _config.end()) {
            folder = _config["screenshots_folder"];
        } else {
            folder = SCREENSHOTS_PATH;
        }
        ss << std::put_time(tm, "%Y-%m-%d_%H:%M:%S");
        _outputFilePath = std::filesystem::path(folder) / ss.str();
        std::filesystem::create_directories(folder);
    }

    Core::Core(int ac, char **av)
    {
        // DEBUG << "Core constructor";
        _parseArgs(ac, av);
        _loadConfigFile();

        /* Scene loader */
        if (_config.find("plugin_folder") == _config.end()) {
            WARNING << "plugin_folder not found in configuration file, using default path (" << PLUGINS_PATH << ")";
            _config["plugin_folder"] = PLUGINS_PATH;
        } else if (_config["plugin_folder"].back() != '/')
            _config["plugin_folder"] += '/';
        if (_config.find("scene_loader") == _config.end()) {
            throw Lib::Exceptions::Critical("Invalid configuration file: scene_loader not found");
        }
        _plugins["scene_loader"] = std::make_unique<PluginLoader>(_config["plugin_folder"] + _config["scene_loader"]);
        _scene_loader = _plugins["scene_loader"]->find<std::unique_ptr<ISceneLoader>>("createSceneLoader");
        if (_scene_loader == nullptr) {
            throw Lib::Exceptions::Critical("Invalid scene loader instance");
        }
        _scene_loader->loadScene(_inputFilePath, _config["plugin_folder"]);
        _scene_loader->displayScene();

        /* Prepare interface */
        if (_config.find("interface") == _config.end()) {
            throw Lib::Exceptions::Critical("Invalid configuration file: interface not found");
        }
        _plugins["interface"] = std::make_unique<PluginLoader>(PLUGINS_PATH + _config["interface"]);
        _interface = _plugins["interface"]->find<std::unique_ptr<IInterface>>("createInterface");
        if (_interface == nullptr) {
            throw Lib::Exceptions::Critical("Invalid interface instance");
        }
        if (_outputFilePath.empty())
            _setOutputFilePath();
        _interface->setupOutputFile(_outputFilePath);
        _camera = _scene_loader->getCamera();
    }

    Core::~Core()
    {
        // DEBUG << "Core destructor";
    }

    void Core::run(void)
    {
        DEBUG << "Core run";
        Rendering renderer(*_camera, _scene_loader->getPrimitives(), _scene_loader->getLights(), _interface);
        try {
            _interface->setResolution(_scene_loader->getCamera()->getResolution());
            renderer.render();
        } catch (const std::exception &e) {
            ERROR << "Error while loading interface: " << e.what();
            return;
        }
    }
}