cmake_minimum_required(VERSION 3.10)



############################ CONFIGURATION ####################################
set(EXECUTABLE_NAME "raytracer")
Project(${EXECUTABLE_NAME} VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/usr/lib64/cmake")
###############################################################################


############################ STANDARD LIB #####################################
file(GLOB STANDARD_LIB "lib/my/*.cpp")
add_library(my ${STANDARD_LIB})
set_target_properties(my PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_options(my PUBLIC -O3)
target_include_directories(my PUBLIC
    ${CMAKE_SOURCE_DIR}/include/lib/my
)
###############################################################################



############################ GRAPHICAL LIB ####################################
# file(GLOB GRAPHIC_LIB "lib/graphics/*.cpp")
# add_library(graphics ${GRAPHIC_LIB})
# target_include_directories(graphics PRIVATE
#     ${CMAKE_SOURCE_DIR}/include/lib/graphics
# )
# find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)
# target_link_libraries(graphics PUBLIC my)
# target_link_libraries(graphics PRIVATE SFML::Graphics SFML::Audio SFML::System)
###############################################################################



############################ CORE #############################################
file(GLOB SOURCES
    "src/*.cpp"
    "src/Core/*.cpp"
    "src/Plugin/*.cpp"
    "src/Camera/*.cpp"
    "src/Rendering/*.cpp"

    "src/Texture/common/*.cpp"
    "src/Texture/*.cpp"
)
add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_include_directories(${EXECUTABLE_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include/Interface/common
    ${CMAKE_SOURCE_DIR}/include/Light/common
    ${CMAKE_SOURCE_DIR}/include/Material/common
    ${CMAKE_SOURCE_DIR}/include/Primitive/common
    ${CMAKE_SOURCE_DIR}/include/Scene-loader/common
    ${CMAKE_SOURCE_DIR}/include/Transformation/common

    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/Core
    ${CMAKE_SOURCE_DIR}/include/Plugin
    ${CMAKE_SOURCE_DIR}/include/Camera
    ${CMAKE_SOURCE_DIR}/include/Rendering


    ${CMAKE_SOURCE_DIR}/include/Texture/common
    ${CMAKE_SOURCE_DIR}/include/Texture/
)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC my)
###############################################################################



############################ LIGHTS ###########################################
# For common light needs
file(GLOB COMMON "src/Light/common/*.cpp")
add_library(raytracer_light SHARED ${COMMON})
set_target_properties(raytracer_light PROPERTIES PREFIX "")
target_include_directories(raytracer_light PUBLIC
        ${CMAKE_SOURCE_DIR}/include/Light/common
)
target_compile_options(raytracer_light PUBLIC -Wall -Wextra -Werror -O3)
set_target_properties(raytracer_light PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
target_link_libraries(raytracer_light PUBLIC my)

# For each light
file(GLOB FINAL_LIGHT "src/Light/*.cpp")
foreach(LIGHT ${FINAL_LIGHT})
    get_filename_component(NAME ${LIGHT} NAME_WE)
    string(TOLOWER ${NAME} NAME)
    add_library(raytracer_light_${NAME} SHARED ${LIGHT})
    set_target_properties(raytracer_light_${NAME} PROPERTIES PREFIX "")
    target_include_directories(raytracer_light_${NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/Light/)
    target_compile_options(raytracer_light_${NAME} PUBLIC -Wall -Wextra -Werror -O3)
    set_target_properties(raytracer_light_${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
    target_link_libraries(raytracer_light_${NAME} PUBLIC raytracer_light)
endforeach()
###############################################################################



############################ MATERIALS ########################################
# For common material needs
file(GLOB COMMON
    "src/Material/common/*.cpp"
    "src/Rendering/Ray.cpp"
    "src/Texture/common/*.cpp"
    "src/Texture/*.cpp")
add_library(raytracer_material SHARED ${COMMON})
set_target_properties(raytracer_material PROPERTIES PREFIX "")
target_include_directories(raytracer_material PUBLIC
        ${CMAKE_SOURCE_DIR}/include/Material/common
        ${CMAKE_SOURCE_DIR}/include/Rendering

        ${CMAKE_SOURCE_DIR}/include/Texture/common
        ${CMAKE_SOURCE_DIR}/include/Texture/
)
target_compile_options(raytracer_material PUBLIC -Wall -Wextra -Werror -O3)
set_target_properties(raytracer_material PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
target_link_libraries(raytracer_material PUBLIC my)

# For each materials
file(GLOB FINAL_MATERIALS "src/Material/*.cpp")
foreach(MATERIAL ${FINAL_MATERIALS})
    get_filename_component(NAME ${MATERIAL} NAME_WE)
    string(TOLOWER ${NAME} NAME)
    add_library(raytracer_material_${NAME} SHARED ${MATERIAL})
    set_target_properties(raytracer_material_${NAME} PROPERTIES PREFIX "")
    target_include_directories(raytracer_material_${NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/Material/)
    target_compile_options(raytracer_material_${NAME} PUBLIC -Wall -Wextra -Werror -O3)
    set_target_properties(raytracer_material_${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
    target_link_libraries(raytracer_material_${NAME} PUBLIC raytracer_material)
endforeach()
###############################################################################



############################ TRANSFORMATION ###################################
# For common transformation needs
file(GLOB COMMON "src/Transformation/common/*.cpp"
    "src/Rendering/Ray.cpp"
    "src/Rendering/AABB.cpp"
    )
add_library(raytracer_transformation SHARED ${COMMON})
set_target_properties(raytracer_transformation PROPERTIES PREFIX "")
target_include_directories(raytracer_transformation PUBLIC
        ${CMAKE_SOURCE_DIR}/include/Transformation/common
        ${CMAKE_SOURCE_DIR}/include/Rendering
)
target_compile_options(raytracer_transformation PUBLIC -Wall -Wextra -Werror -O3)
set_target_properties(raytracer_transformation PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
target_link_libraries(raytracer_transformation PUBLIC my)

# For each transformations
file(GLOB FINAL_TRANSFORMATIONS "src/Transformation/*.cpp")
foreach(TRANSFORMATION ${FINAL_TRANSFORMATIONS})
    get_filename_component(NAME ${TRANSFORMATION} NAME_WE)
    string(TOLOWER ${NAME} NAME)
    add_library(raytracer_transformation_${NAME} SHARED ${TRANSFORMATION})
    set_target_properties(raytracer_transformation_${NAME} PROPERTIES PREFIX "")
    target_include_directories(raytracer_transformation_${NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/Transformation/)
    target_compile_options(raytracer_transformation_${NAME} PUBLIC -Wall -Wextra -Werror -O3)
    set_target_properties(raytracer_transformation_${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
    target_link_libraries(raytracer_transformation_${NAME} PUBLIC raytracer_transformation)
endforeach()
###############################################################################



############################ PRIMITIVES #######################################
# For common primitive needs
file(GLOB COMMON "src/Primitive/common/*.cpp" "src/Rendering/Ray.cpp" "src/Rendering/AABB.cpp")
add_library(raytracer_primitive SHARED ${COMMON})
set_target_properties(raytracer_primitive PROPERTIES PREFIX "")
target_include_directories(raytracer_primitive PUBLIC
        ${CMAKE_SOURCE_DIR}/include/Material/common
        ${CMAKE_SOURCE_DIR}/include/Transformation/common
        ${CMAKE_SOURCE_DIR}/include/Primitive/common
        ${CMAKE_SOURCE_DIR}/include/Rendering
)
target_compile_options(raytracer_primitive PUBLIC -Wall -Wextra -Werror -O3)
set_target_properties(raytracer_primitive PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
target_link_libraries(raytracer_primitive PUBLIC my)


# For each primitives
file(GLOB FINAL_PRIMITIVES "src/Primitive/*.cpp")
foreach(PRIMITIVE ${FINAL_PRIMITIVES})
    get_filename_component(NAME ${PRIMITIVE} NAME_WE)
    string(TOLOWER ${NAME} NAME)
    add_library(raytracer_primitive_${NAME} SHARED ${PRIMITIVE})
    set_target_properties(raytracer_primitive_${NAME} PROPERTIES PREFIX "")
    target_include_directories(raytracer_primitive_${NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/Primitive/)
    target_compile_options(raytracer_primitive_${NAME} PUBLIC -Wall -Wextra -Werror -O3)
    set_target_properties(raytracer_primitive_${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
    target_link_libraries(raytracer_primitive_${NAME} PUBLIC raytracer_primitive)
endforeach()
###############################################################################



############################ SCENE LOADER #####################################
# For common scene loader needs
file(GLOB COMMON "src/Scene-loader/common/*.cpp" "src/Plugin/*.cpp" "src/Camera/*.cpp")
add_library(raytracer_scene_loader SHARED ${COMMON})
set_target_properties(raytracer_scene_loader PROPERTIES PREFIX "")
target_include_directories(raytracer_scene_loader PUBLIC
        ${CMAKE_SOURCE_DIR}/include/Light/common
        ${CMAKE_SOURCE_DIR}/include/Material/common
        ${CMAKE_SOURCE_DIR}/include/Primitive/common
        ${CMAKE_SOURCE_DIR}/include/Transformation/common

        ${CMAKE_SOURCE_DIR}/include/
        ${CMAKE_SOURCE_DIR}/include/Plugin
        ${CMAKE_SOURCE_DIR}/include/Camera
        ${CMAKE_SOURCE_DIR}/include/Rendering
        ${CMAKE_SOURCE_DIR}/include/Scene-loader/common
)
target_compile_options(raytracer_scene_loader PRIVATE -Wall -Wextra -Werror -O3)
set_target_properties(raytracer_scene_loader PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
target_link_libraries(raytracer_scene_loader PUBLIC my)

# For each scene loader
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIGPP libconfig++)
if(NOT LIBCONFIGPP_FOUND)
    message(WARNING "libconfig++ not found. Continuing without it.")
else()
    file(GLOB SCENES "src/Scene-loader/*.cpp")
    foreach(SCENE ${SCENES})
        get_filename_component(NAME ${SCENE} NAME_WE)
        string(TOLOWER ${NAME} NAME)
        add_library(raytracer_scene_loader_${NAME} SHARED ${SCENE})
        set_target_properties(raytracer_scene_loader_${NAME} PROPERTIES PREFIX "")
        target_include_directories(raytracer_scene_loader_${NAME} PUBLIC
                ${CMAKE_SOURCE_DIR}/include/Scene-loader/
                ${LIBCONFIGPP_INCLUDE_DIRS}
        )
        target_compile_options(raytracer_scene_loader_${NAME} PRIVATE -Wall -Wextra -Werror -O3)
        set_target_properties(raytracer_scene_loader_${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
        target_link_libraries(raytracer_scene_loader_${NAME} PUBLIC raytracer_scene_loader ${LIBCONFIGPP_LIBRARIES})
    endforeach()
endif()
###############################################################################



############################ INTERFACE ########################################
# For common interface needs
file(GLOB COMMON "src/Interface/common/*.cpp")
add_library(raytracer_interface SHARED ${COMMON})
set_target_properties(raytracer_interface PROPERTIES PREFIX "")
target_include_directories(raytracer_interface PUBLIC
        ${CMAKE_SOURCE_DIR}/include/Interface/common
)
target_compile_options(raytracer_interface PUBLIC -Wall -Wextra -Werror -O3)
set_target_properties(raytracer_interface PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
target_link_libraries(raytracer_interface PUBLIC my)

# For each interfaces
file(GLOB FINAL_INTERFACES "src/Interface/*.cpp")
foreach(INTERFACE ${FINAL_INTERFACES})
    get_filename_component(NAME ${INTERFACE} NAME_WE)
    string(TOLOWER ${NAME} NAME)
    add_library(raytracer_interface_${NAME} SHARED ${INTERFACE})
    set_target_properties(raytracer_interface_${NAME} PROPERTIES PREFIX "")
    target_include_directories(raytracer_interface_${NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/Interface/)
    target_compile_options(raytracer_interface_${NAME} PUBLIC -Wall -Wextra -Werror -O3)
    set_target_properties(raytracer_interface_${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
    target_link_libraries(raytracer_interface_${NAME} PUBLIC raytracer_interface)
    if (${NAME} STREQUAL "sfml")
        find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
        target_link_libraries(raytracer_interface_${NAME} PUBLIC my)
        target_link_libraries(raytracer_interface_${NAME} PRIVATE sfml-graphics)
    endif()
endforeach()
###############################################################################



############################ DEBUG MODE #######################################
OPTION(DEBUG_MODE "Option to build in debugging mode" OFF)

function(get_all_targets out_var)
    set(targets)
    get_all_targets_recursive(targets "${CMAKE_CURRENT_SOURCE_DIR}")
    set(${out_var} ${targets} PARENT_SCOPE)
endfunction()

function(get_all_targets_recursive targets_var dir)
    get_property(subdirectories DIRECTORY "${dir}" PROPERTY SUBDIRECTORIES)
    foreach(subdir IN LISTS subdirectories)
        get_all_targets_recursive("${targets_var}" "${subdir}")
    endforeach()

    get_property(current_targets DIRECTORY "${dir}" PROPERTY BUILDSYSTEM_TARGETS)
    set(${targets_var} ${${targets_var}} ${current_targets} PARENT_SCOPE)
endfunction()

get_all_targets(ALL_TARGETS)

if (DEBUG_MODE)
    message(STATUS "Debug mode enabled")
    foreach(target ${ALL_TARGETS})
        get_target_property(target_type ${target} TYPE)
        if(target_type STREQUAL "EXECUTABLE" OR
        target_type STREQUAL "STATIC_LIBRARY" OR
        target_type STREQUAL "SHARED_LIBRARY")
            target_compile_definitions(${target} PRIVATE -DDEBUG_MODE)
            target_compile_options(${target} PRIVATE -g3 -O3)
        endif()
    endforeach()
endif()
###############################################################################



############################ CLEAN ALL ########################################
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/*
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME}
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins/*
    COMMENT "Cleaning all build files"
)
###############################################################################



############################ DOCUMENTATION ####################################
find_package(Doxygen QUIET)

if(DOXYGEN_FOUND)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating documentation with Doxygen"
    )
else()
    add_custom_target(doc
        COMMAND ${CMAKE_COMMAND} -E echo "Doxygen not found, documentation will not be generated"
    )
endif()
###############################################################################