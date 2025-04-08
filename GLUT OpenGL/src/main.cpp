//
//  main.cpp
//  GLUT OpenGL
//
//  Created by tuan minh on 25/3/25.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

#include "renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "VertexBufferLayout.hpp"
#include "Texture.hpp"



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      #ifdef __APPLE__
        std::cout << "I'm apple machine" << std::endl;
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      #endif

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    unsigned int major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    unsigned int minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    std::cout << "oepngl shader version: " << major << "." << minor << std::endl;
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    if(glewInit()!=GLEW_OK){
        return -1;
    }
    
    std::cout << glGetString(GL_VERSION) << std::endl;
    
    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, // Bottom-left
        0.5f, -0.5f, 1.0f, 0.0f, // Bottom-right
        0.5f, 0.5f, 1.0f, 1.0f, // Top-right
        -0.5f, 0.5f, 0.0f, 1.0f // Top-Left
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    // Creating and binding the buffer
    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    
    layout.push<float>(2); // Vertex position buffer has 2 float (per position)
    layout.push<float>(2); // Texture position buffer has 2 float (idem)
    va.addBuffer(vb, layout);


    
    IndexBuffer ib(indices, 6);
    
    Shader shader("/Users/tuanminh/Documents/Scribbling/GLUT OpenGL/GLUT OpenGL/res/shaders/basic.shader");
    
    shader.bind();
    shader.setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    shader.unbind();
    
    Texture texture("/Users/tuanminh/Documents/Scribbling/GLUT OpenGL/GLUT OpenGL/res/textures/grass.jpg");
    texture.bind(); // Default slot is 0
    shader.setUniform1i("u_Texture", 0); // Matches the slot of the texture
    
    va.unbind();
    vb.unbind();
    ib.unbind();
    
    Renderer renderer;
    
    
    glfwSwapInterval(1);
    
    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();
        
        shader.bind();
        shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        
        va.bind();
        ib.bind();
        
        renderer.draw(va, ib, shader);

        
        if(r > 1.0f) increment = -0.05f;
        else if (r < 0.0f) increment = 0.05f;
        
        r += increment;
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
