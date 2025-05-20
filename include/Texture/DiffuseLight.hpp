/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The diffuse light class declaration
*/
/**
 * @file DiffuseLight.hpp
 * @brief The DiffuseLight class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef DIFFUSELIGHT_HPP
    #define DIFFUSELIGHT_HPP

    #include "AMaterial.hpp"
    #include "AMaterialBuilder.hpp"
    #include "SolidColor.hpp"
    #include "Texture.hpp"

namespace Raytracer {
    class DiffuseLightBuilder;

    /**
     * @class DiffuseLight
     * @brief Material that emits light
     */
    class DiffuseLight : public AMaterial {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a diffuse light with a texture
             * @param tex Texture to use for light emission
             */
            DiffuseLight(std::shared_ptr<Texture> tex);

            /**
             * @brief Construct a diffuse light with solid color
             * @param emit Color vector to emit
             */
            DiffuseLight(const Lib::Vector3& emit);

            /**
             * @brief Get the builder of the material
             * @return A reference to a unique pointer to the material builder
             */
            std::unique_ptr<IMaterialBuilder>& getBuilder() final;



            /* Getters and setters */

            /**
             * @brief Get emitted light at a point
             * @param u Texture u coordinate
             * @param v Texture v coordinate
             * @param p Point in 3D space
             * @return Lib::Vector3 Emitted color/light
             */
            Lib::Vector3 emitted(double u, double v, const Lib::Vector3& p) const override;

            /**
             * @brief Get the texture used by this light
             * @return Reference to the texture
             */
            [[nodiscard]] std::shared_ptr<Texture>& getTexture();



            /* Display function */

            /**
             * @brief Display the material information
             */
            void display(size_t level) final;



        private:
            Lib::Vector3 _color; ///< Color of the light
            std::shared_ptr<Texture> tex; ///< Texture used for light emission
        };



        /**
         * @brief Builder for DiffuseLight material
         */
        class DiffuseLightBuilder final : public AMaterialBuilder {
        public:
            /**
             * @brief Constructor of the DiffuseLightBuilder
             * @param diffuse Reference to DiffuseLight to be configured
             */
            DiffuseLightBuilder(DiffuseLight &diffuse);

            /**
             * @brief Destructor of the DiffuseLightBuilder
             */
            ~DiffuseLightBuilder() final;

            /**
             * @brief Set a specific property of the material
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the builder being configured
             */
            IMaterialBuilder& set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            DiffuseLight &_diffuse; ///< Reference to the material being configured
    };



    /**
     * @brief Create a DiffuseLight material
     * @return std::shared_ptr<DiffuseLight> A shared pointer to the created material
     */
    extern "C" std::shared_ptr<DiffuseLight> createMaterial();
}

#endif // DIFFUSELIGHT_HPP