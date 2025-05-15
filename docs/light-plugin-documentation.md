# Light Plugins Documentation for Raytracer

## Introduction

This document explains how to create light plugins for the raytracer.  
Our raytracer system is designed with a modular architecture where the core and rendering components are in the main binary,  
while lights are dynamically loaded from shared libraries (.so).



## Naming Conventions

Each light plugin must follow this naming convention:
```
raytrace_light_[light_name].so
```
For example, for a directional light: `raytrace_light_directional.so`



## Plugin Architecture

To create a new light plugin, you need to implement two main classes:
1. A light class that inherits from `ALight`
2. A builder class for this light that inherits from `ALightBuilder`


### Class Hierarchy

```
ILight (Interface)
└── ALight (Abstract class)
    └── YourLight (Concrete implementation)

ILightBuilder (Interface)
└── ALightBuilder (Abstract class)
    └── YourLightBuilder (Concrete implementation)
```



## Creating a New Light

### 1. Light Class

Your light class must inherit from `ALight` and implement all required virtual methods.
Example:
```cpp
namespace Raytracer {
    /**
     * @class YourLight
     * @brief Represents a YourLight light in 3D space
     */
    class YourLight final : public ALight {
        public:
            /* Constructors and destructors */

            /**
             * @brief Construct a new YourLight object
             */
            YourLight();

            /**
             * @brief Destroy the YourLight object
             */
            ~YourLight() final;

            /**
             * @brief Get the builder of the light
             * @return A reference to a unique pointer to the light builder
             */
            std::unique_ptr<ILightBuilder> &getBuilder(void) final;



            /* Display function */

            /**
             * @brief Display the light
             */
            void display(void) final;

            

            /* Methods specific to your light */

            

        protected:

        private:
            /* Properties specific to your light */
    };
}
```


### 2. Builder Class

Your builder class must inherit from `ALightBuilder` and implement the necessary methods to configure your light.  
Example:
```cpp
namespace Raytracer {
    /**
     * @class YourLightBuilder
     * @brief Builder for the YourLight light
     */
    class YourLightBuilder final : public ALightBuilder {
        public:
            /* Constructors and destructors */
            
            /**
             * @brief Constructor of the YourLightBuilder
             * @param yourLight Reference to a YourLight to be configured
             */
            YourLightBuilder(YourLight &yourLight);
            
            /**
             * @brief Destructor of the YourLightBuilder
             */
            ~YourLightBuilder() final;
            
            
            
            /* Setters of the specific properties */
            
            /**
             * @brief Set the specific property of the light
             * @param name The name of the property
             * @param args The arguments to set
             * @return Reference to the YourLight builder being configured
             */
            ILightBuilder &set(const std::string &name, const std::vector<std::string> &args) final;
        
        
        
        protected:
            YourLight &_yourLight; ///< Reference to the YourLight being configured
    };
}
```


### 3. Export Function

Each plugin must export a creation function named `createLight` with the following signature:
```cpp
/**
 * @brief Create a YourLight object
 * @return std::shared_ptr<YourLight> A shared pointer to the created YourLight object
 */
extern "C" std::shared_ptr<YourLight> createLight(void);
```
This function will be called by the raytracer core to instantiate your light.



## Implementation Details

### The ILight Class

This interface defines the basic functionalities that any light must implement:
- Position management (`getPos`, `setPos`)
- Intensity management (`getIntensity`, `setIntensity`)
- Access to the builder (`getBuilder`)
- Information display (`display`)


### The ALight Class

This abstract class implements common functionalities shared by all lights:
- Storage and access to position (`_pos`)
- Storage and access to intensity (`_intensity`)
- Base implementation of the `display` method

You must implement in your derived class:
- The `getBuilder()` method
- Properties and methods specific to your light


### The ILightBuilder Class

This interface defines the behavior of light builders:
- Position configuration (`setPos`)
- Intensity configuration (`setIntensity`)
- Configuration of properties specific to the light (`set`)


### The ALightBuilder Class

This abstract class implements functionalities common to builders:
- Storage of a reference to the light being configured
- Implementation of methods to configure position and intensity

You must implement in your derived builder class:
- The `set()` method to handle properties specific to your light



## How to Compile a Plugin

To compile your light plugin as a shared library (.so), use this command:
```bash
g++ -std=c++20 -Wall -Wextra -Werror -fPIC -shared \
    -I./include/Light/common \
    -I./include/Light \
    -I./include/lib/my \
    -L./plugins -l:raytracer_light.so \
    -o plugins/raytracer_light_<name>.so \
    src/Light/<name>.cpp
```



## Plugin Loading

The raytracer core will automatically search for and load all `.so` files that follow the naming convention.  
For each plugin found, it will call the `createLight()` function to instantiate the light.



## Summary of Steps to Create a New Plugin

1. Create a class that inherits from `ALight`
2. Implement all required virtual methods
3. Create a builder class that inherits from `ALightBuilder`
4. Implement the `set()` method to configure specific properties
5. Export the `createLight()` function
6. Compile as a shared library (.so) following the naming convention
