/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Sound class declaration
*/
/**
 * @file Sound.hpp
 * @brief The Sound class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef SOUND_HPP
    #define SOUND_HPP

    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>

namespace Graphics {
    /**
     * @class Sound
     * @brief Represents a sound object with various attributes and controls
     */
    class Sound {
        public:
            /**
             * @brief Enum to represent the state of the sound
             */
            enum State {
                PLAYING, ///< Sound is currently playing
                PAUSED, ///< Sound is paused
                STOPPED ///< Sound is stopped
            };


        public:
            /**
             * @brief Construct a new Sound object from a file path
             * @param path Path to the sound file
             */
            Sound(const std::string& path);

            /**
             * @brief Construct a new Sound object from a buffer
             * @param buffer Shared pointer to a sound buffer
             */
            Sound(std::shared_ptr<sf::SoundBuffer> buffer);

            /**
             * @brief Destroy the Sound object
             */
            ~Sound() = default;

            /**
             * @brief Initialize sound with default attributes
             */
            void defaultAttributes();

            /**
             * @brief Play the sound
             */
            void play();

            /**
             * @brief Pause the sound
             */
            void pause();

            /**
             * @brief Stop the sound
             */
            void stop();

            /**
             * @brief Set if the sound should loop
             * @param loop Whether the sound should loop (true by default)
             */
            void loop(bool loop = 1);

            /**
             * @brief Set the volume of the sound
             * @param volume Volume value (between 0.0 and 100.0)
             */
            void setVolume(float volume);

            /**
             * @brief Mute or unmute the sound
             * @param mute Whether to mute the sound (true by default)
             */
            void mute(bool mute = 1);

            /**
             * @brief Check if the sound is muted
             * @return true If the sound is muted
             * @return false If the sound is not muted
             */
            bool isMuted() const;

            /**
             * @brief Check if the sound is currently playing
             * @return true If the sound is playing
             * @return false If the sound is not playing
             */
            bool isPlaying() const;

            /**
             * @brief Get the default volume
             * @return float& Reference to the default volume
             */
            float& getDefaultVolume(void);



        private:
            std::shared_ptr<sf::SoundBuffer> _buffer; ///< Shared pointer to the sound buffer
            std::shared_ptr<sf::Sound> _sound; ///< Shared pointer to the sound object
            float _volume; ///< Volume of the sound (between 0.0 and 100.0)
            float _defaultVolume; ///< Default volume of the sound (between 0.0 and 100.0)
            bool _muted; ///< Whether the sound is muted
            State _state; ///< State of the sound (PLAYING, PAUSED, STOPPED)

    };
}

#endif // SOUND_HPP
