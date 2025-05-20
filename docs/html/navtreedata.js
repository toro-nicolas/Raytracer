/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "Raytracer documentation", "index.html", [
    [ "Interface Plugins Documentation for Raytracer", "md_docs_2interface-plugin-documentation.html", [
      [ "Introduction", "md_docs_2interface-plugin-documentation.html#autotoc_md1", null ],
      [ "Naming Conventions", "md_docs_2interface-plugin-documentation.html#autotoc_md2", null ],
      [ "Plugin Architecture", "md_docs_2interface-plugin-documentation.html#autotoc_md3", [
        [ "Class Hierarchy", "md_docs_2interface-plugin-documentation.html#autotoc_md4", null ]
      ] ],
      [ "Creating a New Interface", "md_docs_2interface-plugin-documentation.html#autotoc_md5", [
        [ "Interface Class", "md_docs_2interface-plugin-documentation.html#autotoc_md6", null ],
        [ "Export Function", "md_docs_2interface-plugin-documentation.html#autotoc_md7", null ]
      ] ],
      [ "Implementation Details", "md_docs_2interface-plugin-documentation.html#autotoc_md8", [
        [ "The IInterface Class", "md_docs_2interface-plugin-documentation.html#autotoc_md9", null ],
        [ "The AInterface Class", "md_docs_2interface-plugin-documentation.html#autotoc_md10", null ]
      ] ],
      [ "How to Compile a Interface Plugin", "md_docs_2interface-plugin-documentation.html#autotoc_md11", null ],
      [ "Plugin Loading", "md_docs_2interface-plugin-documentation.html#autotoc_md12", null ],
      [ "Summary of Steps to Create a New Interface Plugin", "md_docs_2interface-plugin-documentation.html#autotoc_md13", null ]
    ] ],
    [ "Light Plugins Documentation for Raytracer", "md_docs_2light-plugin-documentation.html", [
      [ "Introduction", "md_docs_2light-plugin-documentation.html#autotoc_md15", null ],
      [ "Naming Conventions", "md_docs_2light-plugin-documentation.html#autotoc_md16", null ],
      [ "Plugin Architecture", "md_docs_2light-plugin-documentation.html#autotoc_md17", [
        [ "Class Hierarchy", "md_docs_2light-plugin-documentation.html#autotoc_md18", null ]
      ] ],
      [ "Creating a New Light", "md_docs_2light-plugin-documentation.html#autotoc_md19", [
        [ "Light Class", "md_docs_2light-plugin-documentation.html#autotoc_md20", null ],
        [ "Builder Class", "md_docs_2light-plugin-documentation.html#autotoc_md21", null ],
        [ "Export Function", "md_docs_2light-plugin-documentation.html#autotoc_md22", null ]
      ] ],
      [ "Implementation Details", "md_docs_2light-plugin-documentation.html#autotoc_md23", [
        [ "The ILight Class", "md_docs_2light-plugin-documentation.html#autotoc_md24", null ],
        [ "The ALight Class", "md_docs_2light-plugin-documentation.html#autotoc_md25", null ],
        [ "The ILightBuilder Class", "md_docs_2light-plugin-documentation.html#autotoc_md26", null ],
        [ "The ALightBuilder Class", "md_docs_2light-plugin-documentation.html#autotoc_md27", null ]
      ] ],
      [ "How to Compile a Plugin", "md_docs_2light-plugin-documentation.html#autotoc_md28", null ],
      [ "Plugin Loading", "md_docs_2light-plugin-documentation.html#autotoc_md29", null ],
      [ "Summary of Steps to Create a New Plugin", "md_docs_2light-plugin-documentation.html#autotoc_md30", null ]
    ] ],
    [ "Material Plugins Documentation for Raytracer", "md_docs_2material-plugin-documentation.html", [
      [ "Introduction", "md_docs_2material-plugin-documentation.html#autotoc_md32", null ],
      [ "Naming Conventions", "md_docs_2material-plugin-documentation.html#autotoc_md33", null ],
      [ "Plugin Architecture", "md_docs_2material-plugin-documentation.html#autotoc_md34", [
        [ "Class Hierarchy", "md_docs_2material-plugin-documentation.html#autotoc_md35", null ]
      ] ],
      [ "Creating a New Material", "md_docs_2material-plugin-documentation.html#autotoc_md36", [
        [ "Material Class", "md_docs_2material-plugin-documentation.html#autotoc_md37", null ],
        [ "Builder Class", "md_docs_2material-plugin-documentation.html#autotoc_md38", null ],
        [ "Export Function", "md_docs_2material-plugin-documentation.html#autotoc_md39", null ]
      ] ],
      [ "Implementation Details", "md_docs_2material-plugin-documentation.html#autotoc_md40", [
        [ "The IMaterial Class", "md_docs_2material-plugin-documentation.html#autotoc_md41", null ],
        [ "The AMaterial Class", "md_docs_2material-plugin-documentation.html#autotoc_md42", null ],
        [ "The IMaterialBuilder Class", "md_docs_2material-plugin-documentation.html#autotoc_md43", null ],
        [ "The AMaterialBuilder Class", "md_docs_2material-plugin-documentation.html#autotoc_md44", null ]
      ] ],
      [ "How to Compile a Material Plugin", "md_docs_2material-plugin-documentation.html#autotoc_md45", null ],
      [ "Plugin Loading", "md_docs_2material-plugin-documentation.html#autotoc_md46", null ],
      [ "Summary of Steps to Create a New Material Plugin", "md_docs_2material-plugin-documentation.html#autotoc_md47", null ],
      [ "Integrating with Primitives", "md_docs_2material-plugin-documentation.html#autotoc_md48", null ]
    ] ],
    [ "Primitive Plugins Documentation for Raytracer", "md_docs_2primitive-plugin-documentation.html", [
      [ "Introduction", "md_docs_2primitive-plugin-documentation.html#autotoc_md50", null ],
      [ "Naming Conventions", "md_docs_2primitive-plugin-documentation.html#autotoc_md51", null ],
      [ "Plugin Architecture", "md_docs_2primitive-plugin-documentation.html#autotoc_md52", [
        [ "Class Hierarchy", "md_docs_2primitive-plugin-documentation.html#autotoc_md53", null ]
      ] ],
      [ "Creating a New Primitive", "md_docs_2primitive-plugin-documentation.html#autotoc_md54", [
        [ "Primitive Class", "md_docs_2primitive-plugin-documentation.html#autotoc_md55", null ],
        [ "Builder Class", "md_docs_2primitive-plugin-documentation.html#autotoc_md56", null ],
        [ "Export Function", "md_docs_2primitive-plugin-documentation.html#autotoc_md57", null ]
      ] ],
      [ "Implementation Details", "md_docs_2primitive-plugin-documentation.html#autotoc_md58", [
        [ "The IPrimitive Class", "md_docs_2primitive-plugin-documentation.html#autotoc_md59", null ],
        [ "The APrimitive Class", "md_docs_2primitive-plugin-documentation.html#autotoc_md60", null ],
        [ "The IPrimitiveBuilder Class", "md_docs_2primitive-plugin-documentation.html#autotoc_md61", null ],
        [ "The APrimitiveBuilder Class", "md_docs_2primitive-plugin-documentation.html#autotoc_md62", null ]
      ] ],
      [ "How to Compile a Plugin", "md_docs_2primitive-plugin-documentation.html#autotoc_md63", null ],
      [ "Plugin Loading", "md_docs_2primitive-plugin-documentation.html#autotoc_md64", null ],
      [ "Summary of Steps to Create a New Plugin", "md_docs_2primitive-plugin-documentation.html#autotoc_md65", null ]
    ] ],
    [ "Scene File Documentation for Raytracer", "md_docs_2scene-file-documentation.html", [
      [ "📚 Table of Contents", "md_docs_2scene-file-documentation.html#autotoc_md68", null ],
      [ "🧱 General Structure", "md_docs_2scene-file-documentation.html#autotoc_md70", null ],
      [ "📁 File Imports", "md_docs_2scene-file-documentation.html#autotoc_md72", null ],
      [ "Camera Configuration", "md_docs_2scene-file-documentation.html#autotoc_md74", [
        [ "🎥 Camera Parameters", "md_docs_2scene-file-documentation.html#autotoc_md75", null ]
      ] ],
      [ "🧩 Primitives", "md_docs_2scene-file-documentation.html#autotoc_md77", [
        [ "Set builders function", "md_docs_2scene-file-documentation.html#autotoc_md78", null ],
        [ "🎨 Default Materials", "md_docs_2scene-file-documentation.html#autotoc_md79", [
          [ "Color", "md_docs_2scene-file-documentation.html#autotoc_md80", [
            [ "Texture", "md_docs_2scene-file-documentation.html#autotoc_md81", null ]
          ] ],
          [ "Reflection", "md_docs_2scene-file-documentation.html#autotoc_md82", null ],
          [ "Refraction", "md_docs_2scene-file-documentation.html#autotoc_md83", null ],
          [ "Diffuse Light", "md_docs_2scene-file-documentation.html#autotoc_md84", null ]
        ] ],
        [ "🔁 Default Transformations", "md_docs_2scene-file-documentation.html#autotoc_md85", [
          [ "Translation", "md_docs_2scene-file-documentation.html#autotoc_md86", null ],
          [ "Rotation", "md_docs_2scene-file-documentation.html#autotoc_md87", null ]
        ] ],
        [ "🧩 Default Primitives", "md_docs_2scene-file-documentation.html#autotoc_md88", [
          [ "Planes", "md_docs_2scene-file-documentation.html#autotoc_md89", null ],
          [ "Spheres", "md_docs_2scene-file-documentation.html#autotoc_md90", null ]
        ] ],
        [ "Boxes", "md_docs_2scene-file-documentation.html#autotoc_md91", null ],
        [ "Cylinders", "md_docs_2scene-file-documentation.html#autotoc_md92", null ],
        [ "Cones", "md_docs_2scene-file-documentation.html#autotoc_md93", null ],
        [ "Torus", "md_docs_2scene-file-documentation.html#autotoc_md94", null ],
        [ "Tanglecube", "md_docs_2scene-file-documentation.html#autotoc_md95", null ],
        [ "Triangle", "md_docs_2scene-file-documentation.html#autotoc_md96", null ]
      ] ],
      [ "💡 Lights", "md_docs_2scene-file-documentation.html#autotoc_md98", [
        [ "💡 Default Lights", "md_docs_2scene-file-documentation.html#autotoc_md99", [
          [ "Point Lights", "md_docs_2scene-file-documentation.html#autotoc_md100", null ],
          [ "Directional Lights", "md_docs_2scene-file-documentation.html#autotoc_md101", null ]
        ] ]
      ] ]
    ] ],
    [ "Scene Loader Plugins Documentation for Raytracer", "md_docs_2scene-loader-plugin-documentation.html", [
      [ "Introduction", "md_docs_2scene-loader-plugin-documentation.html#autotoc_md103", null ],
      [ "Naming Conventions", "md_docs_2scene-loader-plugin-documentation.html#autotoc_md104", null ],
      [ "Plugin Architecture", "md_docs_2scene-loader-plugin-documentation.html#autotoc_md105", [
        [ "Class Hierarchy", "md_docs_2scene-loader-plugin-documentation.html#autotoc_md106", null ]
      ] ],
      [ "Creating a New Scene Loader", "md_docs_2scene-loader-plugin-documentation.html#autotoc_md107", [
        [ "Scene Loader Class", "md_docs_2scene-loader-plugin-documentation.html#autotoc_md108", null ],
        [ "Export Function", "md_docs_2scene-loader-plugin-documentation.html#autotoc_md109", null ]
      ] ],
      [ "Implementation Details", "md_docs_2scene-loader-plugin-documentation.html#autotoc_md110", [
        [ "The ISceneLoader Class", "md_docs_2scene-loader-plugin-documentation.html#autotoc_md111", null ],
        [ "The ASceneLoader Class", "md_docs_2scene-loader-plugin-documentation.html#autotoc_md112", null ]
      ] ],
      [ "How to Compile a Scene Loader Plugin", "md_docs_2scene-loader-plugin-documentation.html#autotoc_md113", null ],
      [ "Plugin Loading", "md_docs_2scene-loader-plugin-documentation.html#autotoc_md114", null ],
      [ "Summary of Steps to Create a New Scene Loader Plugin", "md_docs_2scene-loader-plugin-documentation.html#autotoc_md115", null ]
    ] ],
    [ "Transformation Plugins Documentation for Raytracer", "md_docs_2transformation-plugin-documentation.html", [
      [ "Introduction", "md_docs_2transformation-plugin-documentation.html#autotoc_md117", null ],
      [ "Naming Conventions", "md_docs_2transformation-plugin-documentation.html#autotoc_md118", null ],
      [ "Plugin Architecture", "md_docs_2transformation-plugin-documentation.html#autotoc_md119", [
        [ "Class Hierarchy", "md_docs_2transformation-plugin-documentation.html#autotoc_md120", null ]
      ] ],
      [ "Creating a New Transformation", "md_docs_2transformation-plugin-documentation.html#autotoc_md121", [
        [ "Transformation Class", "md_docs_2transformation-plugin-documentation.html#autotoc_md122", null ],
        [ "Builder Class", "md_docs_2transformation-plugin-documentation.html#autotoc_md123", null ],
        [ "Export Function", "md_docs_2transformation-plugin-documentation.html#autotoc_md124", null ]
      ] ],
      [ "Implementation Details", "md_docs_2transformation-plugin-documentation.html#autotoc_md125", [
        [ "The ITransformation Class", "md_docs_2transformation-plugin-documentation.html#autotoc_md126", null ],
        [ "The ATransformation Class", "md_docs_2transformation-plugin-documentation.html#autotoc_md127", null ],
        [ "The ITransformationBuilder Class", "md_docs_2transformation-plugin-documentation.html#autotoc_md128", null ],
        [ "The ATransformationBuilder Class", "md_docs_2transformation-plugin-documentation.html#autotoc_md129", null ]
      ] ],
      [ "How to Compile a Plugin", "md_docs_2transformation-plugin-documentation.html#autotoc_md130", null ],
      [ "Plugin Loading", "md_docs_2transformation-plugin-documentation.html#autotoc_md131", null ],
      [ "Summary of Steps to Create a New Plugin", "md_docs_2transformation-plugin-documentation.html#autotoc_md132", null ],
      [ "Integrating with Primitives", "md_docs_2transformation-plugin-documentation.html#autotoc_md133", null ]
    ] ],
    [ "Raytracer", "md_README.html", [
      [ "Table of contents 📑", "md_README.html#autotoc_md135", null ],
      [ "Description 📝", "md_README.html#autotoc_md136", null ],
      [ "Usage ⚔️", "md_README.html#autotoc_md137", null ],
      [ "Result 🚩", "md_README.html#autotoc_md138", [
        [ "my.epitech.eu result", "md_README.html#autotoc_md139", null ],
        [ "Defense", "md_README.html#autotoc_md140", null ]
      ] ],
      [ "Compilation 🛠️", "md_README.html#autotoc_md141", null ],
      [ "Documentation 📚", "md_README.html#autotoc_md142", null ],
      [ "Code mandatory 📦", "md_README.html#autotoc_md143", null ],
      [ "Contributors 👥", "md_README.html#autotoc_md144", null ]
    ] ],
    [ "Data Structures", "annotated.html", [
      [ "Data Structures", "annotated.html", "annotated_dup" ],
      [ "Data Structure Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Data Fields", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", null ],
        [ "Enumerations", "functions_enum.html", null ],
        [ "Enumerator", "functions_eval.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"AABB_8cpp.html",
"Vector3_8hpp.html#ae9461e8d141960709c7fbd36e991171f",
"classRaytracer_1_1Camera.html#a2dea7a8716d46779a8db1851000f03f7",
"classRaytracer_1_1Interval.html",
"classlights_1_1Lights_1_1LightChoice.html",
"md_docs_2transformation-plugin-documentation.html#autotoc_md119"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';