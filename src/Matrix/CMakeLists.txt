include_directories(../../include/MATH)
include_directories(../../include/)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(HEADERS
        ../../include/MATH/Matrix/define.h
        ../../include/MATH/Matrix/matrix.hpp
        ../../include/MATH/Matrix/vector.hpp
        ../../include/MATH/Matrix/algorithm_base.h
        ../../include/MATH/Matrix/matrix_cholesky.hpp
        ../../include/MATH/Matrix/matrix_qr.hpp
        ../../include/MATH/Matrix/matrix_svd.hpp
        ../../include/MATH/Matrix/matrix_conjugate_gradient.hpp
        ../../include/MATH/math_define.h
        )
set(SOURCE_FILES
        a.cpp
        )

add_library(matrix_base SHARED ${HEADERS} ${SOURCE_FILES})
target_link_libraries(matrix_base function)
install(TARGETS matrix_base
        LIBRARY DESTINATION lib/MATH/Matrix
        ARCHIVE DESTINATION lib/MATH/Matrix
        RUNTIME DESTINATION bin/MATH/Matrix
        )
install(FILES ${HEADERS}
        DESTINATION include/MATH/Matrix)