# Scene Loader Plugins Documentation for Raytracer

## Introduction

This document explains how to create scene loader plugins for the raytracer.  
Our raytracer system is designed with a modular architecture where the core and rendering components are in the main binary,  
while scene loaders are dynamically loaded from shared libraries (.so).



## Naming Conventions

Each scene loader plugin must follow this naming convention:
```
raytrace_scene_loader_[scene_loader_name].so
```
For example, for a libconfig scene loader: `raytrace_scene_loader_libconfig.so`



## Plugin Architecture

To create a new scene loader plugin, you need to implement two main classes:
1. A scene loader class that inherits from `ASceneLoader`
2. A loader logic to parse scene files and populate the scene data (cameras, primitives, lights)



### Class Hierarchy

```
ISceneLoader (Interface)
└── ASceneLoader (Abstract class)
    └── YourSceneLoader (Concrete implementation)
```



## Creating a New Scene Loader

### 1. Scene Loader Class

Your scene loader class must inherit from `ASceneLoader` and implement all required virtual methods.  
Example:
```cpp
namespace Raytracer {
    /**
     * @class YourSceneLoader
     * @brief Class for loading scenes with YourSceneLoader
     */
    class YourSceneLoader final : public ASceneLoader
    {
        public:
            /* Constructor and destructor */

            /**
             * @brief Constructor for YourSceneLoader class
             */
            YourSceneLoader();

            /**
             * @brief Destructor for YourSceneLoader class
             */
            ~YourSceneLoader() final;



            /* Loader functions */

            /**
             * @brief Load a scene from a file
             * @param path The path of the scene
             * @param plugin_directory The path of the plugin directory
             */
            void loadScene(const std::string &path, const std::string &plugin_directory) final;



        protected:

        private:
            
            /* Methods specific to your scene loader */
    };
}
```


### 2. Export Function

Each plugin must export a creation function named `createSceneLoader` with the following signature:
```cpp
/**
 * @brief Function to create an instance of the Libconfig
 * @note The function get with dlsym in the PluginLoader class
 * @return <b>std::unique_ptr<ISceneLoader></b> A unique pointer to the Libconfig
 */
extern "C" std::unique_ptr<ISceneLoader> createSceneLoader();
```
This function will be called by the raytracer core to instantiate your scene loader.



## Implementation Details

### The ISceneLoader Class

This interface defines the basic functionalities that any scene loader must implement:
- Loading a scene from a file (`loadScene`)
- Camera management (`getCamera`)
- Lights management (`getLights`)
- Primitives management (`getPrimitives`)
- Information display (`display`)


### The ASceneLoader Class

This abstract class implements common functionalities shared by all scene loaders:
- Storage and access to cameras (`_cameras`)
- Storage and access to lights (`_lights`)
- Storage and access to primitives (`_primitives`)
- Base implementation of the `display` method

You must implement in your derived class:
- The `loadScene()` method
- Properties and methods specific to your scene loader



## How to Compile a Scene Loader Plugin

To compile your scene loader plugin as a shared library (.so), use this command:
```bash
g++ -std=c++20 -Wall -Wextra -Werror -fPIC -shared \
    -I./include/Light/common \
    -I./include/Material/common \
    -I./include/Primitives/common \
    -I./include/Transformation/common \
    -I./include/Scene-loader/common \
    -I./include/Camera \
    -I./include/Plugin \
    -I./include/Scene-loader/ \
    -I./include/lib/my \
    -L./plugins -l:raytracer_scene_loader.so \
    -o plugins/raytracer_scene_loader_<name>.so \
    src/Scene-loader/<name>.cpp
```



## Plugin Loading

The raytracer core will select the `.so` precised in the configuration file with the `scene_loader` key.
It will then load the plugin using the plugin loader and call the `createSceneLoader()` function to instantiate the scene loader.



## Summary of Steps to Create a New Scene Loader Plugin

1. Create a class that inherits from `ASceneLoader`
2. Implement all required virtual methods
3. Use the Factory to create cameras, primitives, and lights.
4. Export the `createSceneLoader()` function
5. Compile as a shared library (.so) following the naming convention
