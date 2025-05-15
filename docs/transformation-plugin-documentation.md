# Transformation Plugins Documentation for Raytracer

## Introduction

This document explains how to create material plugins for the raytracer.  
Our raytracer system is designed with a modular architecture where the core and rendering components are in the main binary,  
while transformations are dynamically loaded from shared libraries (.so).



## Naming Conventions

Each transformation plugin must follow this naming convention:
```
raytrace_transformation_[transformation_name].so
```
For example, for a translation: `raytrace_transformation_translation.so`



## Plugin Architecture

To create a new transformation plugin, you need to implement two main classes:
1. A transformation class that inherits from `ATransformation`
2. A builder class for this transformation that inherits from `ATransformationBuilder`



### Class Hierarchy

```
ITransformation (Interface)
└── ATransformation (Abstract class)
    └── YourTransformation (Concrete implementation)

ITransformationBuilder (Interface)
└── ATransformationBuilder (Abstract class)
    └── YourTransformationBuilder (Concrete implementation)
```



## Creating a New Transformation

### 1. Transformation Class

Your transformation class must inherit from `ATransformation` and implement all required virtual methods.  
Example:
```cpp
namespace Raytracer {
    /**
     * @class YourTransformation
     * @brief Represents a YourTransformation transformation in 3D space
     */
    class YourTransformation final : public ATransformation {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new YourTransformation object
             */
            YourTransformation();

            /**
             * @brief Destroy the YourTransformation object
             */
            ~YourTransformation() final;

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
}
```


### 2. Builder Class

Your builder class must inherit from `ATransformationBuilder` and implement the necessary methods to configure your transformation.  
Example:
```cpp
namespace Raytracer {
    /**
     * @class YourTransformationBuilder
     * @brief Builder for the YourTransformation transformation
     */
    class YourTransformationBuilder final : public ATransformationBuilder {
        public:
            /* Constructors and destructors */
            
            /**
             * @brief Constructor of the YourTransformationBuilder
             * @param YourTransformation Reference to a YourTransformation to be configured
             */
            YourTransformationBuilder(YourTransformation &YourTransformation);
            
            /**
             * @brief Destructor of the YourTransformationBuilder
             */
            ~YourTransformationBuilder() final;
            
            
            
            /* Setters of the specific properties */
            
            /**
             * @brief Set the specific property of the transformation
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the transformation builder being configured
             */
            ITransformationBuilder &set(const std::string &name, const std::vector<std::string> &args) final;
        
        
        
        protected:
            YourTransformation &_yourTransformation; ///< Reference to the YourTransformation being configured
    };
}
```


### 3. Export Function

Each plugin must export a creation function named `createTransformation` with the following signature:
```cpp
/**
 * @brief Create a new YourTransformation object
 * @return std::shared_ptr<YourTransformation> A shared pointer to the created YourTransformation object
 */
extern "C" std::shared_ptr<YourTransformation> createTransformation(void);
```
This function will be called by the raytracer core to instantiate your transformation.



## Implementation Details

### The ITransformation Class

This interface defines the basic functionalities that any transformation must implement:
- Access to the builder (`getBuilder`)
- Information display (`display`)


### The ATransformation Class

This abstract class implements common functionalities shared by all transformations:
- Base implementation of the `display` method

You must implement in your derived class:
- The `getBuilder()` method
- Properties and methods specific to your transformation


### The ITransformationBuilder Class

This interface defines the behavior of transformation builders:
- Configuration of properties specific to the transformation (`set`)


### The ATransformationBuilder Class

This abstract class implements functionalities common to builders:
- Storage of a reference to the transformation being configured

You must implement in your derived builder class:
- The `set()` method to handle properties specific to your transformation



## How to Compile a Plugin

To compile your transformation plugin as a shared library (.so), use this command:
```bash
g++ -std=c++20 -Wall -Wextra -Werror -fPIC -shared \
    -I./include/Transformation/common \
    -I./include/Transformation \
    -I./include/lib/my \
    -L./plugins -l:raytracer_transformation.so \
    -o plugins/raytracer_transformation_<name>.so \
    src/Transformation/<name>.cpp
```



## Plugin Loading

The raytracer core will automatically search for and load all `.so` files that follow the naming convention.
For each plugin found, it will call the `createTransformation()` function to instantiate the transformation.



## Summary of Steps to Create a New Plugin

1. Create a class that inherits from `ATransformation`
2. Implement all required virtual methods
3. Create a builder class that inherits from `ATransformationBuilder`
4. Implement the `set()` method to configure specific properties
5. Export the `createTransformation()` function
6. Compile as a shared library (.so) following the naming convention



## Integrating with Primitives

Materials can be assigned to primitives using the primitive's `setMaterial()` method.
This allows for reusable materials across different primitives.
When creating complex scenes, consider creating a library of commonly used materials.
