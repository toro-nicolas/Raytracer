/*
** EPITECH PROJECT, 2025
** RtwImage.hpp
** File description:
** RtwImage declaration
*/


#ifndef RTWIMAGE_HPP
    #define RTWIMAGE_HPP

#include <string>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace Raytracer {

class RtwImage {
public:
    explicit RtwImage() = default;
    explicit RtwImage(const std::string& filename);
    ~RtwImage();

    int width() const;
    int height() const;
    const unsigned char* pixelData(int x, int y) const;

private:
    static constexpr int m_bytesPerPixel = 3;

    int m_width = 0;
    int m_height = 0;
    int m_bytesPerScanline = 0;

    float* m_floatData = nullptr;
    std::unique_ptr<unsigned char[]> m_byteData;

    static int clamp(int x, int low, int high);
    static unsigned char floatToByte(float value);

    bool loadFromFile(const std::string& filename);
    void convertToBytes();
};

} // namespace Raytracer

#endif // RTWIMAGE_HPP
