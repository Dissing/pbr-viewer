#include <stdio.h>

#include <GLFW/glfw3.h>

#include "common.h"

static struct State { GLFWwindow* window; } state;

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

void startup_windowing() {
    glfwSetErrorCallback(glfw_error_callback);
    ASSERT(glfwInit());

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    state.window = glfwCreateWindow(1280, 720, "Model Viewer", nullptr, nullptr);
    ASSERT(state.window);
}

void shutdown_windowing() {
    glfwTerminate();
}

void startup() {
    startup_windowing();
}

void shutdown() {
    shutdown_windowing();
}

void main_loop() {
    while (!glfwWindowShouldClose(state.window)) { glfwPollEvents(); }
}

int main(int argc, const char** argv) {
    startup();
    main_loop();
    shutdown();

    return 0;
}
