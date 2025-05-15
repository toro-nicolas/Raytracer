/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Object class implementation
*/
/**
 * @file Object.cpp
 * @brief The Object class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Object.hpp"

namespace Graphics {
    Object::Object(const std::string& path, sf::Color hitboxColor)
    {
        _texture = std::make_shared<sf::Texture>(path);
        defaultAttributes(hitboxColor);
    }
    Object::Object(const std::shared_ptr<sf::Texture>& text, sf::Color hitboxColor)
    {
        _texture = text;
        defaultAttributes(hitboxColor);
    }

    void Object::defaultAttributes(sf::Color hitboxColor)
    {
        _sprite = std::make_shared<sf::Sprite>(*_texture);
        _textureRect = _sprite->getTextureRect();
        _hitbox = std::make_shared<sf::RectangleShape>(sf::Vector2f(_textureRect.size.x, _textureRect.size.y));
        _hitbox->setFillColor(sf::Color::Transparent);
        _hitbox->setOutlineColor(hitboxColor);
        _hitbox->setOutlineThickness(1);
        _position = {0, 0};
        _scale = {1, 1};
        _path = "";
        _spriteClock = std::chrono::steady_clock::now();
        _sprite->setPosition(_position);
        _hitbox->setPosition(_position);
        _hitbox->setSize({_sprite->getGlobalBounds().size.x, _sprite->getGlobalBounds().size.y});
        _defaultSpriteColor = _sprite->getColor();
    }

    sf::Texture &Object::getTexture()
    {
        return *_texture;
    }

    sf::Sprite &Object::getSprite()
    {
        return *_sprite;
    }

    sf::RectangleShape& Object::getHitbox()
    {
        return *_hitbox;
    }

    void Object::setHitboxColor(const sf::Color color) const
    {
        _hitbox->setOutlineColor(color);
    }

    void Object::moveRect(const int offsetX, const int delay, int maxSize)
    {
        auto now = std::chrono::steady_clock::now();

        if (maxSize == 0)
            maxSize = _texture->getSize().x;
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _spriteClock).count() > delay) {
            _textureRect.position.x = (_textureRect.position.x + offsetX) % maxSize;
            _sprite->setTextureRect(_textureRect);
            _spriteClock = now;
        }
    }

    void Object::setRect(sf::IntRect &rect)
    {
        _textureRect = rect;
        _sprite->setTextureRect(_textureRect);
    }
    void Object::setRect(sf::IntRect rect)
    {
        _textureRect = rect;
        _sprite->setTextureRect(_textureRect);
    }
    const sf::IntRect &Object::getRect() const
    {
        return _textureRect;
    }

    sf::Vector2u Object::getTextureSize() const
    {
        return _texture->getSize();
    }

    void Object::setPosition(sf::Vector2f pos)
    {
        _position = pos;
        _sprite->setPosition(_position);
        _hitbox->setPosition(_position);
    }

    const sf::Vector2f& Object::getPosition(void) const
    {
        return _position;
    }

    void Object::setScale(sf::Vector2f scale)
    {
        _scale = scale;
        _sprite->setScale(_scale);
        _hitbox->setSize({_sprite->getGlobalBounds().size.x, _sprite->getGlobalBounds().size.y});
    }

    const sf::Vector2f& Object::getScale(void) const
    {
        return _scale;
    }

    sf::Color& Object::getDefaultColor(void)
    {
        return _defaultSpriteColor;
    }
}