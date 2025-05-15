/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Libconfig class implementation
*/
/**
 * @file Libconfig.cpp
 * @brief The Libconfig class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Libconfig.hpp"

namespace Raytracer {
    extern "C" std::unique_ptr<ISceneLoader> createSceneLoader()
    {
        return std::unique_ptr<Libconfig>(new Libconfig());
    }

    Libconfig::Libconfig() : ASceneLoader()
    {
        // DEBUG << "Libconfig constructor";
    }

    Libconfig::~Libconfig()
    {
        DEBUG << "Libconfig destructor";
    }

    void Libconfig::_importScene(const std::string &path)
    {
        libconfig::Config scene_cfg;
        DEBUG << "Libconfig _importScene " << path;
        try {
            scene_cfg.readFile(path.c_str());
        } catch (const libconfig::FileIOException &e) {
            WARNING << "Skipping imported scene (" << path << "): Error reading file: " + path;
            return;
        } catch (const libconfig::ParseException &e) {
            WARNING << "Skipping imported scene (" << path << "): Error parsing file: " + path +
                " at line " + std::to_string(e.getLine()) + ": " + e.getError();
            return;
        }
        _scenesLoaded.push_back(std::filesystem::canonical(path));
        try {
            const libconfig::Setting &root = scene_cfg.getRoot();

            _camera = std::make_shared<Camera>();
            for (const auto &setting : root) {
                std::string type = setting.getName();
                if (type == "import" && setting.getType() == libconfig::Setting::TypeList) {
                    for (int index = 0; index < setting.getLength(); ++index) {
                        std::string import_path = setting[index];
                        if (std::find(_scenesLoaded.begin(), _scenesLoaded.end(), std::filesystem::canonical(import_path)) != _scenesLoaded.end()) {
                            WARNING << "Skipping imported scene (" + std::filesystem::canonical(import_path).string() + "): already loaded";
                            continue;
                        }
                        _importScene(import_path);
                    }
                } else if (type == "primitives" && setting.getType() == libconfig::Setting::TypeGroup) {
                    _setPrimitive(setting);
                } else if (type == "lights" && setting.getType() == libconfig::Setting::TypeGroup) {
                    _setLight(setting);
                }
            }
        } catch (const std::exception &e) {
            WARNING << "Skipping imported scene (" << path << "): Error loading scene: " + std::string(e.what());
        }
    }

    void Libconfig::_getArgsFromSetting(const libconfig::Setting& setting, std::vector<std::string>& output) {
        switch (setting.getType()) {
            case libconfig::Setting::TypeGroup:
            case libconfig::Setting::TypeList:
            case libconfig::Setting::TypeArray:
                for (int i = 0; i < setting.getLength(); ++i) {
                    _getArgsFromSetting(setting[i], output);
                }
                break;

            case libconfig::Setting::TypeInt:
                output.push_back(std::to_string(static_cast<int>(setting)));
                break;

            case libconfig::Setting::TypeInt64:
                output.push_back(std::to_string(static_cast<long long>(setting)));
                break;

            case libconfig::Setting::TypeFloat:
                output.push_back(std::to_string(static_cast<double>(setting)));
                break;

            case libconfig::Setting::TypeString:
                output.push_back(static_cast<std::string>(setting));
                break;

            case libconfig::Setting::TypeBoolean:
                output.push_back(static_cast<bool>(setting) ? "true" : "false");
                break;

            default:
                break;
        }
    }

    template<>
    double Libconfig::_getValue(const libconfig::Setting& setting, const std::string& name) {
        double output = 0;
        if (setting.lookupValue(name, output)) {
            return output;
        }
        int int_output = 0;
        if (setting.lookupValue(name, int_output)) {
            return static_cast<double>(int_output);
        }
        return 0;
    }

    template<>
    int Libconfig::_getValue(const libconfig::Setting& setting, const std::string& name) {
        int output = 0;
        if (setting.lookupValue(name, output)) {
            return output;
        }
        double double_output = 0;
        if (setting.lookupValue(name, double_output)) {
            return static_cast<int>(double_output);
        }
        return 0;
    }

    void Libconfig::_setCamera(const libconfig::Setting &setting)
    {
        DEBUG << "Libconfig _setCamera";
        std::unordered_map<std::string, std::function<void(const libconfig::Setting &setting)>> groups_handlers = {
            {"resolution", [this](const libconfig::Setting &setting) {
                std::array<int, 2> resolution{
                    _getValue<int>(setting, "width"),
                    _getValue<int>(setting, "height")};
                _camera->setResolution(resolution);
            }},
            {"position",  [this](const libconfig::Setting &setting) {
                Lib::Vector3 position(
                    _getValue<double>(setting, "x"),
                    _getValue<double>(setting, "y"),
                    _getValue<double>(setting, "z"));
                _camera->setPosition(position);
            }},
            {"rotation",  [this](const libconfig::Setting &setting) {
                Lib::Vector3 rotation(
                    _getValue<double>(setting, "x"),
                    _getValue<double>(setting, "y"),
                    _getValue<double>(setting, "z"));
                _camera->setRotation(rotation);
            }},
            {"lookAt",  [this](const libconfig::Setting &setting) {
                Lib::Vector3 lookAt(
                    _getValue<double>(setting, "x"),
                    _getValue<double>(setting, "y"),
                    _getValue<double>(setting, "z"));
                _camera->setInitialLookAt(lookAt);
            }},
        };
        std::unordered_map<std::string, std::function<void(const libconfig::Setting &setting)>> attributs_handlers = {
            {"fieldOfView", [this](const libconfig::Setting &setting) {
                double fov = _getValue<double>(setting, "fieldOfView");
                _camera->setFov(fov);
            }},
            {"defocusAngle", [this](const libconfig::Setting &setting) {
                double defocus_angle = _getValue<double>(setting, "defocusAngle");
                _camera->setDefocusAngle(defocus_angle);
            }},
            {"focusDistance", [this](const libconfig::Setting &setting) {
                double focus_distance = _getValue<double>(setting, "focusDistance");
                _camera->setFocusDistance(focus_distance);
            }},
            {"maxDepth", [this](const libconfig::Setting &setting) {
                int max_depth = _getValue<int>(setting, "maxDepth");
                _camera->setMaxDepth(max_depth);
            }},
            {"samplesPerPixel", [this](const libconfig::Setting &setting) {
                int samples_per_pixel = _getValue<int>(setting, "samplesPerPixel");
                _camera->setSamplesPerPixels(samples_per_pixel);
                _camera->setPixelsSampleScale(1.0 / samples_per_pixel);
            }},
        };

        for (const auto &parameter : setting) {
            std::string type = parameter.getName();
            if (groups_handlers.find(type) != groups_handlers.end()) {
                groups_handlers[type](parameter);
            } else if (attributs_handlers.find(type) != attributs_handlers.end()) {
                attributs_handlers[type](setting);
            } else {
                WARNING << "Unknown camera parameter: " + type;
            }
        }
    }

    void Libconfig::_setPrimitive(const libconfig::Setting &setting)
    {
        DEBUG << "Libconfig _setPrimitive";

        for (const auto &primitive_type : setting) {
            std::string primitive_type_name = primitive_type.getName();
            if (!_factory.isTypeRegistered<IPrimitive>(primitive_type_name)) {
                std::string new_primitive_type_name = primitive_type_name;
                new_primitive_type_name.pop_back();
                if (_factory.isTypeRegistered<IPrimitive>(new_primitive_type_name)) {
                    primitive_type_name = new_primitive_type_name;
                } else {
                    WARNING << "Unknown primitive type: " + primitive_type_name;
                    continue;
                }
            }
            for (const auto &primitive : primitive_type) {
                try {
                    std::shared_ptr<IPrimitive> primitive_ptr = _factory.create<IPrimitive>(primitive_type_name);
                    for (const auto &parameter : primitive) {
                        std::string parameter_name = parameter.getName();
                        if (parameter_name == "position") {
                            Lib::Vector3 position(
                                _getValue<double>(parameter, "x"),
                                _getValue<double>(parameter, "y"),
                                _getValue<double>(parameter, "z"));
                            primitive_ptr->getBuilder()->setPos(Lib::Vector3(position.x, position.y, position.z));
                        } else if (_factory.isTypeRegistered<IMaterial>(parameter_name)) {
                            std::shared_ptr<IMaterial> material_ptr = _factory.create<IMaterial>(parameter_name);
                            if (parameter.getType() == libconfig::Setting::TypeGroup
                            || parameter.getType() == libconfig::Setting::TypeList
                            || parameter.getType() == libconfig::Setting::TypeArray) {
                                for (const auto &material_parameter: parameter)
                                    _configureObject(material_ptr, material_parameter, material_parameter.getName());
                            } else {
                                _configureObject(material_ptr, parameter, parameter_name);
                            }
                            primitive_ptr->getBuilder()->setMaterial(parameter_name, material_ptr);
                        } /* else if (_factory.isTypeRegistered<ITransformation>(parameter_name)) {
                            std::shared_ptr<ITransformation> transformation_ptr = _factory.create<ITransformation>(parameter_name);
                            if (parameter.getType() == libconfig::Setting::TypeGroup
                            || parameter.getType() == libconfig::Setting::TypeList
                            || parameter.getType() == libconfig::Setting::TypeArray) {
                                for (const auto &transformation_parameter: parameter)
                                    _configureObject(transformation_ptr, transformation_parameter, transformation_parameter.getName());
                            } else {
                                _configureObject(transformation_ptr, parameter, parameter_name);
                            }
                            primitive_ptr->getBuilder()->setTransformation(parameter_name, transformation_ptr); */
                        else {
                            DEBUG_CONCAT << "On est sur un autre paramètre: " << parameter_name;
                            _configureObject(primitive_ptr, parameter, parameter_name);
                        }
                    }
                    _primitives.push_back(primitive_ptr);
                } catch (const Lib::Exceptions::Warning &e) {
                    WARNING << e.what();
                    break;
                } catch (const std::exception &e) {
                    WARNING << "Error creating primitive: " << e.what();
                    continue;
                }
            }
        }
    }

    void Libconfig::_setLight(const libconfig::Setting &setting)
    {
        DEBUG << "Libconfig _setLight";

        for (const auto &light_type : setting) {
            std::string light_type_name = light_type.getName();
            if (light_type_name == "ambient") {
                double ambient = _getValue<double>(light_type, "ambient");
                try {
                    std::shared_ptr<ILight> light_ptr = _factory.create<ILight>("ambient");
                    light_ptr->getBuilder()->setIntensity(ambient);
                    _lights.push_back(light_ptr);
                } catch (const Lib::Exceptions::Warning &e) {
                    WARNING << "Can't create ambient light: " << e.what();
                }
                continue;
            }
            if (!_factory.isTypeRegistered<ILight>(light_type_name)) {
                std::string new_light_type_name = light_type_name;
                new_light_type_name.pop_back();
                if (_factory.isTypeRegistered<ILight>(new_light_type_name)) {
                    light_type_name = new_light_type_name;
                } else {
                    WARNING << "Unknown light type: " + light_type_name;
                    continue;
                }
            }
            for (const auto &light : light_type) {
                try {
                    std::shared_ptr<ILight> light_ptr = _factory.create<ILight>(light_type_name);
                    for (const auto &parameter : light) {
                        std::string parameter_name = parameter.getName();
                        if (parameter_name == "position") {
                            Lib::Vector3 position(
                                _getValue<double>(parameter, "x"),
                                _getValue<double>(parameter, "y"),
                                _getValue<double>(parameter, "z"));
                            light_ptr->getBuilder()->setPos(position);
                        } else if (parameter_name == "intensity") {
                            float intensity;
                            light.lookupValue("intensity", intensity);
                            light_ptr->getBuilder()->setIntensity(intensity);
                        } else {
                            _configureObject(light_ptr, parameter, parameter_name);
                        }
                    }
                    _lights.push_back(light_ptr);
                } catch (const Lib::Exceptions::Warning &e) {
                    WARNING << e.what();
                    break;
                } catch (const std::exception &e) {
                    WARNING << "Error creating light: " << e.what();
                    continue;
                }
            }
        }
    }

    void Libconfig::loadScene(const std::string &path, const std::string &plugin_directory)
    {
        libconfig::Config scene_cfg;

        DEBUG << "Libconfig loadScene";
        _factory.loadTypeFromPluginFolder(plugin_directory);
        try {
            scene_cfg.readFile(path.c_str());
        } catch (const libconfig::FileIOException &e) {
            throw Lib::Exceptions::Critical("Error reading file: " + path);
        } catch (const libconfig::ParseException &e) {
            throw Lib::Exceptions::Critical("Error parsing file: " + path +
                " at line " + std::to_string(e.getLine()) + ": " + e.getError());
        }
        _scenesLoaded.push_back(std::filesystem::canonical(path));
        try {
            const libconfig::Setting &root = scene_cfg.getRoot();

            _camera = std::make_shared<Camera>();
            for (const auto &setting : root) {
                std::string type = setting.getName();
                if (type == "import" && setting.getType() == libconfig::Setting::TypeList) {
                    for (int index = 0; index < setting.getLength(); ++index) {
                        std::string import_path = setting[index];
                        if (std::find(_scenesLoaded.begin(), _scenesLoaded.end(), std::filesystem::canonical(import_path)) != _scenesLoaded.end()) {
                            WARNING << "Skipping imported scene (" + std::filesystem::canonical(import_path).string() + "): already loaded";
                            continue;
                        }
                        _importScene(import_path);
                    }
                } else if (type == "camera" && setting.getType() == libconfig::Setting::TypeGroup) {
                    _setCamera(setting);
                    _camera->createViewport();
                } else if (type == "primitives" && setting.getType() == libconfig::Setting::TypeGroup) {
                    _setPrimitive(setting);
                } else if (type == "lights" && setting.getType() == libconfig::Setting::TypeGroup) {
                    _setLight(setting);
                }
            }
        } catch (const std::exception &e) {
            throw Lib::Exceptions::Critical("Error loading scene: " + std::string(e.what()));
        }
    }
}
