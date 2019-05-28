
include_directories(../../include)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(HEADERS
        ../../include/MATH/Function/define.h
        ../../include/MATH/Function/function.hpp
        ../../include/MATH/Function/algorithm.hpp
        )
set(SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/Function/a.cpp
        )

add_library(function SHARED ${HEADERS} ${SOURCE_FILES})

install(TARGETS function
        LIBRARY DESTINATION lib/MATH
        ARCHIVE DESTINATION lib/MATH
        RUNTIME DESTINATION bin/MATH
        )
