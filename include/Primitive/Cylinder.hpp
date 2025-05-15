/*
** EPITECH PROJECT, 2025
** Cylinder.hpp
** File description:
** The Cylinder class declaration
*/

/**
 * @file Cylinder.hpp
 * @brief The Cylinder class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef CYLINDER_HPP
    #define CYLINDER_HPP

    #include "APrimitive.hpp"
    #include "APrimitiveBuilder.hpp"

namespace Raytracer {
    /**
     * @class Cylinder
     * @brief Represents a cylinder primitive in 3D space
     */
    class Cylinder final : public APrimitive {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Cylinder object
             */
            Cylinder();

            /**
             * @brief Destroy the Cylinder object
             */
            ~Cylinder() final;

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
     * @class CylinderBuilder
     * @brief Builder for the Cylinder primitive
     */
    class CylinderBuilder final : public APrimitiveBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the CylinderBuilder
             * @param cylinder Reference to a Cylinder to be configured
             */
            CylinderBuilder(Cylinder &cylinder);

            /**
             * @brief Destructor of the CylinderBuilder
             */
            ~CylinderBuilder() final;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Cylinder &_cylinder; ///< Reference to the cylinder being configured
    };



    /**
     * @brief Create a new Cylinder object
     * @return std::shared_ptr<Cylinder> A shared pointer to the created Cylinder object
     */
    extern "C" std::shared_ptr<Cylinder> createPrimitive(void);
}

#endif // CYLINDER_HPP