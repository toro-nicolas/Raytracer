/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Vector3 class implementation
*/
/**
 * @file Vector3.cpp
 * @brief The Vector3 class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Lib.hpp"
#include "Vector3.hpp"

namespace Lib {
    Vector3::Vector3(double x_, double y_, double z_)
        : x(x_), y(y_), z(z_)
    {
    }

    Vector3::Vector3(const Vector3 &other)
        : x(other.x), y(other.y), z(other.z)
    {
    }

    Vector3 Vector3::operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    Vector3& Vector3::operator=(const Vector3 &other)
    {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }
    Vector3 Vector3::operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3& Vector3::operator-=(const Vector3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    Vector3 Vector3::operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3& Vector3::operator+=(const Vector3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3 Vector3::operator*(const Vector3 &other) const
    {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    Vector3& Vector3::operator*=(const Vector3 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vector3 Vector3::operator*(double value) const
    {
        return Vector3(x * value, y * value, z * value);
    }


    Vector3& Vector3::operator*=(double value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    Vector3 Vector3::operator/(double value) const
    {
        if (value == 0) {
            throw std::runtime_error("Division by zero");
        }
        return Vector3(x / value, y / value, z / value);
    }

    Vector3& Vector3::operator/=(double value)
    {
        if (value == 0) {
            throw std::runtime_error("Division by zero");
        }
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    Vector3 Vector3::operator/(const Vector3 &other) const
    {
        if (other.x == 0 || other.y == 0 || other.z == 0) {
            throw std::runtime_error("Division by zero in vector component");
        }
        return Vector3(x / other.x, y / other.y, z / other.z);
    }

    Vector3& Vector3::operator/=(const Vector3 &other)
    {
        if (other.x == 0 || other.y == 0 || other.z == 0) {
            throw std::runtime_error("Division by zero in vector component");
        }
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    double &Vector3::operator[](int index)
    {
        if (index < 0 || index > 2) {
            throw std::out_of_range("Index out of range");
        }
        return index == 0 ? x : (index == 1 ? y : z);
    }

    const double &Vector3::operator[](int index) const
    {
        if (index < 0 || index > 2) {
            throw std::out_of_range("Index out of range");
        }
        return index == 0 ? x : (index == 1 ? y : z);
    }
    bool Vector3::operator==(const Vector3 &other) const
    {
        return (x == other.x && y == other.y && z == other.z);
    }
    bool Vector3::operator!=(const Vector3 &other) const
    {
        return !(*this == other);
    }

    double Vector3::dot(const Vector3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Vector3::cross(const Vector3 &other) const
    {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    double Vector3::length() const
    {
        return std::sqrt(length_squared());
    }

    double Vector3::length_squared() const
    {
        return x * x + y * y + z * z;
    }

    Vector3 Vector3::unit_vector() const
    {
        double len = length();
        if (len < 1e-8) {
            throw std::runtime_error("Cannot normalize zero-length vector");
        }
        return *this / len;
    }
    Vector3 Vector3::reflect(const Vector3 &normal) const
    {
        return *this - normal * 2 * this->dot(normal);
    }

    Vector3 Vector3::clamp(double min, double max) const
    {
        return Vector3(
            std::clamp(x, min, max),
            std::clamp(y, min, max),
            std::clamp(z, min, max));
    }
    Vector3 Vector3::random(double min, double max)
    {
        return Vector3(Lib::random_double(min, max), Lib::random_double(min, max), Lib::random_double(min, max));
    }

    Vector3 Vector3::random()
    {
        return Vector3(Lib::random_double(), Lib::random_double(), Lib::random_double());
    }

    bool Vector3::nearZero() const {
        auto s = 1e-8;
        return (std::fabs(x) < s) && (std::fabs(y) < s) && (std::fabs(z) < s);
    }

    // Fonctions globales
    double dot(const Vector3 &v1, const Vector3 &v2)
    {
        return v1.dot(v2);
    }

    Vector3 cross(const Vector3 &v1, const Vector3 &v2)
    {
        return v1.cross(v2);
    }

    Vector3 unit_vector(const Vector3 &v)
    {
        return v.unit_vector();
    }

    Vector3 random_unit_vector()
    {
        while (true) {
            auto p = Vector3::random(-1,1);
            auto lensq = p.length_squared();
            if (1e-160 < lensq && lensq <= 1)
                return p / sqrt(lensq);
        }
    }
    Vector3 random_in_unit_disk()
    {
        while (true) {
            auto p = Vector3(random_double(-1,1), random_double(-1,1), 0);
            if (p.length_squared() < 1)
                return p;
        }
    }

    Vector3 reflect(const Vector3 &v, const Vector3 &normal)
    {
        return v - 2 * dot(v, normal) * normal;
    }

    Vector3 refract(const Vector3& uv, const Vector3& n, double etai_over_etat)
    {
        auto cos_theta = std::fmin(dot(-uv, n), 1.0);
        Vector3 r_out_perp =  etai_over_etat * (uv + cos_theta * n);
        Vector3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
        return r_out_perp + r_out_parallel;
    }

    Vector3 operator*(double scalar, const Vector3& v)
    {
        return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
    }


    std::ostream &operator<<(std::ostream &os, const Vector3 &vec)
    {
        os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
        return os;
    }

    Vector3 sampleSquare()
    {
        return Lib::Vector3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    Vector3 randomOn(const Vector3 &normal) {
        Vector3 on_unit_sphere = random_unit_vector();
        if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
            return on_unit_sphere;
        else
            return -on_unit_sphere;
    }
}