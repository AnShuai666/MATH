include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(../../include)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(HEADERS
        ../../include/MATH/function/define.h
        ../../include/MATH/function/function.hpp
        ../../include/MATH/function/algorithm.hpp
        )
set(SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/function/a.cpp
        )

add_library(function SHARED ${HEADERS} ${SOURCE_FILES})

install(TARGETS function
        LIBRARY DESTINATION lib/MATH/function
        ARCHIVE DESTINATION lib/MATH/function
        RUNTIME DESTINATION bin/MATH/function
        )

install(FILES ${HEADERS}
        DESTINATION include/MATH/function)