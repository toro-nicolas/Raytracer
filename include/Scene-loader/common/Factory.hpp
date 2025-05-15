/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Factory class declaration
*/
/**
 * @file Factory.hpp
 * @brief The Factory class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef FACTORY_HPP_
    #define FACTORY_HPP_

    #include "Camera/Camera.hpp"
    #include "IPrimitiveBuilder.hpp"
    #include "Light/common/ILightBuilder.hpp"
    #include "Material/common/IMaterialBuilder.hpp"
    #include "Transformation/common/ITransformationBuilder.hpp"
    #include "PluginLoader.hpp"

namespace Raytracer {
    /**
     * @class Factory
     * @brief Class responsible for creating objects of different types
     * @details This class uses the Factory design pattern to create objects of different types
     * based on the registered types. It loads plugins from a specified folder and
     * registers the types found in the plugins.
     */
    class Factory
    {
        public:
            /* Constructor and Destructor */

            /**
             * @brief Constructor for Factory class
             */
            Factory();
            /*
             * @brief Constructor for Factory class
             * @param path The path of the plugin folder
             */
            Factory(const std::string &path);
            /**
             * @brief Destructor for Factory class
             */
            ~Factory();



            /* Factory functions */

            /**
             * @brief Load all types from the plugin folder
             * @param path The path of the plugin folder
             */
            void loadTypeFromPluginFolder(const std::string &path);

            /**
             * @brief Check if the type is registered
             * @tparam T The type of the object to check
             * @param name The name of the type to check
             * @return true if the type is registered, false otherwise
             */
            template<typename T>
            bool isTypeRegistered(const std::string& name) const {
                const auto& map = _getMap<T>();

                return map.find(name) != map.end();
            }

            /**
             * @brief Create a new object of type T
             * @throws Lib::Exceptions::Warning if the type is not registered
             * @tparam T The type of the object to create
             * @param name The name of the type to create
             * @return A shared pointer to the new object
             */
            template<typename T>
            std::shared_ptr<T> create(const std::string& name) const {
                const auto& map = _getMap<T>();
                auto it = map.find(name);

                if (it != map.end()) {
                    return (it->second)();
                }
                throw Lib::Exceptions::Warning("Type not registered: " + name);
            }



        protected:

        private:
            /* Getter for the map of all types */

            /**
             * @brief Get the map of the requested type
             * @tparam T The type of the object to create
             * @return A reference to the map of the requested type
             */
            template<typename T>
            const std::unordered_map<std::string, std::function<std::shared_ptr<T>(void)>>& _getMap() const;

            /**
             * @brief Get the map of the requested type
             * @tparam T The type of the object to create
             * @return A reference to the map of the requested type
             */
            template<typename T>
            std::unordered_map<std::string, std::function<std::shared_ptr<T>(void)>>& _getMap();

            std::unordered_map<std::string, std::unique_ptr<PluginLoader>> _plugins; /* Map of all plugins loaded */
            std::unordered_map<std::string, std::function<std::shared_ptr<IPrimitive>(void)>> _primitive_map; /* Map of all primitives */
            std::unordered_map<std::string, std::function<std::shared_ptr<ILight>(void)>> _light_map; /* Map of all lights */
            std::unordered_map<std::string, std::function<std::shared_ptr<IMaterial>(void)>> _material_map; /* Map of all materials */
            std::unordered_map<std::string, std::function<std::shared_ptr<ITransformation>(void)>> _transformation_map; /* Map of all transformations */
    };
}

#endif /* FACTORY_HPP_ */
