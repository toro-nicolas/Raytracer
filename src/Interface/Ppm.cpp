/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Ppm class implementation
*/
/**
 * @file Ppm.cpp
 * @brief The Ppm class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Ppm.hpp"

namespace Raytracer {
    Ppm::Ppm(void)
    {
        //DEBUG << "Ppm constructor";
    }

    Ppm::~Ppm()
    {
        //DEBUG << "Ppm destructor";
        if (_file.is_open()) {
            _file << "P6" << std::endl;
            _file << ((_pixels.size() == 0) ? std::size_t(0) : _pixels[0].size()) << " " << _pixels.size() << std::endl;
            _file << "255" << std::endl;

            for (auto &line : _pixels) {
                for (auto &pixel : line) {
                    _file << (unsigned char)pixel.x << (unsigned char)pixel.y << (unsigned char)pixel.z;
                }
            }
            _file.close();
        }
        std::cout << "\rDone !                                 " << std::endl;
        std::cout << "You can find your image in: " << _filename << std::endl;
    }

    void Ppm::resize(void)
    {
        
    }

    void Ppm::setupOutputFile(const std::string &filename)
    {
        _filename = filename + ".ppm";
        _file = std::ofstream(_filename);
        if (_file.fail()) {
            throw Lib::Exceptions::Critical("Failed to open file: " + _filename);
        }
    }

    void Ppm::render(void)
    {
        
    }

    extern "C" std::unique_ptr<IInterface> createInterface(void)
    {
        return std::unique_ptr<IInterface>(new Ppm());
    }
}