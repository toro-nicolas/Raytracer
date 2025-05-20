/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Camera class implementation
*/
/**
 * @file Camera.cpp
 * @brief The Camera class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Camera.hpp"

namespace Raytracer {
    Camera::Camera()
    {
        _position = Lib::Vector3(-1, 2, -1);
        _rotation = Lib::Vector3();
        lookAt = Lib::Vector3(0, 2, 0);
        upVector = Lib::Vector3(0, 1, 0);
        createViewport();
        _backgroundColor = Lib::Vector3(0, 0, 0);
    }

    Camera::~Camera()
    {
    }

    const std::array<int, 2> &Camera::getResolution() const
    {
        return _resolution;
    }

    std::array<int, 2> &Camera::getResolution()
    {
        return _resolution;
    }

    void Camera::setResolution(const std::array<int, 2> &res)
    {
        _resolution = res;
    }

    const Lib::Vector3 &Camera::getPosition() const
    {
        return _position;
    }

    Lib::Vector3 &Camera::getPosition()
    {
        return _position;
    }

    void Camera::setPosition(const Lib::Vector3 &pos)
    {
        _position = pos;
    }

    const Lib::Vector3 &Camera::getRotation() const
    {
        return _rotation;
    }

    Lib::Vector3 &Camera::getRotation()
    {
        return _rotation;
    }

    void Camera::setRotation(const Lib::Vector3 &rot)
    {
        _rotation = rot;
        lookAt += rot;
    }

    const double &Camera::getFov() const
    {
        return _fov;
    }

    double &Camera::getFov()
    {
        return _fov;
    }

    void Camera::setFov(const double &fov)
    {
        _fov = fov;
    }

    Lib::Vector3 &Camera::getBackgroundColor()
    {
        return _backgroundColor;
    }
    const Lib::Vector3 &Camera::getBackgroundColor() const
    {
        return _backgroundColor;
    }
    void Camera::setBackgroundColor(const Lib::Vector3 &backgroundColor)
    {
        _backgroundColor = backgroundColor;
    }

    const double &Camera::getDefocusAngle() const
    {
        return _defocusAngle;
    }
    double &Camera::getDefocusAngle()
    {
        return _defocusAngle;
    }
    void Camera::setDefocusAngle(const double &defocusAngle)
    {
        _defocusAngle = defocusAngle;
    }
    const double &Camera::getFocusDistance() const
    {
        return _focusDist;
    }
    double &Camera::getFocusDistance()
    {
        return _focusDist;
    }
    void Camera::setFocusDistance(const double &focusDist)
    {
        _focusDist = focusDist;
    }

    const int &Camera::getMaxDepth() const
    {
        return _maxDepth;
    }

    int &Camera::getMaxDepth()
    {
        return _maxDepth;
    }

    void Camera::setMaxDepth(int maxDepth)
    {
        _maxDepth = maxDepth;
    }

    const int &Camera::getSamplesPerPixels() const
    {
        return _samplesPerPixels;
    }

    int &Camera::getSamplesPerPixels()
    {
        return _samplesPerPixels;
    }

    void Camera::setSamplesPerPixels(int samplesPerPixels)
    {
        _samplesPerPixels = samplesPerPixels;
    }

    const double &Camera::getPixelsSampleScale() const
    {
        return _pixelsSampleScale;
    }

    double &Camera::getPixelsSampleScale()
    {
        return _pixelsSampleScale;
    }

    void Camera::setPixelsSampleScale(double pixelsSampleScale)
    {
        _pixelsSampleScale = pixelsSampleScale;
    }

    const Lib::Vector3 &Camera::getInitialLookAt() const
    {
        return _initialLookAt;
    }

    Lib::Vector3 &Camera::getInitialLookAt()
    {
        return _initialLookAt;
    }

    void Camera::setInitialLookAt(const Lib::Vector3 &initialLookAt)
    {
        _initialLookAt = initialLookAt;
        lookAt = _initialLookAt + _rotation;
    }

    void Camera::createViewport(void)
    {
        auto aspect_ratio = 16.0 / 9.0;
        // auto aspect_ratio = 1.0;
        int RtwImage_width = _resolution[0];
        int RtwImage_height = int(RtwImage_width / aspect_ratio);
        RtwImage_height = (RtwImage_height < 1) ? 1 : RtwImage_height;
        _resolution[1] = RtwImage_height;
        auto center = _position;

        auto theta = Lib::degToRad(_fov);
        auto h = std::tan(theta/2);
        auto viewport_height = 2 * h * _focusDist;
        // auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(_resolution[0])/_resolution[1]);

        w = unit_vector(_position - lookAt);
        u = unit_vector(cross(upVector, w));
        v = cross(w, u);
        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
        auto viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixelDeltaU = viewport_u / _resolution[0];
        pixelDeltaV = viewport_v / _resolution[1];
        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = center - (_focusDist * w) - viewport_u/2 - viewport_v/2;
        firstPixel = viewport_upper_left + 0.5 * (pixelDeltaU + pixelDeltaV);

        auto defocus_radius = _focusDist * std::tan(Lib::degToRad(_defocusAngle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;

    }

    std::ostream &operator<<(std::ostream &os, const Camera &camera)
    {
        os << UNDERLINE << "CAMERA:" << RESET << std::endl;
        os << "- Resolution: " << camera.getResolution()[0] << "x" << camera.getResolution()[1] << std::endl;
        os << "- Position: " << camera.getPosition() << std::endl;
        os << "- Initial look at: " << camera.getInitialLookAt() << std::endl;
        os << "- Rotation: " << camera.getRotation() << std::endl;
        os << "- Look at: " << camera.lookAt << std::endl;
        os << "- Field of view: " << camera.getFov() << std::endl;
        os << "- Defocus angle: " << camera.getDefocusAngle() << std::endl;
        os << "- Focus distance: " << camera.getFocusDistance() << std::endl;
        os << "- Max depth: " << camera.getMaxDepth() << std::endl;
        os << "- Samples per pixel: " << camera.getSamplesPerPixels() << std::endl;
        os << "- Pixels sample scale: " << camera.getPixelsSampleScale() << std::endl;
        os << "- Background color: " << camera.getBackgroundColor() << std::endl;
        return os;
    }
}