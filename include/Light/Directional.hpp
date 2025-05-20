/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Directional class declaration
*/
/**
 * @file Directional.hpp
 * @brief The Directional class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef DIRECTIONAL_HPP
    #define DIRECTIONAL_HPP

    #include "ALight.hpp"
    #include "ALightBuilder.hpp"

namespace Raytracer {
    /**
     * @class Directional
     * @brief Represents a directional light in 3D space
     */
    class Directional final : public ALight {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Directional object
             */
            Directional();

            /**
             * @brief Destroy the Directional object
             */
            ~Directional() final;

            /**
             * @brief Get the builder of the light
             * @return A reference to a unique pointer to the light builder
             */
            std::unique_ptr<ILightBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the light
             */
            void display(size_t level) final;



            /* Getters and setters */

            /**
             * @brief Get the direction of the directional light
             * @return Reference to the direction vector
             */
            Lib::Vector3 &getDirection(void);

            /**
             * @brief Get the direction of the directional light (const version)
             * @return Const reference to the direction vector
             */
            const Lib::Vector3 &getDirection(void) const;

            /**
             * @brief Set the direction of the directional light
             * @param direction New direction vector
             */
            void setDirection(const Lib::Vector3 &direction);

            /**
             * @brief Get the color of the directional light
             * @return Reference to the color vector
             */
            Lib::Vector3 &getColor(void);

            /**
             * @brief Get the color of the directional light (const version)
             * @return Const reference to the color vector
             */
            const Lib::Vector3 &getColor(void) const;

            /**
             * @brief Set the color of the directional light
             * @param color_ New color vector
             */
            void setColor(const Lib::Vector3 &color_);



            /* Compute function */

            /**
             * @brief Compute the light contribution at a given point
             * @param point The point to compute the light contribution for
             * @param normal The normal vector at the point
             * @param view_dir The view direction vector
             * @return The computed light contribution
             */
            Lib::Vector3 compute(const Lib::Vector3& point, const Lib::Vector3& normal,
                                 const Lib::Vector3& view_dir) const final;



        protected:

        private:
            Lib::Vector3 _direction; ///< The direction of the directional light
            Lib::Vector3 _color; ///< The color of the directional light
    };



    /**
     * @class DirectionalBuilder
     * @brief Builder for the Directional light
     */
    class DirectionalBuilder final : public ALightBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the DirectionalBuilder
             * @param directional Reference to a Directional to be configured
             */
            DirectionalBuilder(Directional &directional);

            /**
             * @brief Destructor of the DirectionalBuilder
             */
            ~DirectionalBuilder() final;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the light
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the directional builder being configured
             */
            ILightBuilder &set(const std::string &name, const std::vector<std::string> &args) final;

            /**
             * @brief Set the direction of the directional light
             * @param direction The new direction vector
             * @return Reference to the directional builder being configured
             */
            ILightBuilder &setDirection(const Lib::Vector3 &direction);



        protected:
            Directional &_directional; ///< Reference to the directional being configured
    };



    /**
     * @brief Create a Directional object
     * @return std::shared_ptr<Directional> A shared pointer to the created Directional object
     */
    extern "C" std::shared_ptr<Directional> createLight(void);
}

#endif // DIRECTIONAL_HPP