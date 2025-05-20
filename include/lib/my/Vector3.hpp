/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Vector3 class declaration
*/
/**
 * @file Vector3.hpp
 * @brief The Vector3 class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef VECTOR3_HPP
    #define VECTOR3_HPP

    #include <ostream>
    #include <cmath>
    #include <algorithm>
    #include <stdexcept>

namespace Lib {
    /**
     * @class Vector3
     * @brief A class representing a 3D vector
     */
    class Vector3 {
        public:
            double x; ///< X coordinate
            double y; ///< Y coordinate
            double z; ///< Z coordinate



            /* Constructors and destructors */

            /**
             * @brief Default constructor for Vector3
             * @param x_ X coordinate (default: 0)
             * @param y_ Y coordinate (default: 0)
             * @param z_ Z coordinate (default: 0)
             */
            Vector3(double x_ = 0, double y_ = 0, double z_ = 0);

            /**
             * @brief Copy constructor for Vector3
             * @param other The Vector3 object to copy
             */
            Vector3(const Vector3 &other);

            /**
             * @brief Destructor for Vector3
             */
            ~Vector3() = default;



            /* Operator overloads */

            /**
             * @brief Assignment operator for Vector3
             * @param other The Vector3 object to assign
             * @return Reference to the current object
             */
            Vector3 &operator=(const Vector3 &other);

            /**
             * @brief Subtraction operator for Vector3
             * @param other The Vector3 object to subtract
             * @return A new Vector3 object with the result of the subtraction
             */
            Vector3 operator-(const Vector3 &other) const;

            /**
             * @brief Negation operator for Vector3
             * @return A new Vector3 object with negated coordinates
             */
            Vector3 operator-() const;

            /**
             * @brief Subtraction assignment operator for Vector3
             * @param other The Vector3 object to subtract
             * @return Reference to the current object
             */
            Vector3 &operator-=(const Vector3 &other);

            /**
             * @brief Addition operator for Vector3
             * @param other The Vector3 object to add
             * @return A new Vector3 object with the result of the addition
             */
            Vector3 operator+(const Vector3 &other) const;

            /**
             * @brief Addition assignment operator for Vector3
             * @param other The Vector3 object to add
             * @return Reference to the current object
             */
            Vector3 &operator+=(const Vector3 &other);

            /**
             * @brief Multiplication operator for Vector3
             * @param other The Vector3 object to multiply
             * @return A new Vector3 object with the result of the multiplication
             */
            Vector3 operator*(const Vector3 &other) const;

            /**
             * @brief Multiplication assignment operator for Vector3
             * @param other The Vector3 object to multiply
             * @return Reference to the current object
             */
            Vector3 &operator*=(const Vector3 &other);

            /**
             * @brief Multiplication operator for Vector3 and scalar
             * @param value The scalar value to multiply
             * @return A new Vector3 object with the result of the multiplication
             */
            Vector3 operator*(double value) const;

            /**
             * @brief Multiplication assignment operator for Vector3 and scalar
             * @param value The scalar value to multiply
             * @return Reference to the current object
             */
            Vector3 &operator*=(double value);

            /**
             * @brief Division operator for Vector3 and scalar
             * @param value The scalar value to divide
             * @return A new Vector3 object with the result of the division
             */
            Vector3 operator/(double value) const;

            /**
             * @brief Division assignment operator for Vector3 and scalar
             * @param value The scalar value to divide
             * @return Reference to the current object
             */
            Vector3 &operator/=(double value);

            /**
             * @brief Division operator for Vector3
             * @param other The Vector3 object to divide
             * @return A new Vector3 object with the result of the division
             */
            Vector3 operator/(const Vector3 &other) const;

            /**
             * @brief Division assignment operator for Vector3
             * @param other The Vector3 object to divide
             * @return Reference to the current object
             */
            Vector3 &operator/=(const Vector3 &other);

            /**
             * @brief Index operator for Vector3
             * @param index The index of the coordinate (0, 1, or 2)
             * @return Reference to the coordinate at the specified index
             */
            double &operator[](int index);

            /**
             * @brief Index operator for Vector3 (const version)
             * @param index The index of the coordinate (0, 1, or 2)
             * @return Reference to the coordinate at the specified index
             */
            const double &operator[](int index) const;

            /**
             * @brief Less than operator for Vector3
             * @param other The Vector3 object to compare
             * @return True if the current object is less than the other, false otherwise
             */
            bool operator==(const Vector3 &other) const;

            /**
             * @brief Greater than operator for Vector3
             * @param other The Vector3 object to compare
             * @return True if the current object is greater than the other, false otherwise
             */
            bool operator!=(const Vector3 &other) const;


            /* Vector functions */

            /**
             * @brief Dot product of two vectors
             * @param other The other vector
             * @return The dot product result
             */
            double dot(const Vector3 &other) const;

            /**
             * @brief Cross product of two vectors
             * @param other The other vector
             * @return A new Vector3 object with the result of the cross product
             */
            Vector3 cross(const Vector3 &other) const;

            /**
             * @brief Calculate the length of the vector (the norm)
             * @return The length of the vector
             */
            double length() const;

            /**
             * @brief Calculate the squared length of the vector
             * @return The squared length of the vector
             */
            double length_squared() const;

            /**
             * @brief Normalize the vector (make it a unit vector)
             * @return A new Vector3 object with the normalized vector
             */
            Vector3 unit_vector() const;

            /**
             * @brief Reflect the vector around a normal vector
             * @param normal The normal vector to reflect around
             * @return A new Vector3 object with the reflected vector
             */
            Vector3 reflect(const Vector3 &normal) const;

            /**
             * @brief Clamp the vector components to a specified range
             * @param min The minimum value for clamping
             * @param max The maximum value for clamping
             * @return A new Vector3 object with the clamped vector
             */
            Vector3 clamp(double min, double max) const;

            /**
             * @brief Generate a random vector with components in the range [min, max]
             * @param min The minimum value for each component
             * @param max The maximum value for each component
             * @return A new Vector3 object with the random vector
             */
            static Vector3 random(double min, double max);

            /**
             * @brief Generate a random vector with components in the range [0, 1]
             * @return A new Vector3 object with the random vector
             */
            static Vector3 random();

            /**
             * @brief Generate a random vector with components in the range [0, 1]
             * @return A new Vector3 object with the random vector
             */
            bool nearZero() const;
    };



    /**
     * @brief Calculate the dot product of two vectors
     * @param v1 The first vector
     * @param v2 The second vector
     * @return The dot product result
     */
    double dot(const Vector3 &v1, const Vector3 &v2);

    /**
     * @brief Calculate the cross product of two vectors
     * @param v1 The first vector
     * @param v2 The second vector
     * @return A new Vector3 object with the result of the cross product
     */
    Vector3 cross(const Vector3 &v1, const Vector3 &v2);

    /**
     * @brief Normalize a vector (make it a unit vector)
     * @param v The vector to normalize
     * @return A new Vector3 object with the normalized vector
     */
    Vector3 unit_vector(const Vector3 &v);

    /**
     * @brief Generate a random vector with components in the range [0, 1]
     * @return A new Vector3 object with the random vector
     */
    Vector3 random_unit_vector();

    /**
     * @brief Generate a random vector in a unit disk
     * @return A new Vector3 object with the random vector
     */
    Vector3 random_in_unit_disk();

    /**
     * @brief Reflect a vector around a normal vector
     * @param v The vector to reflect
     * @param normal The normal vector to reflect around
     * @return A new Vector3 object with the reflected vector
     */
    Vector3 reflect(const Vector3 &v, const Vector3 &normal);

    /**
     * @brief Refract a vector through a surface
     * @param uv The incident vector
     * @param n The normal vector at the surface
     * @param etai_over_etat The ratio of indices of refraction
     * @return A new Vector3 object with the refracted vector
     */
    Vector3 refract(const Vector3& uv, const Vector3& n, double etai_over_etat);

    /**
     * @brief Overload the operator << for the Vector class
     * @param os The output stream
     * @param camera The camera to display
     * @return <b>std::ostream &</b> The output stream
     */
    std::ostream &operator<<(std::ostream &os, const Vector3 &vec);

    /**
     * @brief Overload the operator * for scalar multiplication
     * @param scalar The scalar value
     * @param v The vector to multiply
     * @return A new Vector3 object with the result of the multiplication
     */
    Vector3 operator*(double scalar, const Vector3& v);

    /**
     * @brief Overload the operator / for scalar division
     * @param scalar The scalar value
     * @param v The vector to divide
     * @return A new Vector3 object with the result of the division
     */
    Vector3 sampleSquare();

    /**
     * @brief Generate a random point on a sphere
     * @param radius The radius of the sphere
     * @return A new Vector3 object with the random point on the sphere
     */
    Vector3 randomOn(const Vector3 &normal);
}

#endif