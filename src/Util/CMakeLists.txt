include_directories(../../include)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(HEADERS
        ${PROJECT_SOURCE_DIR}/include/Util/define.h
        ${PROJECT_SOURCE_DIR}/include/Util/system.h
        ${PROJECT_SOURCE_DIR}/include/Util/file_system.h
        ${PROJECT_SOURCE_DIR}/include/Util/logging.h
        ${PROJECT_SOURCE_DIR}/include/Util/aligned_allocator.hpp
        ${PROJECT_SOURCE_DIR}/include/Util/ArgParser.h
        ${PROJECT_SOURCE_DIR}/include/Util/string.h
        ${PROJECT_SOURCE_DIR}/include/Util/exception.h
        ${PROJECT_SOURCE_DIR}/include/Util/timer.h
        ../../include/Util/tokenizer.h)
set(SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/Util/system.cpp
        ${PROJECT_SOURCE_DIR}/src/Util/file_system.cpp
        ${PROJECT_SOURCE_DIR}/src/Util/ArgParser.cpp
        ${PROJECT_SOURCE_DIR}/src/Util/string.cpp
        )

add_library(math_util SHARED ${HEADERS} ${SOURCE_FILES})
target_link_libraries(math_util function)
install(TARGETS math_util
        LIBRARY DESTINATION lib/MATH/Util
        ARCHIVE DESTINATION lib/MATH/Util
        RUNTIME DESTINATION bin/MATH/Util
        )
install(FILES ${HEADERS}
        DESTINATION include/MATH/Util)