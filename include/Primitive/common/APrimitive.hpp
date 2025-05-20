/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The APrimitive class declaration
*/
/**
 * @file APrimitive.hpp
 * @brief The APrimitive class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef APRIMITIVE_HPP
    #define APRIMITIVE_HPP

    #include "IPrimitive.hpp"

namespace Raytracer {
    /**
     * @class APrimitive
     * @brief Abstract base class for all primitives in the raytracer
     */
    class APrimitive : public IPrimitive {
        public:
            /* Display function */

            /**
             * @brief Display the primitive
             */
            void display(size_t level) override;



            /* Position functions */

            /**
             * @brief Get the position of the primitive
             * @return A reference to the position of the primitive
             */
            Lib::Vector3 &getPos(void) override;

            /**
             * @brief Get the position of the primitive (const version)
             * @return A const reference to the position of the primitive
             */
            const Lib::Vector3 &getPos(void) const override;

            /**
             * @brief Set the position of the primitive
             * @param pos The new position of the primitive
             */
            void setPos(const Lib::Vector3 &pos) override;



            /* Material functions */

            /**
             * @brief Get the material of the primitive
             * @return A reference to the material of the primitive
             */
            std::vector<std::pair<std::string, std::shared_ptr<IMaterial>>> &getMaterials(void) override;

            /**
             * @brief Get the material of the primitive (const version)
             * @return A const reference to the material of the primitive
             */
            const std::vector<std::pair<std::string, std::shared_ptr<IMaterial>>> &getMaterials(void) const override;

            /**
             * @brief Set the material of the primitive
             * @param name The name of the material
             * @param material A reference to the material to set
             */
            void setMaterial(const std::string &name, std::shared_ptr<IMaterial> &material) override;



            /* Transformation functions */

            /**
             * @brief Get the transformation of the primitive
             * @return A reference to the transformation of the primitive
             */
            std::vector<std::pair<std::string, std::shared_ptr<ITransformation>>> &getTransformations(void) override;

            /**
             * @brief Get the transformation of the primitive (const version)
             * @return A const reference to the transformation of the primitive
             */
            const std::vector<std::pair<std::string, std::shared_ptr<ITransformation>>> &getTransformations(void) const override;

            /**
             * @brief Set the transformation of the primitive
             * @param name The name of the transformation
             * @param transformation A reference to the transformation to set
             */
            void setTransformation(const std::string &name, std::shared_ptr<ITransformation> &transformation) override;



            /* Rendering function */

            /**
             * @brief Check if the ray intersects with the primitive
             * @param ray The ray to check
             * @param ray_t The interval of the ray
             * @param rec The intersection record
             * @return true if the ray intersects, false otherwise
             */
            bool hit(const Ray& ray, Interval ray_t, Intersection& rec) const override;

            /**
             * @brief Get the bounding box of the primitive
             * @return A reference to the bounding box of the primitive
             */
            AABB &boundingBox() override;

            /**
             * @brief Get the bounding box of the primitive (const version)
             * @return A const reference to the bounding box of the primitive
             */
            const AABB &boundingBox() const override;



            /* Child functions */

            /**
             * @brief Get the children of the primitive
             * @return A reference to the children of the primitive
             */
            std::vector<std::shared_ptr<IPrimitive>> getChildren(void) override;



            /* Initialization function */

            /**
             * @brief Initialize the primitive
             * @details This function initializes the primitive and its children
             */
            void init(void) override;



        protected:
            std::unique_ptr<IPrimitiveBuilder> _builder; ///< Pointer to the primitive builder
            Lib::Vector3 _pos; ///< The position of the primitive
            std::vector<std::pair<std::string, std::shared_ptr<IMaterial>>> _materials; ///< The materials of the primitive
            std::vector<std::pair<std::string, std::shared_ptr<ITransformation>>> _transformations; ///< The transformations of the primitive
            AABB _bbox; ///< Axis-aligned bounding box of the primitive
    };
}

#endif // APRIMITIVE_HPP