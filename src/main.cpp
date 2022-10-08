#include <stdio.h>

// clang-format off
// glad must be imported prior to GLFW
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include "common.h"

static struct State { GLFWwindow* window; } state;

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

void windowing_startup() {
    glfwSetErrorCallback(glfw_error_callback);
    ASSERT(glfwInit());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    state.window = glfwCreateWindow(1280, 720, "PBR Viewer", nullptr, nullptr);
    ASSERT(state.window);
}

void windowing_shutdown() {
    glfwTerminate();
}

void GLAPIENTRY gl_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                    GLsizei length, const GLchar* message, const void* userParam) {
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

void swapchain_resize() {
    int width, height;
    glfwGetWindowSize(state.window, &width, &height);
    glViewport(0, 0, width, height);
}

void swapchain_create() {
    glfwMakeContextCurrent(state.window);
    int version = gladLoadGL((GLADloadfunc) glfwGetProcAddress);
    ASSERT(version);
    printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(gl_message_callback, 0);

    swapchain_resize();
}

void swapchain_present() {
    glfwSwapBuffers(state.window);
}

void imgui_startup() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void) io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(state.window, true);
    ImGui_ImplOpenGL3_Init();
}

void imgui_prepare() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void imgui_submit() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void render_startup() {
    swapchain_create();
    imgui_startup();
}

void render_prepare() {
    glClearColor(0.45, 0.55, 0.60, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    imgui_prepare();
}

void startup() {
    windowing_startup();
    render_startup();
}

void shutdown() {
    windowing_shutdown();
}

void main_loop() {
    while (!glfwWindowShouldClose(state.window)) {
        glfwPollEvents();
        render_prepare();

        bool show = true;
        ImGui::ShowDemoWindow(&show);

        imgui_submit();
        swapchain_present();
    }
}

int main(int argc, const char** argv) {
    startup();
    main_loop();
    shutdown();

    return 0;
}
