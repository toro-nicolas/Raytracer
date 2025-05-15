/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Cone class declaration
*/

/**
 * @file Cone.hpp
 * @brief The Cone class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef CONE_HPP
    #define CONE_HPP

    #include "APrimitive.hpp"
    #include "APrimitiveBuilder.hpp"

namespace Raytracer {
    /**
     * @class Cone
     * @brief Represents a cone primitive in 3D space
     */
    class Cone final : public APrimitive {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Cone object
             */
            Cone();

            /**
             * @brief Destroy the Cone object
             */
            ~Cone() final;

            /**
             * @brief Get the builder of the primitive
             * @return A reference to a unique pointer to the primitive builder
             */
            std::unique_ptr<IPrimitiveBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the primitive
             * @return <b>void</b>
             */
            void display(void) final;



        protected:

        private:
    };



    /**
     * @class ConeBuilder
     * @brief Builder for the Cone primitive
     */
    class ConeBuilder final : public APrimitiveBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the ConeBuilder
             * @param cone Reference to a Cone to be configured
             */
            ConeBuilder(Cone &cone);

            /**
             * @brief Destructor of the ConeBuilder
             */
            ~ConeBuilder() final;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Cone &_cone; ///< Reference to the cone being configured
    };



    /**
     * @brief Create a new Cone object
     * @return std::shared_ptr<Cone> A shared pointer to the new Cone object
     */
    extern "C" std::shared_ptr<Cone> createPrimitive(void);
}

#endif // CONE_HPP