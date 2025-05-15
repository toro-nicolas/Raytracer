/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Camera class declaration
*/
/**
 * @file Camera.hpp
 * @brief The Camera class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include "Lib.hpp"

namespace Raytracer {
    /**
     * @class Camera
     * @brief Represents a camera in the raytracer
     */
    class Camera
    {
        public:
            /* Constructor and Destructor */

            /**
             * @brief Constructor for Camera class
             */
            Camera();

            /**
             * @brief Destructor for Camera class
             */
            ~Camera();



            /* Getter and Setter functions (for config file) */

            /**
             * @brief Get the resolution of the camera
             * @return <b>const std::array<int, 2> &</b> The resolution of the camera
             */
            const std::array<int, 2> &getResolution() const;

            /**
             * @brief Get the resolution of the camera
             * @return <b>std::array<int, 2> &</b> The resolution of the camera
             */
            std::array<int, 2> &getResolution();

            /**
             * @brief Set the resolution of the camera
             * @param res The new resolution of the camera
             */
            void setResolution(const std::array<int, 2> &res);

            /**
             * @brief Get the position of the camera
             * @return <b>const Lib::Vector3 &</b> The position of the camera
             */
            const Lib::Vector3 &getPosition() const;

            /**
             * @brief Get the position of the camera
             * @return <b>Lib::Vector3 &</b> The position of the camera
             */
            Lib::Vector3 &getPosition();

            /**
             * @brief Set the position of the camera
             * @param pos The new position of the camera
             */
            void setPosition(const Lib::Vector3 &pos);

            /**
             * @brief Get the rotation of the camera
             * @return <b>const Lib::Vector3 &</b> The rotation of the camera
             */
            const Lib::Vector3 &getRotation() const;

            /**
             * @brief Get the rotation of the camera
             * @return <b>Lib::Vector3 &</b> The rotation of the camera
             */
            Lib::Vector3 &getRotation();

            /**
             * @brief Set the rotation of the camera
             * @param rot The new rotation of the camera
             */
            void setRotation(const Lib::Vector3 &rot);

            /**
             * @brief Get the field of view of the camera
             * @return <b>const double &</b> The field of view of the camera
             */
            const double &getFov() const;

            /**
             * @brief Get the field of view of the camera
             * @return <b>double &</b> The field of view of the camera
             */
            double &getFov();

            /**
             * @brief Set the field of view of the camera
             * @param fov The new field of view of the camera
             */
            void setFov(const double &fov);



            ////////////////////////////////////// depth of field / DEFOCUS //////////////////////////////////////

            /**
             * @brief Get the defocus angle of the camera
             * @return <b>const double &</b> The defocus angle of the camera
             */
            const double &getDefocusAngle() const;

            /**
             * @brief Get the defocus angle of the camera
             * @return <b>double &</b> The defocus angle of the camera
             */
            double &getDefocusAngle();

            /**
             * @brief Set the defocus angle of the camera
             * @param defocusAngle The new defocus angle of the camera
             */
            void setDefocusAngle(const double &defocusAngle);

            /**
             * @brief Get the focus distance of the camera
             * @return <b>const double &</b> The focus distance of the camera
             */
            const double &getFocusDistance() const;

            /**
             * @brief Get the focus distance of the camera
             * @return <b>double &</b> The focus distance of the camera
             */
            double &getFocusDistance();

            /**
             * @brief Set the focus distance of the camera
             * @param focusDistance The new focus distance of the camera
             */
            void setFocusDistance(const double &focusDistance);



            /**
             * @brief Get the maximum depth of the camera
             * @return <b>const int &</b> The maximum depth of the camera
             */
            const int &getMaxDepth() const;

            /**
             * @brief Get the maximum depth of the camera
             * @return <b>int &</b> The maximum depth of the camera
             */
            int &getMaxDepth();

            /**
             * @brief Set the maximum depth of the camera
             * @param maxDepth The maximum depth of the camera
             */
            void setMaxDepth(int maxDepth);

            /**
             * @brief Get the samples per pixels of the camera
             * @return <b>const int &</b> The samples per pixels of the camera
             */
            const int &getSamplesPerPixels() const;

            /**
             * @brief Get the samples per pixels of the camera
             * @return <b>int &</b> The samples per pixels of the camera
             */
            int &getSamplesPerPixels();

            /**
             * @brief Set the samples per pixels of the camera
             * @param samplesPerPixels The samples per pixels of the camera
             */
            void setSamplesPerPixels(int samplesPerPixels);

            /**
             * @brief Get the pixels samples scale of the camera
             * @return <b>const int &</b> The pixels sample scale of the camera
             */
            const double &getPixelsSampleScale() const;

            /**
             * @brief Get the pixels samples scale of the camera
             * @return <b>double &</b> The pixels sample scale of the camera
             */
            double &getPixelsSampleScale();

            /**
             * @brief Set the pixels sample scale of the camera
             * @param samplesPerPixels The pixels sample scale of the camera
             */
            void setPixelsSampleScale(double pixelSamplesScale);

            /**
             * @brief Get the initial look at vector of the camera
             * @return <b>const Lib::Vector3 &</b> The initial look at vector of the camera
             */
            const Lib::Vector3 &getInitialLookAt() const;

            /**
             * @brief Get the initial look at vector of the camera
             * @return <b>Lib::Vector3 &</b> The initial look at vector of the camera
             */
            Lib::Vector3 &getInitialLookAt();

            /**
             * @brief Set the initial look at vector of the camera
             * @param initialLookAt The new initial look at vector of the camera
             */
            void setInitialLookAt(const Lib::Vector3 &initialLookAt);



            ////////////////////////////////////// INIT //////////////////////////////////////
            /**
             * @brief Set the Viewport object
             * @details This function sets the viewport object of the camera
             * @return <b>void</b>
             */
            void createViewport(void);



            Lib::Vector3 firstPixel; ///< The first pixel of the camera
            Lib::Vector3 pixelDeltaU; ///< The delta U of the pixel
            Lib::Vector3 pixelDeltaV; ///< The delta V of the pixel
            Lib::Vector3 lookAt; ///< The look at vector of the camera
            Lib::Vector3 upVector; ///< The up vector of the camera
            Lib::Vector3 w, u, v; ///< The camera vectors
            Lib::Vector3 defocus_disk_u; ///< Defocus disk horizontal radius
            Lib::Vector3 defocus_disk_v; ///< Defocus disk vertical radius



        private:
            std::array<int, 2> _resolution = {1920, 1080}; ///< The resolution of the camera
            Lib::Vector3 _position; ///< The position of the camera
            Lib::Vector3 _rotation; ///< The rotation of the camera
            double _fov = 90; ///< The field of view of the camera
            double _defocusAngle = 0; ///< Variation angle of rays through each pixel
            double _focusDist = 10; ///< Distance from camera lookfrom point to plane of perfect focus
            int _maxDepth = 10; ///< The maximum depth of the camera
            int _samplesPerPixels = 10; ///< The number of samples per pixel
            double _pixelsSampleScale = 0.1; ///< The scale of the pixel samples
            Lib::Vector3 _initialLookAt; ///< The initial look at vector of the camera
    };



    /**
     * @brief Overload the operator << for the Camera class
     * @param os The output stream
     * @param camera The camera to display
     * @return <b>std::ostream &</b> The output stream
     */
    std::ostream &operator<<(std::ostream &os, const Camera &camera);
}

#endif /* CAMERA_HPP_ */
