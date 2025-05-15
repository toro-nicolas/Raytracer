/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Translation class declaration
*/
/**
 * @file Translation.hpp
 * @brief The Translation class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef PLANE_HPP
    #define PLANE_HPP

    #include "ATransformation.hpp"
    #include "ATransformationBuilder.hpp"

namespace Raytracer {
    /**
     * @class Translation
     * @brief Represents a translation transformation in 3D space
     */
    class Translation final : public ATransformation {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Translation object
             */
            Translation();

            /**
             * @brief Destroy the Translation object
             */
            ~Translation() final;

            /**
             * @brief Get the builder of the transformation
             * @return A reference to a unique pointer to the transformation builder
             */
            std::unique_ptr<ITransformationBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the transformation
             */
            void display(void) final;



        protected:

        private:
    };



    /**
     * @class TranslationBuilder
     * @brief Builder for the Translation transformation
     */
    class TranslationBuilder final : public ATransformationBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the TranslationBuilder
             * @param plane Reference to a Translation to be configured
             */
            TranslationBuilder(Translation &plane);

            /**
             * @brief Destructor of the TranslationBuilder
             */
            ~TranslationBuilder() final;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the transformation
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the transformation builder being configured
             */
            ITransformationBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Translation &_translation; ///< Reference to the translation being configured
    };



    /**
     * @brief Create a new Translation object
     * @return std::shared_ptr<Translation> A shared pointer to the created Translation object
     */
    extern "C" std::shared_ptr<Translation> createTransformation(void);
}

#endif // PLANE_HPP