/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The ASceneLoader class declaration
*/
/**
 * @file ASceneLoader.hpp
 * @brief The ASceneLoader class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef ASCENELOADER_HPP_
    #define ASCENELOADER_HPP_

    #include "ISceneLoader.hpp"

namespace Raytracer {
    /**
     * @class ASceneLoader
     * @brief Abstract class for all scene loaders
     */
    class ASceneLoader : public ISceneLoader
    {
        public:
            /* Constructor and destructor */

            /**
             * @brief Constructor for ASceneLoader class
             */
            ASceneLoader();



            /* Getter functions */

            /**
             * @brief Get the camera of the scene
             * @return <b>std::shared_ptr<Camera> &</b>The camera of the scene
             */
            std::shared_ptr<Camera> &getCamera() override;

            /**
             * @brief Get the primitives of the scene
             * @return <b>std::vector<std::shared_ptr<IPrimitive>> &</b>The primitives of the scene
             */
            std::vector<std::shared_ptr<IPrimitive>> &getPrimitives() override;

            /**
             * @brief Get the lights of the scene
             * @return <b>std::vector<std::shared_ptr<ILight>> &</b>The lights of the scene
             */
            std::vector<std::shared_ptr<ILight>> &getLights() override;



            /* Display functions */

            /**
             * @brief Display the scene
             */
            void displayScene(void) override;



        protected:
            Factory _factory; ///< Factory for creating objects
            std::shared_ptr<Camera> _camera; ///< Camera of the scene
            std::vector<std::shared_ptr<IPrimitive>> _primitives; ///< Primitives of the scene
            std::vector<std::shared_ptr<ILight>> _lights; ///< Lights of the scene
    };
}

#endif /* ASCENELOADER_HPP_ */
