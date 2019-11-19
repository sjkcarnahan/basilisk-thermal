cmake_minimum_required(VERSION 3.12)
if(POLICY CMP0025)
    cmake_policy(SET CMP0025 NEW)
endif()
if(POLICY CMP0042)
    cmake_policy(SET CMP0025 NEW)
endif()
if(POLICY CMP0046)
    cmake_policy(SET CMP0046 NEW)
endif()
if(POLICY CMP0068)
    cmake_policy(SET CMP0068 NEW)
endif()
if(POLICY CMP0076)
    cmake_policy(SET CMP0078 NEW)
endif()
if(POLICY CMP0078)
    cmake_policy(SET CMP0078 NEW)
endif()
if(POLICY CMP0086)
    cmake_policy(SET CMP0086 NEW)
endif()
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Building Release."
            FORCE)
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

project(basilisk-thermal
        VERSION 0.0.0
        DESCRIPTION "thermal package for basilisk"
        HOMEPAGE_URL "my github page"
        LANGUAGES CXX)
find_package(BSK REQUIRED)
#find_package (Eigen3 3.3 REQUIRED NO_MODULE)
set(sources
        models/thermalConductor.cpp
        models/thermalMass.cpp
        models/thermalEmitter.cpp)
add_library(basilisk-thermal SHARED
        ${sources})
get_target_property(framework_include BSK::basilisk-framework INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(basilisk-thermal
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${framework_include}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(basilisk-thermal BSK::basilisk-framework)
#target_link_libraries(basilisk-thermal Eigen3::Eigen)

include(FindSWIG)
include(UseSWIG)
find_package(PythonLibs 3 REQUIRED)
find_package(PythonInterp ${PYTHONLIBS_VERSION_STRING} REQUIRED)
set_source_files_properties(SOURCE include/thermal/thermal.i
        PROPERTIES
        CPLUSPLUS ON
        USE_TARGET_INCLUDE_DIRECTORIES TRUE)
SWIG_ADD_LIBRARY(thermal
        LANGUAGE python
        TYPE MODULE
        SOURCES include/thermal/thermal.i)
swig_link_libraries(thermal basilisk-thermal)
swig_link_libraries(thermal ${PYTHON_LIBRARIES})
swig_link_libraries(thermal BSK::basilisk-framework)
include_directories(thermal ${PYTHON_INCLUDE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/include )
set(PYTHON_INSTALL_FILES
        ${CMAKE_CURRENT_BINARY_DIR}/thermal.py
        ${CMAKE_CURRENT_BINARY_DIR}/_thermal.so)
set(SETUP_PY_IN ${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in)
set(SETUP_PY_OUT ${CMAKE_CURRENT_BINARY_DIR}/setup.py)
configure_file(${SETUP_PY_IN} ${SETUP_PY_OUT})
add_custom_target(install-python ALL
        DEPENDS thermal
        COMMAND python3 ${SETUP_PY_OUT} install)

