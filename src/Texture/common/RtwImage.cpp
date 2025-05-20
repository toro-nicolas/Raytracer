/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The RtwImage class implementation
*/
/**
 * @file RtwImage.cpp
 * @brief The RtwImage class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "RtwImage.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Raytracer {
    RtwImage::RtwImage(const std::string& filename)
    {
        if (!loadFromFile(filename)) {
            throw std::runtime_error("Failed to load RtwImage: " + filename);
        }
    }

    RtwImage::~RtwImage()
    {
        stbi_image_free(m_floatData);
    }

    int RtwImage::width() const
    {
        return m_width;
    }

    int RtwImage::height() const
    {
        return m_height;
    }

    const unsigned char* RtwImage::pixelData(int x, int y) const
    {
        static constexpr unsigned char magenta[] = {255, 0, 255};
        if (!m_byteData) return magenta;

        x = clamp(x, 0, m_width);
        y = clamp(y, 0, m_height);

        return m_byteData.get() + y * m_bytesPerScanline + x * m_bytesPerPixel;
    }

    int RtwImage::clamp(int x, int low, int high)
    {
        return std::max(low, std::min(x, high - 1));
    }

    unsigned char RtwImage::floatToByte(float value)
    {
        if (value <= 0.0f) return 0;
        if (value >= 1.0f) return 255;
        return static_cast<unsigned char>(value * 256.0f);
    }

    bool RtwImage::loadFromFile(const std::string& filename)
    {
        int n = m_bytesPerPixel;
        m_floatData = stbi_loadf(filename.c_str(), &m_width, &m_height, &n, m_bytesPerPixel);
        if (!m_floatData)
            return false;

        m_bytesPerScanline = m_width * m_bytesPerPixel;
        convertToBytes();
        return true;
    }

    void RtwImage::convertToBytes()
    {
        int totalBytes = m_width * m_height * m_bytesPerPixel;
        m_byteData = std::make_unique<unsigned char[]>(totalBytes);

        for (int i = 0; i < totalBytes; ++i) {
            m_byteData[i] = floatToByte(m_floatData[i]);
        }
    }
}
