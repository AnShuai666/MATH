include_directories(../../include)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(C_SOURCES flann.cpp)
set(CPP_SOURCES flann_cpp.cpp)

add_library(flann SHARED ${CPP_SOURCES})

#if (0)
#    add_library(flann_s STATIC ${C_SOURCES})
#    add_library(flann SHARED ${C_SOURCES})
#endif()

install(TARGETS flann
        LIBRARY DESTINATION lib/MATH/flann
        ARCHIVE DESTINATION lib/MATH/flann
        RUNTIME DESTINATION bin/MATH/flann
        )
install (
        DIRECTORY flann
        DESTINATION include/MATH/flann
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)