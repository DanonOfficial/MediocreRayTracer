cmake_minimum_required(VERSION 3.17)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenMP)
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual")

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
add_executable(RayTracer main.cpp Image.h thirdParty/Vec3.h Scene.cpp Scene.h Ray.cpp Ray.h Camera.cpp Camera.h RayCaster.cpp RayCaster.h Mesh.cpp Mesh.h)