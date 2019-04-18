include_directories(../../include)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(HEADERS
        ${PROJECT_SOURCE_DIR}/include/util/define.h
        ${PROJECT_SOURCE_DIR}/include/util/system.h
        ${PROJECT_SOURCE_DIR}/include/util/file_system.h
        ${PROJECT_SOURCE_DIR}/include/util/logging.h


        )
set(SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/util/system.cpp
        ${PROJECT_SOURCE_DIR}/src/util/file_system.cpp
        ${PROJECT_SOURCE_DIR}/src/util/logging.cpp
        )

add_library(math_util SHARED ${HEADERS} ${SOURCE_FILES})
target_link_libraries(math_util function)
install(TARGETS math_util
        LIBRARY DESTINATION lib/MATH/util
        ARCHIVE DESTINATION lib/MATH/util
        RUNTIME DESTINATION bin/MATH/util
        )
install(FILES ${HEADERS}
        DESTINATION include/MATH/util)