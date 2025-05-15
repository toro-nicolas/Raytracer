/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Ambient class declaration
*/

/**
 * @file Ambient.hpp
 * @brief The Ambient class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef AMBIENT_HPP
    #define AMBIENT_HPP

    #include "ALight.hpp"
    #include "ALightBuilder.hpp"

namespace Raytracer {
    /**
     * @class Ambient
     * @brief Represents a ambient light in 3D space
     */
    class Ambient final : public ALight {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Ambient object
             */
            Ambient();

            /**
             * @brief Destroy the Ambient object
             */
            ~Ambient() final;

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

            LightType getType() const override {
                return LightType::AMBIENT;
            }



        protected:

        private:
    };



    /**
     * @class AmbientBuilder
     * @brief Builder for the Ambient light
     */
    class AmbientBuilder final : public ALightBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the AmbientBuilder
             * @param ambient Reference to a Ambient to be configured
             */
            AmbientBuilder(Ambient &ambient);

            /**
             * @brief Destructor of the AmbientBuilder
             */
            ~AmbientBuilder() final;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the light
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the ambient builder being configured
             */
            ILightBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Ambient &_ambient; ///< Reference to the ambient being configured
    };



    /**
     * @brief Create an Ambient object
     * @return std::shared_ptr<Ambient> A shared pointer to the created Ambient object
     */
    extern "C" std::shared_ptr<Ambient> createLight(void);
}

#endif // AMBIENT_HPP