
cmake_minimum_required(VERSION 2.8 )
project(MATH)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fPIC")
set(CMAKE_BUILD_TYPE "Debug")

set(MATH_VERSION_MAJOR 1)
set(MATH_VERSION_MINOR 0)
set(MATH_VERSION_PATCH 0)
set(MATH_VERSION ${MATH_VERSION_MAJOR}.${MATH_VERSION_MINOR}.${MATH_VERSION_PATCH})
message("当前MATH版本为:${MATH_VERSION}")
find_package(CUDA QUIET)
if (CUDA_FOUND)
    set(CUDA_ENABLED true)
endif ()

configure_file(
        "${PROJECT_SOURCE_DIR}/config/MATHConfig.h.in"
        "include/MATH/MATHConfig.h"
)

configure_file(
        "${PROJECT_SOURCE_DIR}/config/MATHConfig.cmake.in"
        "${PROJECT_SOURCE_DIR}/cmakemodule/MATHConfig.cmake" @ONLY
)
set_property(TARGET ${MATHConfig.cmake} PROPERTY FOLDER cmakemodule)

configure_file(
        "${PROJECT_SOURCE_DIR}/config/MATHConfigVersion.cmake.in"
        "${PROJECT_SOURCE_DIR}/cmakemodule/MATHConfigVeision.cmake" @ONLY
)

install(FILES MATHConfig.cmake
        DESTINATION share/MATH)
install(FILES MATHConfigVersion.cmake
        DESTINATION share/MATH)


add_subdirectory(examples)
add_subdirectory(src)


install(FILES MATHConfig.h include/MATH/math_define.h
        DESTINATION include/MATH)