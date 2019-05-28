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

add_library(util SHARED ${HEADERS} ${SOURCE_FILES})
target_link_libraries(util function)
install(TARGETS util
        LIBRARY DESTINATION lib/MATH
        ARCHIVE DESTINATION lib/MATH
        RUNTIME DESTINATION bin/MATH
        )