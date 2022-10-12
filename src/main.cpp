#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <Windows.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    if(!glfwInit()) {
        spdlog::error("Unable to initialize GLFW");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    auto window = glfwCreateWindow(1024, 728, "cleanNES", nullptr, nullptr);
    if(!window) {
        spdlog::error("Unable to create GLFW window");
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::error("Unable to load OpenGL bindings");
        return -1;
    }

    while(!glfwWindowShouldClose(window)) {
        int w,h;

        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0,0,w,h);
        glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}