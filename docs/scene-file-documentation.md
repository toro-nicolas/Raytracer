# Scene File Documentation for Raytracer

This document describes the structure and available options for configuring 3D scenes in our raytracing engine via `.cfg` files.  
This documentation is based on the libconfig scene loader plugin, which allows for easy configuration of scenes using a simple syntax.  
The objects in the scene depend on plugins, which are loaded at runtime.  
The plugin name must follow the convention `raytracer_[type]_[plugin_name].so` to be recognized by the engine.

## Table of Contents
1. [General Structure](#general-structure)
2. [File Imports](#file-imports)
3. [Camera Configuration](#camera-configuration)
4. [Primitives](#primitives)
5. [Lights](#lights)



## General Structure

Scene files use a ligconfig syntax.  
You can use the `#` and `\\` characters to add comments in your scene file.  
The general structure of a scene file is as follows:
```c
import = (
    // Import other scene files (optional)
);

camera: {
    // Camera configuration
};

primitives: {
    // Scene objects definition
};

lights: {
    // Light sources definition
};
```
Order does not matter, but it is recommended to keep the `camera` block at the top for clarity.
Please refer to the sections below for detailed descriptions of each block.



## File Imports

External scenes files can be imported to reuse scene elements:
```c
import = (
    "scenes/sky.cfg",
    "scenes/floor.cfg"
);
```
Recursive imports doesn't present any problem.  
If a scene file imports another file, the engine will load all the files in the import chain.  
An imported file can only be a scene file.  
Only the primitives and lights defined in the imported file will be added to the current scene.



## Camera Configuration

The `camera` block defines the properties of the camera used for rendering.  
The default camera settings that will be used if the camera block is not defined are:
```c
camera: {
    resolution = {
        width = 1920;
        height = 1080;
    };
    position = {
        x = -1.0;
        y = 2.0;
        z = -1.0;
    };
    lookAt = {
        x = 0.0;
        y = 2.0;
        z = 0.0;
    };
    rotation = {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    };
    fieldOfView = 90.0;
    defocusAngle = 0.0;
    focusDistance = 10.0;
    maxDepth = 10;
    samplesPerPixel = 10;
};
```

### Camera Parameters

| Parameter          | Description                                                                   |
|--------------------|-------------------------------------------------------------------------------|
| `resolution`       | Defines the width and height of the image in pixels                           |
| `position`         | Camera position in 3D space (x, y, z coordinates)                             |
| `lookAt`           | Point toward which the camera is oriented (x, y, z coordinates)               |
| `rotation`         | Camera rotation in degrees (x, y, z), like an additional offset of the lookAt |
| `fieldOfView`      | Field of view angle in degrees                                                |
| `defocusAngle`     | Defocus angle for depth of field effect (0 = no blur)                         |
| `focusDistance`    | Distance at which objects are perfectly in focus                              |
| `maxDepth`         | Maximum ray recursion depth (number of bounces)                               |
| `samplesPerPixel`  | Number of samples per pixel for anti-aliasing                                 |



## Primitives

The `primitives` block contains an infinite number of objects that can be rendered in the scene.  
All objects are primitive plugins.  
For each primitive plugin, you can define an infinite number of objects in the `primitives` block.  
All you need to do is create a list of the same object.  
For example, if I have the `raytracer_primitive_plane.so` plugin, I can make a list of `planes = ();` or `plane = ();`.  

All primitives have:
- a `position` parameter, which is the position of the object in 3D space
- a map of Material parameters
- a map of Transformation parameters

The loader will first check whether the parameter is a material.  
If it's not a material, it will look to see if it's a transformation.  
If it's not a transformation either, it will send the parameter to the primitive's builder `set`.  
If a material or transformation of the same type is defined a second time, it will be replaced.  
Materials and transformations have no default parameters, so each parameter will be sent to the builder's `set`.  
Don't forget that the order of materials can affect rendering.  
Parameters not defined in a primitive will use their default values.

### Set builders function

All builders use the set function. It takes a key and args.  
The key is the parameter to be added, and the args are the arguments that go with the parameter.  
The arguments are a list of strings representing the recursive value.  
Here's an example for a sample material:  
```c
test_material = {
    r = 255;
    g = 255;
    b = 255;
    vector = {
        x = 0.0;
        y = 2.0;
        z = 0.0;
    };
    texture = {
        file = {
            path = "textures/earth.jpg";
            type = "jpg";
        }
    };
};
```
The set function will be called like this:
```c
test_material.set("r", {"255"});
test_material.set("g", {"255"});
test_material.set("b", {"255"});
test_material.set("vector", {"0.0", "2.0", "0.0"});
test_material.set("texture", {"file", "textures/earth.jpg", "jpg"});
```



### Default Materials

#### Color

The color material is a material to define the color of the primitive.
Default values are:
```c
color = {
    r = 0.0;
    g = 0.0;
    b = 0.0;
};
```

Parameters details:

| Parameter    | Description                                       |
|--------------|---------------------------------------------------|
| `r`          | Red component of the color (0.0-255.0 or "XX%")   |
| `g`          | Green component of the color (0.0-255.0 or "XX%") |
| `b`          | Blue component of the color (0.0-255.0 or "XX%")  |

Example:
```c
color = {
    r = 255;
    g = "75.5%";
    b = 15.8;
};
```


#### Reflection

The reflection material is a material to define the reflection of the primitive.

Default values are:
```c
reflection = "0%"
```

Parameters details:

| Parameter    | Description                                      |
|--------------|--------------------------------------------------|
| `reflection` | Reflection level of the primitive (0-100%)       |

Example:
```c
reflection = "100%";
```


#### Refraction

The refraction material is a material to define the refraction of the primitive.

Default values are:
```c
refraction = "0%"
```

Parameters details:

| Parameter    | Description                                      |
|--------------|--------------------------------------------------|
| `refraction` | Refraction level of the primitive (0-100%)       |

Example:
```c
refraction = "100%";
```


### Default Transformations

#### Translation

The translation transformation is a transformation to define the translation of the primitive.
Default values are:
```c
translation = {
    x = 0.0;
    y = 0.0;
    z = 0.0;
};
```

Parameters details:

| Parameter    | Description                                       |
|--------------|---------------------------------------------------|
| `x`          | Translation on the x-axis (in units)              |
| `y`          | Translation on the y-axis (in units)              |
| `z`          | Translation on the z-axis (in units)              |

Example:
```c
translation = {
    x = 1.0;
    y = 2.0;
    z = 3.0;
};
```

#### Rotation

The rotation transformation is a transformation to define the rotation of the primitive.
Default values are:
```c
rotation = {
    x = 0.0;
    y = 0.0;
    z = 0.0;
};
```

Parameters details:

| Parameter    | Description                                       |
|--------------|---------------------------------------------------|
| `x`          | Rotation around the x-axis (in degrees)           |
| `y`          | Rotation around the y-axis (in degrees)           |
| `z`          | Rotation around the z-axis (in degrees)           |

Example:
```c
rotation = {
    x = 90.0;
    y = 0.0;
    z = 0.0;
};
```


### Default Primitives

### Spheres

The sphere primitive is a basic 3D object defined by its center position and radius.
Default values are:
```c
spheres = (
    {
        position = {
            x = 0.0;
            y = 0.0;
            z = 0.0;
        };
        r = 0.0;
    }
);
```

Parameters details:

| Parameter    | Description                                           |
|--------------|-------------------------------------------------------|
| `position`   | Position of the sphere's center (x, y, z coordinates) |
| `r`          | Radius of the sphere                                  |

Example:
```c
spheres = (
    {
        position = {
            x = 0.0;
            y = 1.0;
            z = 0.0;
        };
        r = 1.0;
        
        // Additional material and transformation parameters can be added here
    }
);
```


### Planes

The plane primitive is a flat surface defined by its normal vector and a point on the plane.
Default values are:
```c
planes = (
    {
        position = {
            x = 0.0;
            y = 0.0;
            z = 0.0;
        };
        direction = {
            xu = 0.0;
            yu = 0.0;
            zu = 0.0;
            xv = 0.0;
            yv = 0.0;
            zv = 0.0;
        };
    }
);
```

Parameters details:

| Parameter   | Description                                              |
|-------------|----------------------------------------------------------|
| `position`  | Position of the point on the plane (x, y, z coordinates) |
| `direction` | Normal vector of the plane (xu, yu, zu) and (xv, yv, zv) |

Example:
```c
planes = (
    {
        position = {
            x = 0.0;
            y = 1.0;
            z = 0.0;
        };
        direction = {
            xu = 1.0;
            yu = 0.0;
            zu = 0.0;
            xv = 0.0;
            yv = 1.0;
            zv = 0.0;
        };
        
        // Additional material and transformation parameters can be added here
    }
);
```



## Lights

The `lights` block defines the lighting configuration for the scene.  
It includes ambient lighting settings and different types of light sources.  
Like primitives, lights can be defined in a list.  
For each light type, you can define multiple lights in the `lights` block.  

Default values for the lights block are:
```c
lights: {
    ambient = 0.0;
};
```

General parameters for lights:

| Parameter | Description                                                                                |
|-----------|--------------------------------------------------------------------------------------------|
| `ambient` | Global ambient light multiplier (0.0-1.0). Affects the base illumination of all objects    |


### Default Lights

#### Point Lights

Point lights emit light in all directions from a specific point in 3D space.  
They're useful for creating local light sources like lamps or bulbs.  
Default values are:
```c
    point = (
        {
            position = {
                x = 0.0;
                y = 0.0;
                z = 0.0;
            };
            intensity = "0%";
        },
    );
};
```

Parameters details:

| Parameter   | Description                                                    |
|-------------|----------------------------------------------------------------|
| `position`  | Position of the light source in 3D space (x, y, z coordinates) |
| `intensity` | Brightness of the light ("X%")                                 |

Example:
```c
point = (
    {
        position = {
            x = 2.0;
            y = 5.0;
            z = 1.0;
        };
        intensity = "80%";
    }, {
        position = {
            x = -3.0;
            y = 2.0;
            z = 4.0;
        };
        intensity = "50%";
    }
);
```


#### Directional Lights

Directional lights emit light rays in a single direction, simulating distant light sources.  
All rays from a directional light are parallel.
Default values are:
```c
directional = (
    {
        position = {
            x = 0.0;
            y = 0.0;
            z = 0.0;
        };
        direction = {
            x = 0.0;
            y = 0.0;
            z = 0.0;
        };
        intensity = 0.0;
    }
);
```

Parameters details:

| Parameter   | Description                                                          |
|-------------|----------------------------------------------------------------------|
| `position`  | Starting position of the light in 3D space (x, y, z coordinates)     |
| `direction` | Direction vector for light rays (x, y, z), will be normalized        |
| `intensity` | Brightness of the light (0.0-1.0)                                    |








## Textures (to rework)

### Checker Texture

```c
color = {
    texture = {
        type = "checker";
        scale = 0.32;
        r1 = 0.2;  g1 = 0.3;  b1 = 0.1;  // First color
        r2 = 0.9;  g2 = 0.9;  b2 = 0.9;  // Second color
    };
};
```

#### Texture Parameters

| Parameter    | Description                                             |
|--------------|---------------------------------------------------------|
| `type`       | Texture type ("checker" for checkered pattern)          |
| `scale`      | Texture scale (size of squares for the checker pattern) |
| `r1, g1, b1` | First color of the pattern                              |
| `r2, g2, b2` | Second color of the pattern                             |


### File Texture

```c
color = {
    texture = {
        type = "image";
        filename = "scenes/earthmap.jpg";
    };
};
```

#### Texture Parameters
| Parameter    | Description                                             |
|--------------|---------------------------------------------------------|
| `type`       | Texture type ("image" for image file)                   |
| `filename`   | Path to the image file (e.g., "scenes/earthmap.jpg")    |

### Perlin Noise Texture

```c
color = {
    texture = {
        type = "perlin";
        scale = 4;
    };
};
```

#### Texture Parameters
| Parameter    | Description                                             |
|--------------|---------------------------------------------------------|
| `type`       | Texture type ("perlin" for Perlin noise)                |
| `scale`      | Scale of the Perlin noise texture                       |