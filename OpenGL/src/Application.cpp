#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vendor/stb_image.h"

#include <iostream>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "DebugUtils.h"
#include "Shader.h"
#include "Texture.h"

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
        // Positions.           // Colors                   // Texture coordinates
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 0.0f,
         0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 1.0f, 1.0f,     0.0f, 1.0f,
    };

    // Index data.
    unsigned int indices[] =
    {
        0, 1, 2,
        0, 2, 3,
    };

    {
        VertexBuffer vb(vertices, 4 * 9 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);  // position
        layout.Push<float>(4);  // color
        layout.Push<float>(2);  // texture coordinate

        IndexBuffer ib(indices, 6);
        ib.Unbind();

        VertexArray va;
        va.AddBuffer(vb, layout);
        va.Unbind();

        Shader shader("res/shaders/source.shader");
        shader.Bind();

        unsigned int texture1;
        glGenTextures(1, &texture1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
        int width1, height1, nrChannels1;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* textureData1 = stbi_load("res/textures/img1.jpg", &width1, &height1, &nrChannels1, 0);
        ASSERT(textureData1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData1);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(textureData1);
        shader.SetUniform("u_texture1", 0);

        unsigned int texture2;
        glGenTextures(1, &texture2);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
        int width2, height2, nrChannels2;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* textureData2 = stbi_load("res/textures/img2.jpg", &width2, &height2, &nrChannels2, 0);
        ASSERT(textureData2);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData2);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(textureData2);
        shader.SetUniform("u_texture2", 1);

       
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        Renderer renderer;

        // Render Loop.
        while (!glfwWindowShouldClose(window))
        {
            ProcessInput(window);
            renderer.Clear();
            
            
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
