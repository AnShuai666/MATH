include_directories(../../include)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(HEADERS
        ${PROJECT_SOURCE_DIR}/include/Matrix/define.h
        ${PROJECT_SOURCE_DIR}/include/Matrix/matrix.hpp
        )
set(SOURCE_FILES

        a.cpp)

add_library(matrix_base SHARED ${HEADERS} ${SOURCE_FILES})