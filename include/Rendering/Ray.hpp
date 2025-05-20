/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Ray class declaration
*/
/**
 * @file Ray.hpp
 * @brief The Ray class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef RAY_HPP
    #define RAY_HPP

    #include "Lib.hpp"

using namespace Lib;

namespace Raytracer {
    class IMaterial; ///< Forward declaration of the IMaterial class

    /**
    * @class Ray
    * @brief Represents a ray with origin and direction
    */
    class Ray {
        public:
            /* Constructors and destructors */

            /**
             * @brief Default constructor for Ray
             */
            Ray() = default;
            /**
            * @brief Construct a new Ray object
            * @param origin The origin point of the ray
            * @param direction The direction vector of the ray (will be normalized)
            * @param t The ray parameter
            */
            Ray(const Lib::Vector3& origin, const Lib::Vector3& direction, double t);

            /**
            * @brief Construct a new Ray object
            * @param origin The origin point of the ray
            * @param direction The direction vector of the ray (will be normalized)
            */
            Ray(const Lib::Vector3& origin, const Lib::Vector3& direction);

            /**
            * @brief Destructor
            */
            ~Ray();

            /**
            * @brief Copy constructor
            * @param other The ray to copy
            */
            Ray(const Ray& other);

            /**
            * @brief Assignment operator
            * @param other The ray to assign
            * @return A reference to this ray
            */
            Ray& operator=(const Ray& other);



            /* Getters and setters */

            /**
            * @brief Get the direction of the ray
            * @return The direction vector of the ray
            */
            const Vector3 &direction(void) const;

            /**
            * @brief Get the origin of the ray
            * @return The origin point of the ray
            */
            const Vector3 &origin(void) const;

            /**
            * @brief Get a point at a certain distance along the ray
            * @param t The distance along the ray
            * @return The point at distance t from the origin
            */
            Vector3 pointAt(float t) const;

            /**
            * @brief Get the color of the ray
            * @return The color vector of the ray
            */
            Vector3 getColor(void) const;

            /**
             * @brief Get the time parameter of the ray (non-const version)
             * @return Reference to the time parameter
             */
            double &getTime(void);

            /**
             * @brief Get the time parameter of the ray (const version)
             * @return Const reference to the time parameter
             */
            const double &getTime(void) const;



        private:
            Lib::Vector3 _origin; ///< Origin point of the ray
            Lib::Vector3 _direction; ///< Normalized direction vector of the ray
            double _t; ///< Time parameter of the ray
    };



    /**
    * @class Intersection
    * @brief Represents an intersection between a ray and a primitive
    */
    class Intersection {
        public:
            Vector3 p; ///< Intersection point
            Vector3 normal; ///< Surface normal at intersection point
            std::vector<std::pair<std::string, std::shared_ptr<IMaterial>>> material; ///< Materials at intersection point
            double t; ///< Ray parameter at intersection
            bool front_face; ///< Whether the intersection is on the front face
            double u; ///< Texture coordinate U
            double v; ///< Texture coordinate V



            /* Setters */

            /**
             * @brief Set the face normal based on the ray direction
             * @param r The ray that hit the surface
             * @param outward_normal The geometric normal pointing outward
             */
            void setFaceNormal(const Ray& r, const Vector3& outward_normal);
    };



    /**
     * @class AABB
     * @brief Axis-Aligned Bounding Box for efficient ray intersection tests
     */
    class AABB {
        public:
            Interval x, y, z; ///< Intervals for each axis



            /* Constructors and destructors */

            /**
             * @brief Default constructor creates an empty bounding box
             */
            AABB();

            /**
             * @brief Construct a new AABB from intervals along each axis
             * @param x Interval along the x-axis
             * @param y Interval along the y-axis
             * @param z Interval along the z-axis
             */
            AABB(const Interval& x, const Interval& y, const Interval& z);

            /**
             * @brief Construct a new AABB from min and max points
             * @param a Minimum point
             * @param b Maximum point
             */
            AABB(const Lib::Vector3& a, const Lib::Vector3& b);

            /**
             * @brief Construct a new AABB that contains two other AABBs
             * @param box0 First bounding box
             * @param box1 Second bounding box
             */
            AABB(const AABB& box0, const AABB& box1);

            /**
             * @brief Destructor
             */
            ~AABB();


            /* Getters and setters */

            /**
             * @brief Get the interval for a specific axis
             * @param n Axis index (0=x, 1=y, 2=z)
             * @return The interval along the specified axis
             */
            const Interval& axis_interval(int n) const;



            /* Rendering functions */

            /**
             * @brief Test if a ray intersects this bounding box
             * @param r The ray to test
             * @param ray_t Interval of valid hit distances (modified if hit found)
             * @return True if the ray hits the bounding box
             */
            bool hit(const Ray& r, Interval& ray_t) const;

            /**
             * @brief Find the axis with the longest extent
             * @return Axis index (0=x, 1=y, 2=z)
             */
            int longestAxis() const;



            static const AABB empty; ///< Constant representing an empty bounding box
            static const AABB universe; ///< Constant representing an infinite bounding box



        private:
            /**
             * @brief Pad the box to ensure minimum dimensions for numerical stability
             */
            void padToMinimum();
    };



    /**
     * @brief Add a vector offset to an AABB
     * @param bbox The original bounding box
     * @param offset The offset vector to add
     * @return A new AABB offset by the specified vector
     */
    AABB operator+(const AABB& bbox, const Lib::Vector3& offset);

    /**
     * @brief Add a vector offset to an AABB (reverse order)
     * @param offset The offset vector to add
     * @param bbox The original bounding box
     * @return A new AABB offset by the specified vector
     */
    AABB operator+(const Lib::Vector3& offset, const AABB& bbox);



    /**
     * @class Hittable
     * @brief Abstract class for objects that can be hit by rays
     */
    class Hittable {
        public:
            /* Constructors and destructors */

            /**
             * @brief Virtual destructor
             */
            virtual ~Hittable() = default;



            /* Rendering functions */

            /**
             * @brief Test if a ray hits this object
             * @param ray The ray to test
             * @param ray_t Interval of valid hit distances
             * @param rec Intersection record to be filled if hit occurs
             * @return True if the ray hits this object
             */
            virtual bool hit(const Ray& ray, Interval ray_t, Intersection& rec) const = 0;

            /**
             * @brief Get the bounding box of this object (const version)
             * @return The axis-aligned bounding box containing this object
             */
            virtual const AABB &boundingBox() const = 0;

            /**
             * @brief Get the bounding box of this object
             * @return The axis-aligned bounding box containing this object
             */
            virtual AABB &boundingBox() = 0;
    };
};

#endif // RAY_HPP
