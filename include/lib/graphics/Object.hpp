/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Object class declaration
*/
/**
 * @file Object.hpp
 * @brief The Object class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef OBJECT_HPP
    #define OBJECT_HPP

    #include <SFML/Graphics.hpp>
    #include <SFML/Graphics/Rect.hpp>
    #include <SFML/Graphics/RectangleShape.hpp>
    #include <SFML/System/Vector2.hpp>
    #include <chrono>

namespace Graphics {
    /**
     * @class Object
     * @brief Represents a graphical object with a texture and hitbox
     */
    class Object {
        public:
            /**
             * @brief Construct a new Object with a texture from a file path
             * @param path Path to the texture file
             * @param hitboxColor Color of the hitbox outline
             */
            Object(const std::string& path, sf::Color hitboxColor = sf::Color::Blue);
            
            /**
             * @brief Construct a new Object with an existing texture
             * @param text Shared pointer to an existing texture
             * @param hitboxColor Color of the hitbox outline
             */
            Object(const std::shared_ptr<sf::Texture>& text, sf::Color hitboxColor = sf::Color::Blue);
            
            /**
             * @brief Destroy the Object object
             */
            ~Object() = default;
            
            /**
             * @brief Initialize default attribute values
             * @param hitboxColor Color of the hitbox outline
             */
            void defaultAttributes(sf::Color hitboxColor);

            /**
             * @brief Get the Hitbox object
             * @return sf::RectangleShape& Reference to the hitbox
             */
            sf::RectangleShape &getHitbox();
            
            /**
             * @brief Set the color of the hitbox outline
             * @param color New color for the hitbox outline
             */
            void setHitboxColor(sf::Color color) const;
            
            /**
             * @brief Move the texture rectangle for animation
             * @param offsetX Horizontal offset to move the rectangle
             * @param delay Time in milliseconds between each frame
             * @param maxSize Maximum size of the texture, defaults to texture width if 0
             */
            void moveRect(int offsetX, int delay, int maxSize = 0);

            /**
             * @brief Get the Texture object
             * @return sf::Texture& Reference to the texture
             */
            sf::Texture &getTexture();
            
            /**
             * @brief Get the size of the texture
             * @return sf::Vector2u Size of the texture
             */
            sf::Vector2u getTextureSize() const;

            /**
             * @brief Get the Sprite object
             * @return sf::Sprite& Reference to the sprite
             */
            sf::Sprite &getSprite();
            
            /**
             * @brief Set the texture rectangle by reference
             * @param rect New texture rectangle
             */
            void setRect(sf::IntRect &rect);
            
            /**
             * @brief Set the texture rectangle by value
             * @param rect New texture rectangle
             */
            void setRect(sf::IntRect rect);
            
            /**
             * @brief Get the current texture rectangle
             * @return const sf::IntRect& Reference to the current texture rectangle
             */
            const sf::IntRect &getRect() const;

            /**
             * @brief Get the current position
             * @return const sf::Vector2f& Reference to the position vector
             */
            const sf::Vector2f &getPosition(void) const;
            
            /**
             * @brief Set the position of the object
             * @param pos New position vector
             */
            void setPosition(sf::Vector2f pos);

            /**
             * @brief Set the scale of the object
             * @param scale New scale vector
             */
            void setScale(sf::Vector2f scale);
            
            /**
             * @brief Get the current scale
             * @return const sf::Vector2f& Reference to the scale vector
             */
            const sf::Vector2f &getScale(void) const;

            /**
             * @brief Get the default sprite color
             * @return sf::Color& Reference to the default color
             */
            sf::Color &getDefaultColor(void);



        private:
            std::string _path; ///< Path to the texture file

            std::shared_ptr<sf::Texture> _texture; ///< Shared pointer to the texture
            std::shared_ptr<sf::Sprite> _sprite; ///< Shared pointer to the sprite
            std::shared_ptr<sf::RectangleShape> _hitbox; ///< Shared pointer to the hitbox

            sf::IntRect _textureRect; ///< Texture rectangle for animation
            sf::Vector2f _position; ///< Position of the object
            sf::Vector2f _scale; ///< Scale of the object
            sf::Color _defaultSpriteColor; ///< Default color of the sprite

            std::chrono::steady_clock::time_point _spriteClock; ///< Clock for sprite animation
    };
}



#endif // OBJECT_HPP
