/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Refraction class declaration
*/
/**
 * @file Refraction.hpp
 * @brief The Refraction class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef REFRACTION_HPP_
    #define REFRACTION_HPP_

    #include "AMaterial.hpp"
    #include "AMaterialBuilder.hpp"

namespace Raytracer {
    /**
     * @class Refraction
     * @brief Represents a color material for primitives
     */
    class Refraction final : public AMaterial {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Refraction object
             */
            Refraction();

            /**
             * @brief Destroy the Refraction object
             */
            ~Refraction() final;

            /**
             * @brief Get the builder of the refraction
             * @return A reference to a unique pointer to the refraction builder
             */
            std::unique_ptr<IMaterialBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the refraction
             * @return <b>void</b>
             */
            void display(size_t level) override;



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



            /* Calculation functions */

            /**
             * @brief Calculate the reflectance based on the cosine and refraction index
             * @param cosine The cosine of the angle
             * @param ref_idx The refraction index
             * @return double The reflectance value
             */
            static double reflectance(double cosine, double ref_idx);

        private:
            double _fuze = 0.0; ///< The fuze value
    };



    /**
     * @class RefractionBuilder
     * @brief Builder for the Refraction material
     */
    class RefractionBuilder final : public AMaterialBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the RefractionBuilder
             * @param refraction Reference to a Refraction to be configured
             */
            RefractionBuilder(Refraction &refraction);

            /**
             * @brief Destructor of the RefractionBuilder
             */
            ~RefractionBuilder() final;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the material
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the Refraction builder being configured
             */
            IMaterialBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            Refraction &_refraction; ///< Reference to the material being configured
    };



    /**
     * @brief Create a Refraction object
     * @return std::shared_ptr<Refraction> A shared pointer to the created Refraction object
     */
    extern "C" std::shared_ptr<Refraction> createMaterial(void);
}

#endif /* REFRACTION_HPP_ */