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
add_executable(RayTracer main.cpp include/Image.h thirdParty/Vec3.h src/Scene.cpp include/Scene.h src/Ray.cpp include/Ray.h src/Camera.cpp include/Camera.h src/RayCaster.cpp include/RayCaster.h src/Mesh.cpp include/Mesh.h src/LightSource.cpp include/LightSource.h src/Material.cpp include/Material.h src/AreaLightSource.cpp include/AreaLightSource.h include/Random.h)