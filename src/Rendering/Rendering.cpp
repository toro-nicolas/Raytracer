/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Rendering class implementation
*/
/**
 * @file Rendering.cpp
 * @brief The Rendering class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Rendering.hpp"
#include "Ray.hpp"
#include "BVHNode.hpp"

namespace Raytracer {
    Rendering::Rendering(const Camera& camera,
                         std::vector<std::shared_ptr<IPrimitive>>& primitives,
                         std::vector<std::shared_ptr<ILight>>& lights,
                         std::shared_ptr<IInterface> &interface)
        : _camera(camera), _primitives(primitives), _lights(lights), _interface(interface), _nb_thread(std::thread::hardware_concurrency()), _nb_running_thread(0), _list_thread(_nb_thread), _lines_rendered(0), _framerate(1000 / 60)
    {
        _world = std::make_shared<HittableList>();
        for (auto& object : _primitives) {
            _world->add(object);
            for (auto &child : object->getChildren()) {
                if (child) {
                    _world->add(child);
                }
            }
        }
        _world = std::make_shared<HittableList>(std::make_shared<BvhNode>(*_world));
    }

    Rendering::~Rendering()
    {
    }

    using namespace Lib;
    using Color = Vector3;


    void Rendering::render(void)
    {
        const auto& resolution = _camera.getResolution();
        int image_width = resolution[0];
        int image_height = resolution[1];
        DEBUG << "Rendering::render: image_width: " << image_width << ", image_height: " << image_height;

        _interface->setResolution(image_width, image_height);
        for (unsigned int i = 0; i < _nb_thread; i++) {
            _list_thread[i] = std::thread(&Rendering::thread_rendering, this, i);
            _nb_running_thread += _list_thread[i].joinable();
        }
        std::chrono::time_point<std::chrono::high_resolution_clock> next_tick = std::chrono::high_resolution_clock::now();
        int last_lines_rendered = 0;
        while (_nb_running_thread) {
            std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
            if (now >= next_tick && last_lines_rendered < _lines_rendered) {
                _interface->render();
                std::clog << "\rScanlines done: " << _lines_rendered << '/' << image_height << std::flush;
                do {
                    next_tick += _framerate;
                } while (now >= next_tick);
            }
        }
        for (auto &thread : _list_thread) {
            thread.join();
        }
        std::clog << "\rScanlines done: " << _lines_rendered << '/' << image_height << std::flush;
    }

    void Rendering::thread_rendering(int id)
    {
        const auto& resolution = _camera.getResolution();
        int image_width = resolution[0];
        int image_height = resolution[1];

        for (size_t j = id; j < image_height; j += _nb_thread) {
            for (size_t i = 0; i < image_width; i++) {
                auto pixel_center = _camera.firstPixel + (i * _camera.pixelDeltaU) + (j * _camera.pixelDeltaV);
                auto ray_direction = pixel_center - _camera.getPosition();
                Color pixel_color = Vector3(0, 0, 0);
                for (int sample = 0; sample < _camera.getSamplesPerPixels(); sample++) {
                    auto ray = generateRay(i, j);
                    pixel_color += rayColor(ray, _camera.getMaxDepth());
                }
                _interface->writeColor(i, j, pixel_color * _camera.getPixelsSampleScale());
            }
            _lines_rendered++;
        }
        _nb_running_thread--;
    }

    Ray Rendering::generateRay(int x, int y)
    {
        auto offset = sampleSquare();
        auto pixel_sample = _camera.firstPixel
                            + ((x + offset.x) * _camera.pixelDeltaU)
                            + ((y + offset.y) * _camera.pixelDeltaV);
        auto center = _camera.getPosition();

        auto point = random_in_unit_disk();
        auto defocus_disk =
            center
            + (_camera.defocus_disk_u * point.x)
            + (_camera.defocus_disk_v * point.y);

        auto ray_origin =
            (_camera.getDefocusAngle() <= 0) ? center : defocus_disk;
        auto ray_direction = pixel_sample - ray_origin;
        auto ray_time = random_double();
        return Ray(ray_origin, ray_direction, ray_time);
    }

    Color Rendering::rayColor(const Ray& ray, int max_depth)
    {
        Intersection rec;
        Interval ray_t(0.001, std::numeric_limits<double>::infinity());
        Color color;
        bool material_apply = false;

        if (max_depth <= 0)
            return Lib::Vector3(0, 0, 0);

        if (!_world->hit(ray, ray_t, rec))
            return _camera.getBackgroundColor();

        Ray scattered;
        Color attenuation;

        // Get emission from emissive materials
        Color color_from_emission; // = rec.material[0].second->emitted(rec.u, rec.v, rec.p);
        for (const auto& material : rec.material) {
            color_from_emission += material.second->emitted(rec.u, rec.v, rec.p);
        }

        // Get surface properties for lighting calculations
        Lib::Vector3 normal = rec.normal;
        Lib::Vector3 view_dir = -ray.direction().unit_vector();
        Lib::Vector3 point = rec.p;

        // Calculate light contributions from all lights
        Lib::Vector3 light_contribution(0, 0, 0);
        for (const auto& light : _lights) {
            light_contribution += light->compute(point, normal, view_dir);
        }

        // Apply material effects
        for (const auto& material : rec.material) {
            if (material.second->scatter(ray, rec, attenuation, scattered)) {
                material_apply = true;
            }
        }
        if (material_apply) {
            // For non-emissive materials, apply lighting
            color = attenuation * (rayColor(scattered, max_depth - 1) + light_contribution);
            return color + color_from_emission;
        } else {
            // For emissive materials, just return their emission
            return color_from_emission;
        }
    }
}