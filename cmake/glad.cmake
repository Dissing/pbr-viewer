add_subdirectory(${DEPENDS_DIR}/glad/cmake ${CMAKE_BINARY_DIR}/depends/glad)
glad_add_library(glad_gl_core_46 STATIC REPRODUCIBLE API gl:core=4.6)
target_link_libraries(viewer glad_gl_core_46)
