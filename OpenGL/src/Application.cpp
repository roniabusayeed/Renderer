#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "DebugUtils.h"
#include "Shader.h"

#include "Renderer.h"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

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

    // Vertex data.
    float vertices[] =
    {
        // Positions.
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    // Index data.
    unsigned int indices[] =
    {
        0, 1, 2,
        0, 2, 3,
    };

    {
        VertexBuffer vb(vertices, 4 * 3 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);

        IndexBuffer ib(indices, 6);
        ib.Unbind();

        VertexArray va;
        va.AddBuffer(vb, layout);
        va.Unbind();

        Shader shader("res/shaders/source.shader");
        shader.Bind();

        Renderer renderer;

        // Render Loop.
        while (!glfwWindowShouldClose(window))
        {
            ProcessInput(window);
            renderer.Clear();

            // Set uniform value dynamically.
            float greenValue = sin(glfwGetTime() * 3) / 2 + 0.5f;
            shader.SetUniform("u_greenValue", greenValue);
            
            renderer.Draw(va, ib, shader);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    GLCall(glViewport(0, 0, width, height));
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
