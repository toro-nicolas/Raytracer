/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Color class declaration
*/
/**
 * @file Color.hpp
 * @brief The Color class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef COLOR_HPP
    #define COLOR_HPP

    #include "AMaterial.hpp"
    #include "AMaterialBuilder.hpp"
    #include "Texture.hpp"

namespace Raytracer {
    /**
     * @class Color
     * @brief Represents a color material for primitives
     */
    class Color final : public AMaterial {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Color object
             * @param r Red component value (0-255)
             * @param g Green component value (0-255)
             * @param b Blue component value (0-255)
             */
            Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0);

            Color(std::shared_ptr<Texture> texture);

            /**
             * @brief Destroy the Color object
             */
            ~Color() final;

            /**
             * @brief Get the builder of the material
             * @return A reference to a unique pointer to the material builder
             */
            std::unique_ptr<IMaterialBuilder> &getBuilder(void) final;

            /* Getters and setters */
            std::shared_ptr<Texture> &getTexture(void);



            /* Display function */

            /**
             * @brief Display the material
             */
            void display(void) final;



            /* Rendering function */

            /**
             * @brief Scatter the ray based on the material properties
             * @param r_in The incoming ray
             * @param rec The intersection record
             * @param attenuation The attenuation color
             * @param scattered The scattered ray
             * @return true if the ray is scattered, false otherwise
             */
            bool scatter(const Ray& r_in, const Intersection& rec, Lib::Vector3 &attenuation, Ray& scattered)
            const override final;



            /* Getters and setters */

            /**
             * @brief Get the color value
             * @return Lib::Vector3 The color value (RGB)
             */
            Lib::Vector3 &getColor(void);

            /**
             * @brief Get the color value (const version)
             * @return const Lib::Vector3 The color value (RGB)
             */
            const Lib::Vector3 &getColor(void) const;

            /**
             * @brief Set the color value
             * @param color The new color value (RGB)
             */
            void setColor(const Lib::Vector3 &color);



        private:
            Lib::Vector3 _color; ///< Color value (RGB)
            std::shared_ptr<Texture> _texture; ///< Texture for the color
            
    };




    /**
     * @class ColorBuilder
     * @brief Builder for the Color material
     */
    class ColorBuilder final : public AMaterialBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the ColorBuilder
             * @param color Reference to a Color to be configured
             */
            ColorBuilder(Color &color);

            /**
             * @brief Destructor of the ColorBuilder
             */
            ~ColorBuilder() final;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the material
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the Color builder being configured
             */
            IMaterialBuilder &set(const std::string &name, const std::vector<std::string> &args) final;

            IMaterialBuilder &setTexture(const std::string &texture_name, const std::vector<std::string> &args);

        protected:
            Color &_color; ///< Reference to the material being configured
    };



    /**
     * @brief Create a Color object
     * @return std::shared_ptr<Color> A shared pointer to the created Color object
     */
    extern "C" std::shared_ptr<Color> createMaterial(void);
}

#endif // COLOR_HPP