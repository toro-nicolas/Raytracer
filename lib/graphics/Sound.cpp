/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Sound class implementation
*/
/**
 * @file Sound.cpp
 * @brief The Sound class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Sound.hpp"

namespace Graphics {
    Sound::Sound(const std::string& path)
    {
        _buffer = std::make_shared<sf::SoundBuffer>();
        if (!_buffer->loadFromFile(path)) {
            throw std::runtime_error("Failed to load sound file");
        }
        _sound = std::make_shared<sf::Sound>(*_buffer);
        defaultAttributes();
    }

    Sound::Sound(std::shared_ptr<sf::SoundBuffer> buffer)
    {
        _buffer = buffer;
        if (!_buffer) {
            throw std::runtime_error("Failed to load sound buffer");
        }
        _sound = std::make_shared<sf::Sound>(*_buffer);
        defaultAttributes();
    }

    void Sound::defaultAttributes()
    {
        _sound = std::make_shared<sf::Sound>(*_buffer);
        _volume = 100;
        _defaultVolume = _volume;
        _sound->setVolume(_volume);
        _state = STOPPED;
        _muted = false;
    }


    void Sound::play()
    {
        _state = PLAYING;
        _sound->play();
    }

    void Sound::pause()
    {
        if (_state == PLAYING) {
            _sound->pause();
            _state = PAUSED;
        }
    }

    void Sound::stop()
    {
        if (_state == PLAYING || _state == PAUSED) {
            _sound->stop();
            _state = STOPPED;
        }
    }

    void Sound::loop(const bool loop)
    {
        if (_state != PLAYING) {
            _sound->setLooping(loop);
            this->play();
        }
    }

    void Sound::setVolume(const float volume)
    {
        _volume = std::clamp(volume, 0.f, 100.f);
        _sound->setVolume(_volume * !_muted);
    }

    void Sound::mute(const bool mute)
    {
        _muted = mute;
        _sound->setVolume(_volume * !_muted);
    }

    bool Sound::isMuted() const
    {
        return _muted;
    }

    bool Sound::isPlaying() const
    {
        return _state == PLAYING;
    }

    float& Sound::getDefaultVolume(void)
    {
        return _defaultVolume;
    }
}
