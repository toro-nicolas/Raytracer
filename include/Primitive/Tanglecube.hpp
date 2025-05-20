/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The TangleCube class declaration
*/
/**
 * @file TangleCube.hpp
 * @brief The TangleCube class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef TANGLECUBE_HPP
    #define TANGLECUBE_HPP

    #include "APrimitive.hpp"
    #include "APrimitiveBuilder.hpp"

namespace Raytracer {
    /**
     * @class TangleCube
     * @brief Represents a tangle cube primitive (Steiner surface) in 3D space
     */
    class TangleCube final : public APrimitive {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new TangleCube object
             */
            TangleCube();

            /**
             * @brief Destroy the TangleCube object
             */
            ~TangleCube() final;

            /**
             * @brief Get the builder of the tangle cube
             * @return A reference to a unique pointer to the tangle cube builder
             */
            std::unique_ptr<IPrimitiveBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the primitive
             */
            void display(size_t level) final;



            /* Getters and setters */

            /**
             * @brief Get the size of the tangle cube
             * @return float& Reference to the size value
             */
            float &getSize(void);

            /**
             * @brief Get the size of the tangle cube (const version)
             * @return const float& Const reference to the size value
             */
            const float &getSize(void) const;

            /**
             * @brief Set the size of the tangle cube
             * @param size The new size value
             */
            void setSize(const float &size);

            /**
             * @brief Get the power parameter of the tangle cube
             * @return float& Reference to the power value
             */
            float &getPower(void);

            /**
             * @brief Get the power parameter of the tangle cube (const version)
             * @return const float& Const reference to the power value
             */
            const float &getPower(void) const;

            /**
             * @brief Set the power parameter of the tangle cube
             * @param power The new power value
             */
            void setPower(const float &power);



            /* Rendering function */

            /**
             * @brief Check if the ray intersects with the tangle cube
             * @param ray The ray to check for intersection
             * @param rayT Valid interval for intersection
             * @param rec Intersection record to fill with details
             * @return true if the ray intersects with the tangle cube, false otherwise
             */
            bool hit(const Ray& ray, Interval rayT, Intersection& rec) const override;



            /* Initialization function */

            /**
             * @brief Initialize the tangle cube properties
             */
            void init(void) final;



        private:
            float _size;  ///< Size parameter controlling the overall scale of the tangle cube
            float _power; ///< Power parameter controlling the shape of the tangle cube (typically 4)



            /**
             * @brief Compute UV coordinates for a point on the tangle cube
             * @param p The point on the tangle cube surface
             * @param u Output u coordinate [0,1]
             * @param v Output v coordinate [0,1]
             */
            void getTangleCubeUV(const Lib::Vector3& p, double& u, double& v) const;

            /**
             * @brief Calculate the bounding box for the tangle cube
             */
            void setBoundingBox();
    };

    /**
     * @class TangleCubeBuilder
     * @brief Builder for the TangleCube primitive
     */
    class TangleCubeBuilder final : public APrimitiveBuilder {
        public:
            /**
             * @brief Constructor of the TangleCubeBuilder
             * @param tangleCube Reference to a TangleCube to be configured
             */
            TangleCubeBuilder(TangleCube &tangleCube);

            /**
             * @brief Destructor of the TangleCubeBuilder
             */
            ~TangleCubeBuilder() final;

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            TangleCube &_tangleCube; ///< Reference to the tangle cube being configured
    };



    /**
     * @brief Create a TangleCube object
     * @return std::shared_ptr<TangleCube> A shared pointer to the created TangleCube object
     */
    extern "C" std::shared_ptr<TangleCube> createPrimitive(void);
}

#endif // TANGLECUBE_HPP