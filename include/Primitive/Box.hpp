/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Box class declaration
*/
/**
 * @file Box.hpp
 * @brief The Box class declaration
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#ifndef BOX_HPP
    #define BOX_HPP

    #include "APrimitive.hpp"
    #include "APrimitiveBuilder.hpp"

namespace Raytracer {
    /**
     * @class BoxPlane
     * @brief Represents a box primitive in 3D space
     */
    class BoxPlane final : public APrimitive {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Plane object
             */
            BoxPlane();

            /**
             * @brief Destroy the BoxPlane object
             */
            ~BoxPlane() final;

            /**
             * @brief Get the builder of the primitive
             * @return A reference to a unique pointer to the primitive builder
             */
            std::unique_ptr<IPrimitiveBuilder> &getBuilder(void) final;



            /* Getter functions */

            /**
             * @brief Get the first side of the box
             * @return Reference to the first side vector
             */
            Lib::Vector3 &getFirstSide(void);

            /**
             * @brief Get the second side of the box
             * @return Reference to the second side vector
             */
            Lib::Vector3 &getSecondSide(void);



            /* Display function */

            /**
             * @brief Display the primitive
             */
            void display(size_t level) final;



            /* Rendering function */

            /**
             * @brief Set the bounding box of the primitive
             */
            void setBoundingBox();

            /**
             * @brief Check if the ray intersects with the primitive
             * @param ray The ray to check
             * @param ray_t The interval of the ray
             * @param rec The intersection record
             * @return true if the ray intersects, false otherwise
             */
            bool hit(const Ray &r, Interval ray_t, Intersection &rec) const override;

            /**
             * @brief Check if the intersection point is inside the box
             * @param a The first side of the box
             * @param b The second side of the box
             * @param rec The intersection record
             * @return true if the point is inside, false otherwise
             */
            bool isInterior(double a, double b, Intersection& rec) const;



            /* Initialization function */

            /**
             * @brief Initialize the box properties
             */
            void init(void) final;



        private:
            Lib::Vector3 _u, _v; ///< The u and v vectors of the BoxPlane (first and second side)
            Lib::Vector3 _w; ///< The w vector of the BoxPlane
            Lib::Vector3 _normal; ///< The normal vector of the BoxPlane
            double D; ///< The distance from the origin to the BoxPlane
    };



    /**
     * @class BoxPlaneBuilder
     * @brief Builder for the BoxPlane primitive
     */
    class BoxPlaneBuilder : public APrimitiveBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the BoxPlaneBuilder
             * @param boxPlane Reference to a BoxPlane to be configured
             */
            BoxPlaneBuilder(BoxPlane &boxPlane);

            /**
             * @brief Destructor of the BoxPlaneBuilder
             */
            ~BoxPlaneBuilder();



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the BoxPlaneBuilder being configured
             */
            IPrimitiveBuilder &set(const std::string &name, const std::vector<std::string> &args) override;



        private:
            BoxPlane &_boxPlane; ///< The BoxPlane being built
    };



    /**
     * @class Box
     * @brief Represents a box primitive in 3D space
     */
    class Box : public APrimitive {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new Box object
             */
            Box();

            /**
             * @brief Destroy the Box object
             */
            ~Box();

            /**
             * @brief Get the builder of the box
             * @return A reference to a unique pointer to the box builder
             */
            std::unique_ptr<IPrimitiveBuilder> &getBuilder(void) final;



            /* Getter functions */

            /**
             * @brief Get the maximum point of the box
             * @return Reference to the maximum point vector
             */
           const Lib::Vector3 &getMax(void) const;

            /**
             * @brief Get the maximum point of the box
             * @return Reference to the maximum point vector
             */
            Lib::Vector3 &getMax(void);

            /**
             * @brief Get the planes of the box
             * @return Reference to the planes vector
             */
            std::vector<std::shared_ptr<BoxPlane>> &getPlanes(void);

            /**
             * @brief Get the planes of the box (const version)
             * @return Const reference to the planes vector
             */
            const std::vector<std::shared_ptr<BoxPlane>> &getPlanes(void) const;



            /* Display function */

            /**
             * @brief Display the box
             */
            void display(size_t level) final;



            /* Rendering function */

            /**
             * @brief Get the bounding box of the primitive
             * @return A reference to the bounding box of the primitive
             */
            bool hit(const Ray &r, Interval ray_t, Intersection &rec) const override;

            /**
             * @brief Create the planes of the box
             */
            void createPlanes();



            /* Child functions */

            /**
             * @brief Get the children of the box
             * @return A reference to the children of the box
             */
            std::vector<std::shared_ptr<IPrimitive>> getChildren(void) override;



            /* Initialization function */

            /**
             * @brief Initialize the box
             */
            void init(void) final;



        private:
            Lib::Vector3 _max; ///< The maximum point of the box
            std::vector<std::shared_ptr<BoxPlane>> _planes; ///< The planes of the box
    };



    /**
     * @class BoxBuilder
     * @brief Builder for the Box primitive
     */
    class BoxBuilder : public APrimitiveBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the BoxBuilder
             * @param box Reference to a Box to be configured
             */
            BoxBuilder(Box &box);

            /**
             * @brief Destructor of the BoxBuilder
             */
            ~BoxBuilder();



            /* Setters of the properties */

            /**
             * @brief Set a material of the primitive
             * @param name The name of the material
             * @param material The material to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &setMaterial(const std::string &name, std::shared_ptr<IMaterial> &material) override;

            /**
             * @brief Set a transformation of the primitive
             * @param name The name of the transformation
             * @param transformation The transformation to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &setTransformation(const std::string &name, std::shared_ptr<ITransformation> &transformation) override;

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the BoxBuilder being configured
             */
            IPrimitiveBuilder &set(const std::string &name, const std::vector<std::string> &args) override;



        private:
            Box &_box; ///< The box being built
    };



    /**
     * @brief Create a Box object
     * @return std::shared_ptr<Box> A shared pointer to the created Box object
     */
    extern "C" std::shared_ptr<Box> createPrimitive(void);
}



#endif // BOX_HPP