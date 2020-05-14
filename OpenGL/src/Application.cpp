#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    // Initialize GLFW library.
    if (!glfwInit())
        return -1;

    // Configure GLFW.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window and valid OpenGL context.
    GLFWwindow* window = glfwCreateWindow(680, 480, "Ignite", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Set window callbacks.
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    // Make context current.
    glfwMakeContextCurrent(window);

    // Initialize glad.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    // Set buffer swap interval.
    glfwSwapInterval(1);

    // Render Loop.
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
