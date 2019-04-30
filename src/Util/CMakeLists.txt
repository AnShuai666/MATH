include_directories(../../include/MATH)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(HEADERS
        ../../include/MATH/Util/define.h
        ../../include/MATH/Util/system.h
        ../../include/MATH/Util/file_system.h
        ../../include/MATH/Util/logging.h
        ../../include/MATH/Util/aligned_allocator.hpp
        ../../include/MATH/Util/ArgParser.h
        ../../include/MATH/Util/string.h
        ../../include/MATH/Util/exception.h
        ../../include/MATH/Util/timer.h
        ../../include/MATH/Util/tokenizer.h)
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