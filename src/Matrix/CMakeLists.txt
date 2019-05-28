include_directories(../../include)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(HEADERS
        ${PROJECT_SOURCE_DIR}/include/Matrix/define.h
        ${PROJECT_SOURCE_DIR}/include/Matrix/matrix.hpp
        ${PROJECT_SOURCE_DIR}/include/Matrix/vector.hpp
        ${PROJECT_SOURCE_DIR}/include/Matrix/algorithm_base.h
        ${PROJECT_SOURCE_DIR}/include/Matrix/matrix_cholesky.hpp
        ${PROJECT_SOURCE_DIR}/include/Matrix/matrix_qr.hpp
        ${PROJECT_SOURCE_DIR}/include/Matrix/matrix_svd.hpp
        ${PROJECT_SOURCE_DIR}/include/Matrix/matrix_conjugate_gradient.hpp

        )
set(SOURCE_FILES
        matrix_LU.cpp
        )

add_library(matrix_LU SHARED ${HEADERS} ${SOURCE_FILES})
target_link_libraries(matrix_LU function)
install(TARGETS matrix_LU
        LIBRARY DESTINATION lib/MATH/Matrix
        ARCHIVE DESTINATION lib/MATH/Matrix
        RUNTIME DESTINATION bin/MATH/Matrix
        )
install(FILES ${HEADERS}
        DESTINATION include/MATH/Matrix)