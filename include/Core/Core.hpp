/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Core class declaration
*/
/**
 * @file Core.hpp
 * @brief The Core class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include "Lib.hpp"
    #include "PluginLoader.hpp"
    #include "IInterface.hpp"
    #include "ISceneLoader.hpp"
    #include "Rendering.hpp"

    #define PLUGINS_PATH "plugins/"
    #define SCREENSHOTS_PATH "screenshots/"

namespace Raytracer {
    /**
     * @class Core
     * @brief The Core of the raytracer that links all the components together
     */
    class Core {
        public:
            /* Constructor and Destructor */

            /**
             * @brief Constructor of the Core class
             * @param ac The number of arguments
             * @param av The arguments
             */
            Core(int ac, char **av);

            /**
             * @brief Destructor of the Core class
             */
            ~Core();



            /* Core functions */

            /**
             * @brief Run the core
             */
            void run(void);



        protected:

        private:
            /* Configuration functions */

            /**
             * @brief Parse the arguments
             * @param ac The number of arguments
             * @param av The arguments
             * @throw Lib::Exceptions::Critical if the arguments are invalid
             * @throw Lib::Exceptions::Help if the help flag is set
             */
            void _parseArgs(int ac, char **av);

            #define CONFIG_FILE_PATH "config.txt"

            /**
             * @brief Load the configuration file
             * @details This function loads the configuration file and stores the values in a map
             * @throw Lib::Exceptions::Critical if the file cannot be opened or if the file isn't valid
             */
            void _loadConfigFile();

            /**
             * @brief Set the output file path
             */
            void _setOutputFilePath();



            std::string _configFilePath = "config.txt"; ///< The config file path (default: config.txt)
            std::unordered_map<std::string, std::string> _config; ///< The configuration map
            std::string _inputFilePath; ///< The input file path
            std::string _outputFilePath; ///< The output file path
            std::unordered_map<std::string, std::unique_ptr<PluginLoader>> _plugins; ///< The plugin map
            std::unique_ptr<ISceneLoader> _scene_loader; ///< The current scene loader
            std::shared_ptr<IInterface> _interface; ///< The current interface
            std::shared_ptr<Camera> _camera; ///< The current camera
            std::vector<std::shared_ptr<IPrimitive>> _primitives; ///< The primitives of the scene
            std::vector<std::shared_ptr<ILight>> _lights; ///< The lights of the scene
    };
}

#endif /* CORE_HPP_ */
