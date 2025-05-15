# Interface Plugins Documentation for Raytracer

## Introduction

This document explains how to create interface plugins for the raytracer.  
Our raytracer system is designed with a modular architecture where the core and rendering components are in the main binary,  
while interfaces are dynamically loaded from shared libraries (.so).



## Naming Conventions

Each interface plugin must follow this naming convention:
```
raytrace_interface_[interface_name].so
```
For example, for a libconfig interface: `raytrace_interface_libconfig.so`



## Plugin Architecture

To create a new interface plugin, you need to implement two main classes:
1. A interface class that inherits from `AInterface`



### Class Hierarchy

```
IInterface (Interface)
└── AInterface (Abstract class)
    └── YourInterface (Concrete implementation)
```



## Creating a New Interface

### 1. Interface Class

Your interface class must inherit from `AInterface` and implement all required virtual methods.  
Example:
```cpp
namespace Raytracer {
    /**
     * @class YourInterface
     * @brief Class for rendering scenes with YourInterface
     */
    class YourInterface final : public ASceneLoader
    {
        public:
            /* Constructor and destructor */

            /**
             * @brief Constructor for YourInterface class
             */
            YourSceneLoader();

            /**
             * @brief Destructor for YourInterface class
             */
            ~YourSceneLoader() final;



            /* Rendering functions */

            /**
             * @brief Set the color of a specific pixel
             * @param x The x coordinate of the pixel
             * @param y The y coordinate of the pixel
             * @param r Red component (0-255)
             * @param g Green component (0-255)
             * @param b Blue component (0-255)
             */
            void setPixel(int x, int y, int r, int g, int b) final;

            /**
             * @brief Render the scene to the output format
             */
            void render() final;

            /**
             * @brief Legacy method for rendering camera (can delegate to render)
             * @param map The color map to render
             */
            void renderCamera(std::vector<std::vector<ColorRGB>> &screen) final;



        protected:

        private:
            
            /* Methods specific to your interface */
    };
}
```


### 2. Export Function

Each plugin must export a creation function named `createInterface` with the following signature:
```cpp
/**
 * @brief Create a YourInterface interface
 * @return <b>std::unique_ptr<IInterface></b> A unique pointer to the YourInterface interface
 */
extern "C" std::unique_ptr<IInterface> createInterface();
```
This function will be called by the raytracer core to instantiate your interface.



## Implementation Details

### The IInterface Class

This interface defines the basic functionalities that any interface must implement:
- Resolution management (`getResolution`, `setResolution`)
- Pixels management (`setPixel`)
- Rendering management (`render`, `renderCamera`)


### The AInterface Class

This abstract class implements common functionalities shared by all interface:
- Storage and access to resolution (`_resolution`)
- Storage and access to pixels (`_pixels`)

You must implement in your derived class:
- The `setPixel()` method
- The `render()` method
- The `renderCamera()` method



## How to Compile a Interface Plugin

To compile your interface plugin as a shared library (.so), use this command:
```bash
g++ -std=c++20 -Wall -Wextra -Werror -fPIC -shared \
    -I./include/Light/common \
    -I./include/Material/common \
    -I./include/Primitives/common \
    -I./include/Transformation/common \
    -I./include/Interface/common \
    -I./include/Camera \
    -I./include/Plugin \
    -I./include/Interface/ \
    -I./include/lib/my \
    -L./plugins -l:raytracer_interface.so \
    -o plugins/raytracer_interface_<name>.so \
    src/Interface/<name>.cpp
```



## Plugin Loading

The raytracer core will select the `.so` precised in the configuration file with the `interface` key.
It will then load the plugin using the plugin loader and call the `createInterface()` function to instantiate the interface.



## Summary of Steps to Create a New Interface Plugin

1. Create a class that inherits from `AInterface`
2. Implement all required virtual methods
3. Export the `createInterface()` function
4. Compile as a shared library (.so) following the naming convention
