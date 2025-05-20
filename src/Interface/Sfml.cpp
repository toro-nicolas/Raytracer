/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Sfml class implementation
*/
/**
 * @file Sfml.cpp
 * @brief The Sfml class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Sfml.hpp"

namespace Raytracer {
    Sfml::Sfml(void)
    : _filename(""), _image(), _texture(), _sprite(), _window(sf::VideoMode(800, 600), "RayTracer", sf::Style::None)
    {
        _image.create(800, 600, sf::Color::Transparent);
        if (!_texture.loadFromImage(_image)) {
            throw Lib::Exceptions::Critical("Sfml::Sfml(): texture::loadFromImage() failed.");
        }
        _sprite.setTexture(_texture, true);
    }

    Sfml::~Sfml()
    {
        for (size_t y = 0; y < _pixels.size(); y++) {
            for (size_t x = 0; x < _pixels[y].size(); x++) {
                _image.setPixel(x, y, sf::Color(_pixels[y][x].x, _pixels[y][x].y, _pixels[y][x].z));
            }
        }
        _texture.update(_image);
        if (!_filename.empty() && !_image.saveToFile(_filename)) {
            ERROR << "CRITICAL ERROR: " << "Sfml::~Sfml(): image::saveToFile() failed.";
        }
        std::cout << "\rDone !                                 " << std::endl;
        std::cout << "You can find your image in: " << _filename << std::endl;
    }

    void Sfml::resize(void)
    {
        _window.close();
        _window.create(sf::VideoMode(_resolution[0], _resolution[1]), "RayTracer", sf::Style::Close);
        _image.create(_resolution[0], _resolution[1], sf::Color::Transparent);
        if (!_texture.loadFromImage(_image)) {
            throw Lib::Exceptions::Critical("Sfml::resize(): texture::loadFromImage() failed.");
        }
        _sprite.setTexture(_texture, true);
    }

    void Sfml::setupOutputFile(const std::string &filename)
    {
        _filename = filename + ".png";
    }

    void Sfml::render(void)
    {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }

        for (size_t y = 0; y < _pixels.size(); y++) {
            for (size_t x = 0; x < _pixels[y].size(); x++) {
                _image.setPixel(x, y, sf::Color(_pixels[y][x].x, _pixels[y][x].y, _pixels[y][x].z));
            }
        }
        _texture.update(_image);

        _window.clear();
        _window.draw(_sprite);
        _window.display();
    }


    extern "C" std::unique_ptr<IInterface> createInterface(void)
    {
        return std::unique_ptr<IInterface>(new Sfml());
    }
}