/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The box class implementation
*/
/**
 * @file Box.cpp
 * @brief The box class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Box.hpp"

namespace Raytracer {
    BoxPlane::BoxPlane()
    {
        // DEBUG << "BoxPlane constructor";
        _u = Lib::Vector3(0, 0, 0);
        _v = Lib::Vector3(0, 0, 0);
    }

    BoxPlane::~BoxPlane()
    {
        // DEBUG << "BoxPlane destructor";
    }

    std::unique_ptr<IPrimitiveBuilder> &BoxPlane::getBuilder(void)
    {
        // DEBUG << "BoxPlane getBuilder";
        if (!_builder)
            _builder = std::make_unique<BoxPlaneBuilder>(*this);
        return _builder;
    }

    Lib::Vector3 &BoxPlane::getFirstSide(void)
    {
        return _u;
    }
    Lib::Vector3 &BoxPlane::getSecondSide(void)
    {
        return _v;
    }

    void BoxPlane::display(size_t level)
    {
        std::string indent = std::string(level * 4, ' ');
        std::cout << "BoxPlane data:" << std::endl;
        std::cout << indent << "- Position: " << _pos << std::endl;
        std::cout << indent << "- Materials: (" << _materials.size() << ")" << std::endl;
        for (const auto &pair: _materials) {
            std::cout << indent << "    - ";
            pair.second->display(level + 2);
        }
        if (_materials.empty())
            std::cout << indent << "    No materials" << std::endl;
        std::cout << indent << "- Transformations: (" << _transformations.size() << ")" << std::endl;
        for (const auto &pair: _transformations) {
            std::cout << indent << "    - ";// << pair.first << ": ";
            pair.second->display(level + 2);
        }
        if (_transformations.empty())
            std::cout << indent << "    No transformations" << std::endl;
        std::cout << indent << "- First side: " << _u << std::endl;
        std::cout << indent << "- Second side: " << _v << std::endl;
        std::cout << indent << "- Normal: " << _normal << std::endl;
        std::cout << indent << "- D: " << D << std::endl;
    }

    void BoxPlane::setBoundingBox()
    {
        auto n = cross(_u, _v);
        _normal = unit_vector(n);
        D = dot(_normal, _pos);
        _w = n / dot(n,n);

        auto bbox_diagonal1 = AABB(_pos, _pos + _u + _v);
        auto bbox_diagonal2 = AABB(_pos + _u, _pos + _v);
        _bbox = AABB(bbox_diagonal1, bbox_diagonal2);

        for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
            const auto& [type, transfo] = *it;
            transfo->newBoundingBox(_bbox);
        }
    }

    bool BoxPlane::hit(const Ray& ray, Interval rayT, Intersection& rec) const
    {
        Ray transformed_ray = ray;
        for (const auto &[type, transfo] : _transformations) {
                transfo->compute(transformed_ray);
        }
        auto denom = dot(_normal, transformed_ray.direction());
        if (std::fabs(denom) < 1e-8)
            return false;

        auto t = (D - dot(_normal, transformed_ray.origin())) / denom;
        if (!rayT.contains(t))
            return false;

        auto intersection = transformed_ray.pointAt(t);
        Lib::Vector3 planar_hitpt_vector = intersection - _pos;
        auto alpha = dot(_w, cross(planar_hitpt_vector, _v));
        auto beta = dot(_w, cross(_u, planar_hitpt_vector));
        if (!isInterior(alpha, beta, rec))
            return false;

        rec.t = t;
        rec.p = intersection;
        rec.material = _materials;
        rec.setFaceNormal(transformed_ray, _normal);

        for (auto it = _transformations.rbegin(); it != _transformations.rend(); ++it) {
            const auto& [type, transfo] = *it;
            transfo->decompute(rec);
        }
        return true;
    }

    bool BoxPlane::isInterior(double a, double b, Intersection& rec) const
    {
        Interval unit_interval = Interval(0, 1);
        // Given the hit point in BoxPlane coordinates, return false if it is outside the
        // primitive, otherwise set the hit record UV coordinates and return true.
        if (!unit_interval.contains(a) || !unit_interval.contains(b))
            return false;

        rec.u = a;
        rec.v = b;
        return true;
    }

    void BoxPlane::init(void)
    {
        // DEBUG << "BoxPlane init";
        setBoundingBox();
    }
};

namespace Raytracer {

    BoxPlaneBuilder::BoxPlaneBuilder(BoxPlane &boxPlane) : APrimitiveBuilder(boxPlane), _boxPlane(boxPlane)
    {
        // DEBUG << "PlaneBuilder constructor";
    }

    BoxPlaneBuilder::~BoxPlaneBuilder()
    {
        // DEBUG << "BoxPlaneBuilder destructor";
    }

    IPrimitiveBuilder &BoxPlaneBuilder::set(const std::string &name, UNUSED const std::vector<std::string> &args)
    {
        DEBUG << "BoxPlaneBuilder set " << name;
        if (name == "direction") {
            if (args.size() != 6)
                return *this;
            // first side
            float xu = std::stof(args[0]);
            float yu = std::stof(args[1]);
            float zu = std::stof(args[2]);
            // second side
            float xv = std::stof(args[3]);
            float yv = std::stof(args[4]);
            float zv = std::stof(args[5]);
            _boxPlane.getFirstSide() = Lib::Vector3(xu, yu, zu);
            _boxPlane.getSecondSide() = Lib::Vector3(xv, yv, zv);
            _boxPlane.setBoundingBox();
        }
        return *this;
    }
}


namespace Raytracer {
    Box::Box()
    {
        // DEBUG << "Box constructor";
        _max = Lib::Vector3(0, 0, 0);
        _planes.reserve(6);
    }
    Box::~Box()
    {
        // DEBUG << "Box destructor";
    }
    std::unique_ptr<IPrimitiveBuilder> &Box::getBuilder(void)
    {
        // DEBUG << "Box getBuilder";
        if (!_builder)
            _builder = std::make_unique<BoxBuilder>(*this);
        return _builder;
    }
    const Lib::Vector3 &Box::getMax(void) const
    {
        return _max;
    }
    Lib::Vector3 &Box::getMax(void)
    {
        return _max;
    }

    std::vector<std::shared_ptr<BoxPlane>> &Box::getPlanes(void)
    {
        return _planes;
    }
    const std::vector<std::shared_ptr<BoxPlane>> &Box::getPlanes(void) const
    {
        return _planes;
    }

    bool Box::hit(UNUSED const Ray &r, UNUSED Interval ray_t, UNUSED Intersection &rec) const
    {
        // bool hit = false;
        // for (const auto &plane : _planes) {
        //     if (plane->hit(r, ray_t, rec)) {
        //         return true;
        //     }
        // }
        return false;
    }

    void Box::createPlanes()
    {
        // Create 6 planes for the box
        _planes.clear();
        auto min = Lib::Vector3(std::fmin(_pos.x, _max.x), std::fmin(_pos.y, _max.y), std::fmin(_pos.z, _max.z));
        auto max = Lib::Vector3(std::fmax(_pos.x, _max.x), std::fmax(_pos.y, _max.y), std::fmax(_pos.z, _max.z));

        auto dx = Vector3(max.x - min.x, 0, 0);
        auto dy = Vector3(0, max.y - min.y, 0);
        auto dz = Vector3(0, 0, max.z - min.z);

        // front
        _planes.push_back(std::make_shared<BoxPlane>());
        _planes.back()->getPos() = Lib::Vector3(min.x, min.y, max.z);
        _planes.back()->getFirstSide() = dx;
        _planes.back()->getSecondSide() = dy;

        // right
        _planes.push_back(std::make_shared<BoxPlane>());
        _planes.back()->getPos() = Lib::Vector3(max.x, min.y, max.z);
        _planes.back()->getFirstSide() = -dz;
        _planes.back()->getSecondSide() = dy;

        // back
        _planes.push_back(std::make_shared<BoxPlane>());
        _planes.back()->getPos() = Lib::Vector3(max.x, min.y, min.z);
        _planes.back()->getFirstSide() = -dx;
        _planes.back()->getSecondSide() = dy;

        // left
        _planes.push_back(std::make_shared<BoxPlane>());
        _planes.back()->getPos() = Lib::Vector3(min.x, min.y, min.z);
        _planes.back()->getFirstSide() = dz;
        _planes.back()->getSecondSide() = dy;

        // top -
        _planes.push_back(std::make_shared<BoxPlane>());
        _planes.back()->getPos() = Lib::Vector3(min.x, max.y, max.z);
        _planes.back()->getFirstSide() = dx;
        _planes.back()->getSecondSide() = -dz;

        // bottom
        _planes.push_back(std::make_shared<BoxPlane>());
        _planes.back()->getPos() = Lib::Vector3(min.x, min.y, min.z);
        _planes.back()->getFirstSide() = dx;
        _planes.back()->getSecondSide() = dz;
    }

    void Box::display(size_t level)
    {
        std::string indent = std::string(level * 4, ' ');
        std::cout << "Box data:" << std::endl;
        std::cout << indent << "- Position: " << _pos << std::endl;
        std::cout << indent << "- Materials: (" << _materials.size() << ")" << std::endl;
        for (const auto &pair: _materials) {
            std::cout << indent << "    - ";// << pair.first << ": ";
            pair.second->display(level + 2);
        }
        if (_materials.empty())
            std::cout << indent << "    No materials" << std::endl;
        std::cout << indent << "- Transformations: (" << _transformations.size() << ")" << std::endl;
        for (const auto &pair: _transformations) {
            std::cout << indent << "    - ";// << pair.first << ": ";
            pair.second->display(level + 2);
        }
        if (_transformations.empty())
            std::cout << indent << "    No transformations" << std::endl;
        std::cout << indent << "- Max: " << _max << std::endl;
        std::cout << indent << "- Planes: (" << _planes.size() << ")" << std::endl;
        for (const auto &plane : _planes) {
            std::cout << indent << "    - ";
            plane->display(level + 2);
        }
    }

    std::vector<std::shared_ptr<IPrimitive>> Box::getChildren(void)
    {
        std::vector<std::shared_ptr<IPrimitive>> converted;

        for (const auto& plane : _planes) {
            converted.push_back(std::dynamic_pointer_cast<IPrimitive>(plane));
        }
        return converted;
    }

    void Box::init(void)
    {
        // Initialize the box's planes
        for (const auto &plane : _planes) {
            plane->init();
        }
    }

    extern "C" std::shared_ptr<Box> createPrimitive(void)
    {
        auto box = std::make_shared<Box>();
        return box;
    }
}

namespace Raytracer {

    BoxBuilder::BoxBuilder(Box &box) : APrimitiveBuilder(box), _box(box)
    {
        // DEBUG << "BoxBuilder constructor";
    }

    BoxBuilder::~BoxBuilder()
    {
        // DEBUG << "BoxBuilder destructor";
    }

    IPrimitiveBuilder &BoxBuilder::setMaterial(const std::string &name, std::shared_ptr<IMaterial> &material)
    {
        _box.setMaterial(name, material);
        for (const auto &plane : _box.getPlanes())
            plane->setMaterial(name, material);
        return *this;
    };

    IPrimitiveBuilder &BoxBuilder::setTransformation(const std::string &name, std::shared_ptr<ITransformation> &transfo)
    {
        _box.setTransformation(name, transfo);
        for (const auto &plane : _box.getPlanes())
            plane->setTransformation(name, transfo);
        return *this;
    };



    IPrimitiveBuilder &BoxBuilder::set(const std::string &name, const std::vector<std::string> &args)
    {
        DEBUG << "BoxBuilder set " << name;
        if (name == "size") {
            if (args.size() != 3)
                return *this;
            float x = std::stof(args[0]);
            float y = std::stof(args[1]);
            float z = std::stof(args[2]);
            _box.getMax() = Lib::Vector3(x, y, z);
            _box.createPlanes();
        }
        else {
            DEBUG << "BoxBuilder set: unknown property " << name;
        }
        return *this;
    }

}