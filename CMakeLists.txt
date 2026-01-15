# =============================================================================
# Planet Donut Simulation - CMake Build Configuration
# =============================================================================
# Authors: Daniel Abraham Elmaleh, Imane Jennane
# Date: May 2021
# Institution: EPFL
# =============================================================================

cmake_minimum_required(VERSION 3.10)

project(PlanetDonut
    VERSION 1.0
    DESCRIPTION "2D Robot Resource Gathering Simulation"
    LANGUAGES CXX
)

# =============================================================================
# C++ Standard Configuration
# =============================================================================

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =============================================================================
# Compiler Flags
# =============================================================================

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# =============================================================================
# Find GTKmm 3.0
# =============================================================================

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
add_definitions(${GTKMM_CFLAGS_OTHER})

# =============================================================================
# Source Files
# =============================================================================

set(SOURCES
    src/projet.cc
    src/simulation.cc
    src/base.cc
    src/robot.cc
    src/gisement.cc
    src/geomod.cc
    src/gui.cc
    src/graphic.cc
    src/message.cc
)

set(HEADERS
    include/simulation.h
    include/base.h
    include/robot.h
    include/gisement.h
    include/geomod.h
    include/gui.h
    include/graphic.h
    include/graphic_gui.h
    include/constantes.h
    include/message.h
)

# =============================================================================
# Include Directories
# =============================================================================

include_directories(${CMAKE_SOURCE_DIR}/include)

# =============================================================================
# Executable
# =============================================================================

add_executable(projet ${SOURCES} ${HEADERS})

target_link_libraries(projet ${GTKMM_LIBRARIES})

# =============================================================================
# Installation (Optional)
# =============================================================================

install(TARGETS projet DESTINATION bin)
