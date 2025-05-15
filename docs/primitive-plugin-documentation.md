# Primitive Plugins Documentation for Raytracer

## Introduction

This document explains how to create material plugins for the raytracer.  
Our raytracer system is designed with a modular architecture where the core and rendering components are in the main binary,  
while primitive are dynamically loaded from shared libraries (.so).



## Naming Conventions

Each primitive plugin must follow this naming convention:
```
raytrace_primitive_[primitive_name].so
```
For example, for a sphere: `raytrace_primitive_sphere.so`



## Plugin Architecture

To create a new primitive plugin, you need to implement two main classes:
1. A primitive class that inherits from `APrimitive`
2. A builder class for this primitive that inherits from `APrimitiveBuilder`

### Class Hierarchy

```
IPrimitive (Interface)
└── APrimitive (Abstract class)
    └── YourPrimitive (Concrete implementation)

IPrimitiveBuilder (Interface)
└── APrimitiveBuilder (Abstract class)
    └── YourPrimitiveBuilder (Concrete implementation)
```

## Creating a New Primitive

### 1. Primitive Class

Your primitive class must inherit from `APrimitive` and implement all required virtual methods.  
Example:
```cpp
namespace Raytracer {
    /**
     * @class YourPrimitive
     * @brief Represents a YourPrimitive primitive in 3D space
     */
    class YourPrimitive final : public APrimitive {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new YourPrimitive object
             */
            YourPrimitive();

            /**
             * @brief Destroy the YourPrimitive object
             */
            ~YourPrimitive() final;

            /**
             * @brief Get the builder of the primitive
             * @return A reference to a unique pointer to the primitive builder
             */
            std::unique_ptr<IPrimitiveBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the primitive
             */
            void display(void) final;



            /* Intersection function */

            /**
             * @brief Calculate the intersection of the plane with a ray
             * @param ray The ray to intersect with the plane
             * @return The intersection result
             */
            Intersection intersect(const Ray& ray) const override;



        protected:

        private:
    };
}
```


### 2. Builder Class

Your builder class must inherit from `APrimitiveBuilder` and implement the necessary methods to configure your primitive.  
Example:

```cpp
namespace Raytracer {
     /**
     * @class YourPrimitiveBuilder
     * @brief Builder for the YourPrimitive primitive
     */
    class YourPrimitiveBuilder final : public APrimitiveBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the YourPrimitiveBuilder
             * @param plane Reference to a YourPrimitive to be configured
             */
            YourPrimitiveBuilder(YourPrimitive &yourPrimitive);

            /**
             * @brief Destructor of the YourPrimitiveBuilder
             */
            ~PYourPrimitiveBuilder() final;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the primitive
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the primitive builder being configured
             */
            IPrimitiveBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            YourPrimitive &_yourPrimitive; ///< Reference to the plane being configured
    };
}
```


### 3. Export Function

Each plugin must export a creation function named `createPrimitive` with the following signature:
```cpp
/**
 * @brief Create a new YourPrimitive object
 * @return std::shared_ptr<YourPrimitive> A shared pointer to the created YourPrimitive object
 */
extern "C" std::shared_ptr<YourPrimitive> createPrimitive(void);
```
This function will be called by the raytracer core to instantiate your primitive.



## Implementation Details

### The IPrimitive Class

This interface defines the basic functionalities that any primitive must implement:
- Position management (`getPos`, `setPos`)
- Material management (`getMaterials`, `setMaterial`)
- Transformation management (`getTransformations`, `setTransformation`)
- Ray intersection calculation (`intersect`)
- Access to the builder (`getBuilder`)
- Information display (`display`)


### The APrimitive Class

This abstract class implements common functionalities shared by all primitives:
- Storage and access to position (`_pos`)
- Storage and access to materials (`_materials`)
- Storage and access to transformations (`_transformations`)
- Base implementation of the `display` method

You must implement in your derived class:
- The `getBuilder()` method
- The `intersect()` method
- Properties and methods specific to your primitive


### The IPrimitiveBuilder Class

This interface defines the behavior of primitive builders:
- Position configuration (`setPos`)
- Material configuration (`setMaterial`)
- Transformation configuration (`setTransformation`)
- Configuration of properties specific to the primitive (`set`)


### The APrimitiveBuilder Class

This abstract class implements functionalities common to builders:
- Storage of a reference to the primitive being configured
- Implementation of methods to configure position, materials, and transformations

You must implement in your derived builder class:
- The `set()` method to handle properties specific to your primitive



## How to Compile a Plugin

To compile your primitive plugin as a shared library (.so), use this command:
```bash
g++ -std=c++20 -Wall -Wextra -Werror -fPIC -shared \
    -I./include/Material/common \
    -I./include/Transformation/common \
    -I./include/Primitive/common \
    -I./include/Primitive \
    -I./include/lib/my \
    -L./plugins -l:raytracer_primitive.so \
    -o plugins/raytracer_primitive_<name>.so \
    src/Primitive/<name>.cpp
```



## Plugin Loading

The raytracer core will automatically search for and load all `.so` files that follow the naming convention.  
For each plugin found, it will call the `createPrimitive()` function to instantiate the primitive.



## Summary of Steps to Create a New Plugin

1. Create a class that inherits from `APrimitive`
2. Implement all required virtual methods
3. Create a builder class that inherits from `APrimitiveBuilder`
4. Implement the `set()` method to configure specific properties
5. Export the `createPrimitive()` function
6. Compile as a shared library (.so) following the naming convention
