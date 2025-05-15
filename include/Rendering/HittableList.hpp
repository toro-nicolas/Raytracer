/*
** EPITECH PROJECT, 2025
** HittableList.hpp
** File description:
** HittableList declaration
*/


#ifndef HITTABLELIST_HPP
    #define HITTABLELIST_HPP
    #include "Ray.hpp"

namespace Raytracer {

    class HittableList : public Hittable {
        public:
            HittableList();
            ~HittableList() = default;
            HittableList(std::shared_ptr<Hittable> object);

            void clear();
            void add(std::shared_ptr<Hittable> object);

            bool hit(const Ray& ray, Interval ray_t, Intersection& rec) const override;

            const AABB& boundingBox() const override;
            AABB& boundingBox() override;

            std::vector<std::shared_ptr<Hittable>>& getObjects();

        private:
            std::vector<std::shared_ptr<Hittable>> _objects;
            AABB _worldBox;
    };
}

#endif // HITTABLELIST_HPP