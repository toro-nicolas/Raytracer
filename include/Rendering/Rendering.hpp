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
//TODO: Refaire la doc de ce fichier quand il sera vraiment fini parce que la c'est le bordel

#ifndef RENDERING_HPP
    #define RENDERING_HPP

#include "Camera.hpp"
#include "HittableList.hpp"
#include "IInterface.hpp"
#include "ILight.hpp"
#include "IPrimitive.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"
#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>

namespace Raytracer {

/**
 * @class Rendering
 * @brief Handles the ray tracing rendering process
 */
class Rendering {
    public:
        /**
        * @brief Construct a new Rendering object
        * @param camera The camera used for rendering
        * @param primitives The list of primitives in the scene
        * @param lights The list of lights in the scene
        */
        Rendering(const Camera& camera,
                std::vector<std::shared_ptr<IPrimitive>>& primitives,
                std::vector<std::shared_ptr<ILight>>& lights,
                std::shared_ptr<IInterface> &interface);

        /**
        * @brief Destroy the Rendering object
        */
        ~Rendering();

        /**
        * @brief Render the scene to the provided interface
        * @param interface The output interface (e.g., PPM)
        */
        void render(void);

    private:
        /**
         * @brief Render all the line with id interval
         * @param id The number of line interval to render
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
        * @return The computed color
        */
        Lib::Vector3 rayColor(const Ray& ray, int max_depth);

        // /**
        // * @brief Check if the ray intersects with any object in the scene
        // * @param ray The ray to check for intersections
        // * @param ray_t The interval for the ray
        // * @param rec The intersection details if an intersection occurs
        // * @return True if an intersection occurs, false otherwise
        // */
        // bool worldHit(const Ray& ray, Interval ray_t, Intersection& rec);

        /**
        * @brief Compute the color for a ray-intersection
        * @param ray The ray that caused the intersection
        * @param intersection The intersection details
        * @param depth The current recursion depth (for reflections/refractions)
        * @return The computed color
        */
        Lib::Vector3 computeColor(const Ray& ray, const Intersection& intersection, int depth = 0);

        /**
        * @brief Calculate the lighting at an intersection point
        * @param intersection The intersection details
        * @param ray The ray that caused the intersection
        * @return The computed lighting color
        */
        Lib::Vector3 calculateLighting(const Intersection& intersection, const Ray& ray);

        const Camera& _camera;
        std::vector<std::shared_ptr<IPrimitive>>& _primitives;
        std::vector<std::shared_ptr<ILight>>& _lights;
        std::shared_ptr<IInterface> _interface;
        unsigned int _nb_thread;
        std::atomic<unsigned int> _nb_running_thread;
        std::vector<std::thread> _list_thread;
        std::atomic<int> _lines_rendered;

        const std::chrono::milliseconds _framerate;
        std::shared_ptr<HittableList> _world;
    };



} // namespace Raytracer

#endif // RENDERING_HPP