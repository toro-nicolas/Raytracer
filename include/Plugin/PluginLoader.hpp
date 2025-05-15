/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The PluginLoader class declaration
*/
/**
 * @file PluginLoader.hpp
 * @brief The PluginLoader class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef PLUGINLOADER_HPP
    #define PLUGINLOADER_HPP

    #include "Lib.hpp"

namespace Raytracer {
    /**
     * @class PluginLoader
     * @brief Class responsible for loading dynamic libraries and retrieving symbols
     */
    class PluginLoader {
        public:
            /* Constructors and Destructor */

            /**
             * @brief Constructor for PluginLoader
             */
            PluginLoader();

            /**
             * @brief Constructor for PluginLoader
             * @param libToLoad Path to the dynamic library to load
             * @throw Lib::Exceptions::Critical if the library cannot be loaded
             */
            PluginLoader(const std::filesystem::path &libToLoad);

            /**
             * @brief Destructor for PluginLoader
             * @details Closes the loaded library if one is open
             */
            ~PluginLoader();



            /* PluginLoader functions */

            /**
             * @brief Loads a new library
             * @param libToLoad Path to the dynamic library to load
             * @throw Lib::Exceptions::Critical if the library cannot be loaded
             */
            void newLib(const std::filesystem::path &libToLoad);

            /**
             * @brief Find and instantiate a symbol from the loaded library
             * @tparam T Type of object to instantiate
             * @param symbol Name of the symbol to find in the library
             * @return Pointer to the newly created object of type T, or nullptr if failed
             */
            template<typename T>
            T find(const std::string &symbol)
            {
                char *error = NULL;
                void *sym = NULL;
                T (*creator)() = NULL;

                if (!_lib)
                    return nullptr;
                dlerror();
                sym = dlsym(_lib, symbol.c_str());
                error = dlerror();
                if (error) {
                    ERROR << "Error while finding the library symbol: "
                    << std::string(error);
                    return nullptr;
                }
                creator = reinterpret_cast<T(*)()>(sym);
                return creator();
            }



        private:
            void *_lib; ///< Handle to the loaded dynamic library
    };
}

#endif // PLUGINLOADER_HPP
