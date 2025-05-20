/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Perlin noise generator class declaration
*/
/**
 * @file Perlin.hpp
 * @brief The Perlin noise generator class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef PERLIN_HPP
    #define PERLIN_HPP

    #include "Lib.hpp"

namespace Raytracer {
    /**
     * @class Perlin
     * @brief Perlin noise generator class
     */
    class Perlin {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Perlin noise generator
             */
            Perlin();



            /* Generation functions */

            /**
             * @brief Generate noise at given point
             * @param p 3D point vector
             * @return double Noise value [0.0-1.0]
             */
            [[nodiscard]] double noise(const Lib::Vector3& p) const;

            /**
             * @brief Generate turbulence noise by summing noise at different frequencies
             * @param p 3D point vector
             * @param depth Number of noise frequencies to sum
             * @return double Turbulence value
             */
            double turb(const Lib::Vector3& p, int depth) const;



        private:
            static constexpr int point_count = 256; ///< Number of random vectors in noise
            std::vector<Lib::Vector3> randvec; ///< Random gradient vectors
            std::vector<int> perm_x; ///< Permutation table for x-axis
            std::vector<int> perm_y; ///< Permutation table for y-axis
            std::vector<int> perm_z; ///< Permutation table for z-axis



            /**
             * @brief Generate permutation tables
             * @param p Permutation table to fill
             */
            static void perlinGeneratePerm(std::vector<int>& p);

            /**
             * @brief Shuffle permutation table
             * @param p Permutation table to shuffle
             */
            static void permute(std::vector<int>& p);

            /**
             * @brief Interpolate between grid points to compute perlin noise
             * @param c Grid of control points
             * @param u X-coordinate for interpolation
             * @param v Y-coordinate for interpolation
             * @param w Z-coordinate for interpolation
             * @return double Interpolated value
             */
            static double perlin_interp(const Lib::Vector3 c[2][2][2], double u, double v, double w);
    };
}

#endif // PERLIN_HPP