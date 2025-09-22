cmake_minimum_required(VERSION 3.10)
project(MiProyectoCXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Agrega todos los archivos fuente de tu proyecto
file(GLOB SOURCES
    ../Codigo/C++/*/*.cpp
)

add_executable(MiEjecutable ${SOURCES})

# Si usas SFML, agrega esto:
find_package(SFML 3.0 COMPONENTS graphics window system REQUIRED)
target_link_libraries(MiEjecutable sfml-graphics sfml-window sfml-system)

# Si tienes otros includes, agrégalos aquí
target_include_directories(MiEjecutable PRIVATE ../Codigo/C++)

# Opcional: para mostrar más información de compilación
set(CMAKE_VERBOSE_MAKEFILE ON)