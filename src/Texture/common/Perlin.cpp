/*
** EPITECH PROJECT, 2025
** Perlin.cpp
** File description:
** Perlin noise generator implementation
*/

#include "Perlin.hpp"
#include "Vector3.hpp"
#include <algorithm>
#include <random>

namespace Raytracer {

    Perlin::Perlin()
        : randvec(point_count)
        , perm_x(point_count)
        , perm_y(point_count)
        , perm_z(point_count)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        for (int i = 0; i < point_count; i++) {
            randvec[i] = Lib::unit_vector(Lib::Vector3::random(-1, 1));
        }
        perlinGeneratePerm(perm_x);
        perlinGeneratePerm(perm_y);
        perlinGeneratePerm(perm_z);
    }

    double Perlin::noise(const Lib::Vector3& p) const
    {
        auto u = p.x - std::floor(p.x);
        auto v = p.y - std::floor(p.y);
        auto w = p.z - std::floor(p.z);
        // Hermitian smoothing
        // u = u*u*(3-2*u);
        // v = v*v*(3-2*v);
        // w = w*w*(3-2*w);

        auto i = int(std::floor(p.x));
        auto j = int(std::floor(p.y));
        auto k = int(std::floor(p.z));
        Lib::Vector3 c[2][2][2];

        for (int di=0; di < 2; di++)
            for (int dj=0; dj < 2; dj++)
                for (int dk=0; dk < 2; dk++)
                    c[di][dj][dk] = randvec[
                        perm_x[(i+di) & 255] ^
                        perm_y[(j+dj) & 255] ^
                        perm_z[(k+dk) & 255]
                    ];

        return perlin_interp(c, u, v, w);
    }

    void Perlin::perlinGeneratePerm(std::vector<int>& p)
    {
        for (int i = 0; i < point_count; i++) {
            p[i] = i;
        }
        permute(p);
    }

    void Perlin::permute(std::vector<int>& p)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        // Modern Fisher-Yates shuffle
        for (int i = p.size() - 1; i > 0; i--) {
            std::uniform_int_distribution<int> dist(0, i);
            int target = dist(gen);
            std::swap(p[i], p[target]);
        }
    }

    double Perlin::perlin_interp(const Lib::Vector3 c[2][2][2], double u, double v, double w) {
        auto uu = u*u*(3-2*u);
        auto vv = v*v*(3-2*v);
        auto ww = w*w*(3-2*w);
        auto accum = 0.0;

        for (int i=0; i < 2; i++)
            for (int j=0; j < 2; j++)
                for (int k=0; k < 2; k++) {
                    Lib::Vector3 weight_v(u-i, v-j, w-k);
                    accum += (i*uu + (1-i)*(1-uu))
                           * (j*vv + (1-j)*(1-vv))
                           * (k*ww + (1-k)*(1-ww))
                           * dot(c[i][j][k], weight_v);
                }

        return accum;
    }

    double Perlin::turb(const Lib::Vector3& p, int depth) const {
        auto accum = 0.0;
        auto temp_p = p;
        auto weight = 1.0;

        for (int i = 0; i < depth; i++) {
            accum += weight * noise(temp_p);
            weight *= 0.5;
            temp_p *= 2;
        }
        return std::fabs(accum);
    }

} // namespace Raytracer
