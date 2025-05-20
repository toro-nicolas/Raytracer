/*
** EPITECH PROJECT, 2025
** IPrimitive.hpp
** File description:
** The IPrimitive class declaration
*/
/**
 * @file IPrimitive.hpp
 * @brief The IPrimitive class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef IPRIMITIVE_HPP
    #define IPRIMITIVE_HPP

    #include "Lib.hpp"
    #include "Ray.hpp"
    #include "IMaterial.hpp"
    #include "ITransformation.hpp"

namespace Raytracer {
    class IPrimitiveBuilder; ///< Forward declaration of the IPrimitiveBuilder class

    /**
     * @class IPrimitive
     * @brief Interface for all primitive shapes in the raytracer
     */
    class IPrimitive : public Hittable {
        public:
            /**
             * @brief Destructor of the IPrimitive
             */
            virtual ~IPrimitive() = default;

            /**
             * @brief Get the builder of the primitive
             * @return A reference to a unique pointer to the primitive builder
             */
            virtual std::unique_ptr<IPrimitiveBuilder> &getBuilder(void) = 0;



            /* Display function */

            /**
             * @brief Display the primitive
             * @param level Indentation level for display
             */
            virtual void display(size_t level) = 0;



            /* Position functions */

            /**
             * @brief Get the position of the primitive
             * @return A reference to the position of the primitive
             */
            virtual Lib::Vector3 &getPos(void) = 0;

            /**
             * @brief Get the position of the primitive (const version)
             * @return A const reference to the position of the primitive
             */
            virtual const Lib::Vector3 &getPos(void) const = 0;

            /**
             * @brief Set the position of the primitive
             * @param pos The new position of the primitive
             */
            virtual void setPos(const Lib::Vector3 &pos) = 0;



            /* Material functions */

            /**
             * @brief Get the materials of the primitive
             * @return A reference to the materials of the primitive
             */
            virtual std::vector<std::pair<std::string, std::shared_ptr<IMaterial>>> &getMaterials(void) = 0;

            /**
             * @brief Get the materials of the primitive (const version)
             * @return A const reference to the materials of the primitive
             */
            virtual const std::vector<std::pair<std::string, std::shared_ptr<IMaterial>>> &getMaterials(void) const = 0;

            /**
             * @brief Set a material for the primitive
             * @param name The name of the material
             * @param material A reference to the material to set
             */
            virtual void setMaterial(const std::string &name, std::shared_ptr<IMaterial> &material) = 0;



            /* Transformation functions */

            /**
             * @brief Get the transformations of the primitive
             * @return A reference to the transformations of the primitive
             */
            virtual std::vector<std::pair<std::string, std::shared_ptr<ITransformation>>> &getTransformations(void) = 0;

            /**
             * @brief Get the transformations of the primitive (const version)
             * @return A const reference to the transformations of the primitive
             */
            virtual const std::vector<std::pair<std::string, std::shared_ptr<ITransformation>>> &getTransformations(void) const = 0;

            /**
             * @brief Set a transformation for the primitive
             * @param name The name of the transformation
             * @param transformation A reference to the transformation to set
             */
            virtual void setTransformation(const std::string &name, std::shared_ptr<ITransformation> &transformation) = 0;



            /* Rendering function */

            /**
             * @brief Check if the ray intersects with the primitive
             * @param ray The ray to check
             * @param ray_t The interval of the ray
             * @param rec The intersection record
             * @return true if the ray intersects, false otherwise
             */
            virtual bool hit(const Ray& ray, Interval ray_t, Intersection& rec) const = 0;



            /* Child functions */

            /**
             * @brief Get the child primitives of this primitive
             * @return Vector of child primitives
             */
            virtual std::vector<std::shared_ptr<IPrimitive>> getChildren(void) = 0;



            /* Initialization function */

            /**
             * @brief Initialize the primitive
             */
            virtual void init(void) = 0;
    };
}

#endif /* IPRIMITIVE_HPP */