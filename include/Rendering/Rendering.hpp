/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Rendering class declaration
*/
/**
 * @file Rendering.hpp
 * @brief The Rendering class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef RENDERING_HPP
    #define RENDERING_HPP

    #include "Camera.hpp"
    #include "IInterface.hpp"
    #include "ILight.hpp"
    #include "IPrimitive.hpp"
    #include "HittableList.hpp"

namespace Raytracer {

/**
 * @class Rendering
 * @brief Handles the ray tracing rendering process
 */
class Rendering {
    public:
        /* Constructors and destructors */

        /**
        * @brief Construct a new Rendering object
        * @param camera The camera used for rendering
        * @param primitives The list of primitives in the scene
        * @param lights The list of lights in the scene
        * @param interface The output interface for the rendered image
        */
        Rendering(const Camera& camera,
                std::vector<std::shared_ptr<IPrimitive>>& primitives,
                std::vector<std::shared_ptr<ILight>>& lights,
                std::shared_ptr<IInterface> &interface);

        /**
        * @brief Destroy the Rendering object
        */
        ~Rendering();



        /* Rendering functions */

        /**
        * @brief Render the scene to the provided interface
        */
        void render(void);

    private:
        /**
         * @brief Render all the lines within a specific interval for multi-threading
         * @param id The thread ID determining which lines to render
         */
        void thread_rendering(int id);

        /**
        * @brief Generate a ray for a specific pixel
        * @param x The x coordinate of the pixel
        * @param y The y coordinate of the pixel
        * @return The generated ray
        */
        Ray generateRay(int x, int y);

        /**
        * @brief Compute the color for a given ray
        * @param ray The ray to compute the color for
        * @param max_depth The maximum number of ray bounces to consider
        * @return The computed color
        */
        Lib::Vector3 rayColor(const Ray& ray, int max_depth);



        const Camera& _camera; ///< Reference to the camera used for rendering
        std::vector<std::shared_ptr<IPrimitive>>& _primitives; ///< Reference to scene primitives
        std::vector<std::shared_ptr<ILight>>& _lights; ///< Reference to scene lights
        std::shared_ptr<IInterface> _interface; ///< Output interface for the rendered image
        unsigned int _nb_thread; ///< Number of rendering threads
        std::atomic<unsigned int> _nb_running_thread; ///< Number of currently running threads
        std::vector<std::thread> _list_thread; ///< List of rendering threads
        std::atomic<int> _lines_rendered; ///< Number of lines rendered so far
        const std::chrono::milliseconds _framerate; ///< Target framerate for rendering
        std::shared_ptr<HittableList> _world; ///< Scene hittable list
    };
}

#endif // RENDERING_HPP