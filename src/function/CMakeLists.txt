include_directories(../../include)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(HEADERS
        ${PROJECT_SOURCE_DIR}/include/function/define.h
        ${PROJECT_SOURCE_DIR}/include/function/function.hpp
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