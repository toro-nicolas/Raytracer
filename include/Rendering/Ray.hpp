/*
** EPITECH PROJECT, 2025
** Ray.hpp
** File description:
** Ray declaration
*/

#ifndef RAY_HPP
    #define RAY_HPP
    #include "Lib.hpp"
    #include <limits>
    #include <memory>

using namespace Lib;


namespace Raytracer {
    class IMaterial;
    /**
    * @class Ray
    * @brief Represents a ray with origin and direction
    */
    class Ray {
    public:

        Ray() = default;
        /**
        * @brief Construct a new Ray object
        * @param origin The origin point of the ray
        * @param direction The direction vector of the ray (will be normalized)
        */
        Ray(const Lib::Vector3& origin, const Lib::Vector3& direction, double t);

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

        double &getTime(void);
        const double &getTime(void) const;

    private:
        Lib::Vector3 _origin;
        Lib::Vector3 _direction;
        double _t;
    };

    /**
    * @struct Intersection
    * @brief Represents an intersection between a ray and a primitive
    */
    class Intersection {
    public:
        Vector3 p;
        Vector3 normal;
        std::vector<std::pair<std::string, std::shared_ptr<IMaterial>>> material;
        double t;
        bool front_face;
        double u;
        double v;

        void setFaceNormal(const Ray& r, const Vector3& outward_normal);
    };



    class AABB {
        public:
            Interval x, y, z;
            AABB();
            AABB(const Interval& x, const Interval& y, const Interval& z);
            AABB(const Lib::Vector3& a, const Lib::Vector3& b);
            AABB(const AABB& box0, const AABB& box1);

            ~AABB();

            const Interval& axis_interval(int n) const;
            bool hit(const Ray& r, Interval& ray_t) const;
            int longestAxis() const;

            static const AABB empty, universe;
        private:
            void padToMinimum();
    };

    /**
     * @class Hittable
     * @brief Abstract class for hittable objects
     */
    class Hittable {
        public:
            virtual ~Hittable() = default;
            virtual bool hit(const Ray& ray, Interval ray_t, Intersection& rec) const = 0;
            virtual const AABB &boundingBox() const = 0;
            virtual AABB &boundingBox() = 0;

    };


}; // namespace Raytracer

#endif // RAY_HPP
