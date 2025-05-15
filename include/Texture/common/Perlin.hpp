/*
** EPITECH PROJECT, 2025
** Perlin.hpp
** File description:
** Perlin noise generator declaration
*/

#ifndef PERLIN_HPP
#define PERLIN_HPP

#include "Lib.hpp"
#include "Vector3.hpp"
#include <memory>
#include <vector>

namespace Raytracer {
    /**
     * @brief Perlin noise generator class
     */
    class Perlin {
    public:
        /**
         * @brief Construct a new Perlin noise generator
         */
        Perlin();

        /**
         * @brief Generate noise at given point
         *
         * @param p 3D point vector
         * @return double Noise value [0.0-1.0]
         */
        [[nodiscard]] double noise(const Lib::Vector3& p) const;

        double turb(const Lib::Vector3& p, int depth) const;


    private:
        static constexpr int point_count = 256;
        std::vector<Lib::Vector3> randvec;
        std::vector<int> perm_x;
        std::vector<int> perm_y;
        std::vector<int> perm_z;

        /**
         * @brief Generate permutation tables
         *
         * @param p Permutation table to fill
         */
        static void perlinGeneratePerm(std::vector<int>& p);

        /**
         * @brief Shuffle permutation table
         *
         * @param p Permutation table to shuffle
         */
        static void permute(std::vector<int>& p);

        static double perlin_interp(const Lib::Vector3 c[2][2][2], double u, double v, double w);


    };

} // namespace Raytracer

#endif // PERLIN_HPP