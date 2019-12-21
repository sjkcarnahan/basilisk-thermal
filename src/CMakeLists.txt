cmake_minimum_required(VERSION 3.12)
if(POLICY CMP0078)
    cmake_policy(SET CMP0078 NEW)
endif()
if(POLICY CMP0086)
    cmake_policy(SET CMP0086 NEW)
endif()

include(FindSWIG)
include(UseSWIG)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

project(basilisk-thermal
    VERSION 0.0.0
    DESCRIPTION "thermal package for basilisk"
    HOMEPAGE_URL "https://github.com/sjkcarnahan/basilisk-thermal"
    LANGUAGES CXX)

set(module_name thermal)
set(package_name basilisk)

find_package(Python3 COMPONENTS Interpreter NumPy) # we typemap eigen to and from numpy
find_package(Eigen3 3.3 REQUIRED NO_MODULE) # we typemap eigen to and from numpy
find_package(BSK REQUIRED)
find_package(BSKDynamics REQUIRED)
find_package(BSKEnvironment REQUIRED)
find_package(BSKNavigation REQUIRED)

# Need other basilisk package include directories to interface custom types
get_target_property(framework_include BSK::${package_name}-framework INTERFACE_INCLUDE_DIRECTORIES)  # this one also needed for linking to utilities
get_target_property(dynamics_include BSK::${package_name}-dynamics INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(environment_include BSK::${package_name}-environment INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(navigation_include BSK::${package_name}-navigation INTERFACE_INCLUDE_DIRECTORIES)
set(${package_name}_includes ${framework_include} ${dynamics_include} ${environment_include} ${navigation_include})

# make the extension library
add_library(${package_name}-${module_name} 
    SHARED
        models/ArithmeticSurface.cpp
        models/BetaAngle.cpp
        models/FluxHeating.cpp
        models/HeatPath.cpp
        models/HeatSource.cpp
        models/ThermalConductor.cpp
        models/ThermalEmitter.cpp
        models/ThermalMass.cpp
        models/NetworkConductor.cpp
        models/NetworkEmitter.cpp
        models/NetworkMass2.cpp
        models/NetworkRadiationConductor.cpp
        models/NetworkSolver.cpp
        models/SolarAngle.cpp)
target_include_directories(${package_name}-${module_name}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${${package_name}_includes}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${package_name}-${module_name} BSK::${package_name}-framework)


# make the swig library
set_source_files_properties(
    SOURCE include/${module_name}/${module_name}.i
    PROPERTIES CPLUSPLUS ON
    USE_TARGET_INCLUDE_DIRECTORIES TRUE)
swig_add_library(${module_name}
    LANGUAGE python
    TYPE MODULE
    SOURCES include/${module_name}/${module_name}.i)
swig_link_libraries(${module_name} 
    ${package_name}-${module_name} 
    ${Python3_LIBRARIES})
include_directories(${module_name}
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${Python3_INCLUDE_DIRS}
    ${Python3_NumPy_INCLUDE_DIRS}
    ${${package_name}_includes})
    
# install python module
set(SETUP_PY_OUT ${CMAKE_CURRENT_BINARY_DIR}/setup.py)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in ${SETUP_PY_OUT})
add_custom_target(install-python ALL
    DEPENDS ${module_name}
    COMMAND Python3::Interpreter ${SETUP_PY_OUT} install)

# export as a cmake package that can be found
export(TARGETS ${package_name}-${module_name} 
    NAMESPACE BSK:: 
    FILE BSKThermalConfig.cmake)
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
export(PACKAGE BSKThermal)