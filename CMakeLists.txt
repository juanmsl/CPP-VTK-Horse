cmake_minimum_required(VERSION 2.8)

PROJECT(VTK_BUMP)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(LIBRARIES
        libs/horse.cxx
        libs/scene.cxx
        libs/shapes/shape.cxx
        libs/shapes/shapesource.cxx
        libs/shapes/booleanunion.cxx
        libs/shapes/shapes.cxx
        libs/shapes/implicitunion.cxx
        )

add_executable(bump MACOSX_BUNDLE main.cxx ${LIBRARIES} paramsmanager.cxx)

target_link_libraries(bump ${VTK_LIBRARIES})
