# Material Plugins Documentation for Raytracer

## Introduction

This document explains how to create material plugins for the raytracer.
Our raytracer system is designed with a modular architecture where the core and rendering components are in the main binary,
while materials are dynamically loaded from shared libraries (.so).



## Naming Conventions

Each material plugin must follow this naming convention:
```
raytrace_material_[material_name].so
```
For example, for a color material: `raytrace_material_color.so`



## Plugin Architecture

To create a new material plugin, you need to implement two main classes:
1. A material class that inherits from `AMaterial`
2. A builder class for this material that inherits from `AMaterialBuilder`



### Class Hierarchy

```
IMaterial (Interface)
└── AMaterial (Abstract class)
    └── YourMaterial (Concrete implementation)

IMaterialBuilder (Interface)
└── AMaterialBuilder (Abstract class)
    └── YourMaterialBuilder (Concrete implementation)
```



## Creating a New Material

### 1. Material Class

Your material class must inherit from `AMaterial` and implement all required virtual methods.
Example:
```cpp
namespace Raytracer {
    /**
     * @class YourMaterial
     * @brief Represents a YourMaterial material for primitives
     */
    class YourMaterial final : public AMaterial {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new YourMaterial object
             */
            YourMaterial();

            /**
             * @brief Destroy the YourMaterial object
             */
            ~YourMaterial() final;

            /**
             * @brief Get the builder of the material
             * @return A reference to a unique pointer to the material builder
             */
            std::unique_ptr<IMaterialBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the material
             */
            void display(size_t level) final;




            /* Methods specific to your material */



        protected:

        private:
            /* Properties specific to your material */
    };
}
```


### 2. Builder Class

Your builder class must inherit from `AMaterialBuilder` and implement the necessary methods to configure your material.
Example:
```cpp
namespace Raytracer {
    /**
     * @class YourMaterialBuilder
     * @brief Builder for the YourMaterial material
     */
    class YourMaterialBuilder final : public AMaterialBuilder {
        public:
            /* Constructors and destructors */

            /**
             * @brief Constructor of the YourMaterialBuilder
             * @param yourMaterial Reference to a YourMaterial to be configured
             */
            YourMaterialBuilder(YourMaterial &yourMaterial);

            /**
             * @brief Destructor of the YourMaterialBuilder
             */
            ~YourMaterialBuilder() final;



            /* Setters of the specific properties */

            /**
             * @brief Set the specific property of the material
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the YourMaterial builder being configured
             */
            IMaterialBuilder &set(const std::string &name, const std::vector<std::string> &args) final;



        protected:
            YourMaterial &_yourMaterial; ///< Reference to the material being configured
    };
}
```


### 3. Export Function

Each plugin must export a creation function named `createMaterial` with the following signature:
```cpp
/**
 * @brief Create a YourMaterial object
 * @return std::shared_ptr<YourMaterial> A shared pointer to the created YourMaterial object
 */
extern "C" std::shared_ptr<YourMaterial> createMaterial(void);
```
This function will be called by the raytracer core to instantiate your material.



## Implementation Details

### The IMaterial Class

This interface defines the basic functionalities that any material must implement:
- Access to the builder (`getBuilder`)
- Information display (`display`)


### The AMaterial Class

This abstract class implements common functionalities shared by all materials:
- Base implementation of the `display` method

You must implement in your derived class:
- The `getBuilder()` method
- Properties and methods specific to your material


### The IMaterialBuilder Class

This interface defines the behavior of material builders:
- Configuration of properties specific to the material (`set`)


### The AMaterialBuilder Class

This abstract class implements functionalities common to builders:
- Storage of a reference to the material being configured

You must implement in your derived builder class:
- The `set()` method to handle properties specific to your material



## How to Compile a Material Plugin

To compile your material plugin as a shared library (.so), use this command:
```bash
g++ -std=c++20 -Wall -Wextra -Werror -fPIC -shared \
    -I./include/Material/common \
    -I./include/Material \
    -I./include/lib/my \
    -L./plugins -l:raytracer_material.so \
    -o plugins/raytracer_material_<name>.so \
    src/Material/<name>.cpp
```



## Plugin Loading

The raytracer core will automatically search for and load all `.so` files that follow the naming convention.
For each plugin found, it will call the `createMaterial()` function to instantiate the material.



## Summary of Steps to Create a New Material Plugin

1. Create a class that inherits from `AMaterial`
2. Implement all required virtual methods
3. Create a builder class that inherits from `AMaterialBuilder`
4. Implement the `set()` method to configure specific properties
5. Export the `createMaterial()` function
6. Compile as a shared library (.so) following the naming convention



## Integrating with Primitives

Materials can be assigned to primitives using the primitive's `setMaterial()` method.
This allows for reusable materials across different primitives.
When creating complex scenes, consider creating a library of commonly used materials.
