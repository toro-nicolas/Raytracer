/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ISceneLoader class declaration
*/
/**
 * @file ISceneLoader.hpp
 * @brief The ISceneLoader class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef ISCENELOADER_HPP_
    #define ISCENELOADER_HPP_

    #include "Factory.hpp"

namespace Raytracer {
    /**
     * @class ISceneLoader
     * @brief Interface for all scene loaders
     */
    class ISceneLoader
    {
        public:
            /**
             * @brief Destructor of the ISceneLoader
             */
            virtual ~ISceneLoader() = default;



            /* Loader functions */

            /**
             * @brief Load a scene from a file
             * @param path The path of the scene
             * @param plugin_directory The path of the plugin directory
             */
            virtual void loadScene(const std::string &path, const std::string &plugin_directory) = 0;



            /* Getter functions */

            /**
             * @brief Get the cameras of the scene
             * @return <b>std::shared_ptr<Camera> &</b>The cameras of the scene
             */
            virtual std::shared_ptr<Camera> &getCamera() = 0;

            /**
             * @brief Get the primitives of the scene
             * @return <b>std::vector<std::shared_ptr<IPrimitive>> &</b>The primitives of the scene
             */
            virtual std::vector<std::shared_ptr<IPrimitive>> &getPrimitives() = 0;

            /**
             * @brief Get the lights of the scene
             * @return <b>std::vector<std::shared_ptr<ILight>> &</b>The lights of the scene
             */
            virtual std::vector<std::shared_ptr<ILight>> &getLights() = 0;



            /* Display functions */

            /**
             * @brief Display the scene
             */
            virtual void displayScene(void) = 0;
    };
}

#endif /* ISCENELOADER_HPP_ */
