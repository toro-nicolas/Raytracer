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
            void display(void) final;

            // TODO: par ici
            LightType getType() const override {
                return LightType::DIRECTIONAL;
            }



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



        protected:

        private:
            Lib::Vector3 _direction; ///< The direction of the directional light
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