/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Reflection class declaration
*/
/**
 * @file Reflection.hpp
 * @brief The Reflection class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef REFLECTION_HPP_
    #define REFLECTION_HPP_

    #include "AMaterial.hpp"
    #include "AMaterialBuilder.hpp"

namespace Raytracer {
    /**
     * @class Reflection
     * @brief Represents a color material for primitives
     */
    class Reflection final : public AMaterial {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Reflection object
             */
            Reflection();

            /**
             * @brief Destroy the Reflection object
             */
            ~Reflection() final;

            /**
             * @brief Get the builder of the reflection
             * @return A reference to a unique pointer to the reflection builder
             */
            std::unique_ptr<IMaterialBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the reflection
             * @return <b>void</b>
             */
            void display(void) override;



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
             * @brief Get the fuze value
             * @return <b>double &</b> The fuze value
             */
            double &getFuze(void);

            /**
             * @brief Get the fuze value (const version)
             * @return <b>const double&</b> The fuze value
             */
            const double &getFuze(void) const;

            /**
             * @brief Set the fuze value
             * @param fuze The new fuze value
             */
            void setFuze(double fuze);



        private:
            double _fuze = 0.0; ///< The fuze value
    };



    /**
     * @class ReflectionBuilder
     * @brief Builder for the Reflection material
     */
    class ReflectionBuilder final : public AMaterialBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the ReflectionBuilder
             * @param reflection Reference to a Reflection to be configured
             */
            ReflectionBuilder(Reflection &reflection);

            /**
             * @brief Destructor of the ReflectionBuilder
             */
            ~ReflectionBuilder() final;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the material
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the Reflection builder being configured
             */
            IMaterialBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Reflection &_reflection; ///< Reference to the material being configured
    };



    /**
     * @brief Create a Reflection object
     * @return std::shared_ptr<Reflection> A shared pointer to the created Reflection object
     */
    extern "C" std::shared_ptr<Reflection> createMaterial(void);
}

#endif /* REFLECTION_HPP_ */