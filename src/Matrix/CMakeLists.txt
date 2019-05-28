#include_directories(../../include/MATH)
include_directories(../../include/)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(HEADERS
        ../../include/MATH/Matrix/define.h
        ../../include/MATH/Matrix/matrix.hpp
        ../../include/MATH/Matrix/vector.hpp
        ../../include/MATH/Function/algorithm.hpp
        ../../include/MATH/Matrix/matrix_cholesky.hpp
        ../../include/MATH/Matrix/matrix_qr.hpp
        ../../include/MATH/Matrix/matrix_svd.hpp
        ../../include/MATH/Matrix/matrix_conjugate_gradient.hpp
        ../../include/MATH/math_define.h
        )
set(SOURCE_FILES
        matrix_LU.cpp
        )

add_library(matrix SHARED ${HEADERS} ${SOURCE_FILES})
target_link_libraries(matrix function)
install(TARGETS matrix
        LIBRARY DESTINATION lib/MATH
        ARCHIVE DESTINATION lib/MATH
        RUNTIME DESTINATION bin/MATH
        )
