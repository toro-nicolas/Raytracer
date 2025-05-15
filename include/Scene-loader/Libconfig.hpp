/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Libconfig class declaration
*/
/**
 * @file Libconfig.hpp
 * @brief The Libconfig class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef LIBCONFIG_HPP_
    #define LIBCONFIG_HPP_

    #include "ASceneLoader.hpp"
    #include <libconfig.h++>

namespace Raytracer {
    /**
     * @class Libconfig
     * @brief Class for loading scenes from libconfig files
     */
    class Libconfig final : public ASceneLoader
    {
        public:
            /* Constructor and destructor */

            /**
             * @brief Constructor for Libconfig class
             */
            Libconfig();

            /**
             * @brief Destructor for Libconfig class
             */
            ~Libconfig() final;



            /* Loader functions */

            /**
             * @brief Load a scene from a file
             * @param path The path of the scene
             * @param plugin_directory The path of the plugin directory
             * @throw Lib::Exceptions::Critical if the file cannot be opened or if the scene is invalid
             */
            void loadScene(const std::string &path, const std::string &plugin_directory) final;



        protected:

        private:
            /* Setup functions */

            /**
             * @brief Import a scene from the "import" parameter
             * @param path The path of the scene
             */
            void _importScene(const std::string &path);

            /**
             * @brief Get the arguments (the list of value) from the libconfig setting
             * @param setting The libconfig setting
             * @param output The output vector to fill with the args
             */
            static void _getArgsFromSetting(const libconfig::Setting &setting, std::vector<std::string>& output);

            /**
             * @brief Get the value from the libconfig setting
             * @tparam T The type of the value
             * @param setting The libconfig setting
             * @param name The name of the setting
             * @return <b>T</b> The value of the setting
             */
            template<typename T>
            T _getValue(const libconfig::Setting& setting, const std::string& name) {
                T output;
                if (setting.lookupValue(name, output)) {
                    return output;
                }
                return T();
            }

            /**
             * @brief Configure the object from the libconfig setting
             * @tparam T The type of the object
             * @param object The object to configure
             * @param setting The libconfig setting
             * @param setting_name The name of the setting
             */
            template<typename T>
            void _configureObject(std::shared_ptr<T> &object, const libconfig::Setting &setting, const std::string &setting_name) {
                //DEBUG << "Libconfig _configureObject " << typeid(T).name();
                /*if (setting.isGroup() || setting.isList() || setting.isArray()) {
                    for (const auto &parameter: setting) {
                        std::string parameter_name = parameter.getName();
                        std::vector<std::string> args;
                        _getArgsFromSetting(parameter, args);
                        object->getBuilder()->set(parameter_name, args);
                    }
                } else {
                    std::vector<std::string> args;
                    _getArgsFromSetting(setting, args);
                    object->getBuilder()->set(setting_name, args);
                }*/
                std::vector<std::string> args;
                _getArgsFromSetting(setting, args);
                object->getBuilder()->set(setting_name, args);
            }

            /**
             * @brief Set the camera from the libconfig setting
             * @param setting The libconfig setting for the camera
             */
            void _setCamera(const libconfig::Setting &setting);

            /**
             * @brief Set the primitive from the libconfig setting
             * @param setting The libconfig setting for the primitive
             */
            void _setPrimitive(const libconfig::Setting &setting);

            /**
             * @brief Set the light from the libconfig setting
             * @param setting The libconfig setting for the light
             */
            void _setLight(const libconfig::Setting &setting);


            std::vector<std::string> _scenesLoaded; ///< The list of scenes loaded
    };

    /**
     * @brief Function to create an instance of the Libconfig
     * @note The function get with dlsym in the PluginLoader class
     * @return <b>std::unique_ptr<ISceneLoader></b> A unique pointer to the Libconfig
     */
    extern "C" std::unique_ptr<ISceneLoader> createSceneLoader();
}

#endif /* LIBCONFIG_HPP_ */
