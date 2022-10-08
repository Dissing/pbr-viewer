set(IMGUI_PATH ${DEPENDS_DIR}/imgui)
set(IMGUI_SRCS
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
    ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(viewer PUBLIC ${IMGUI_PATH})
target_sources(viewer PRIVATE ${IMGUI_SRCS})
