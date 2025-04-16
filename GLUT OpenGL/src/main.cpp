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

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <imgui/imgui.h>
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"


int main(void)
{
    GLFWwindow* window;
    
    const char* glsl_version = "#version 410"; 

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
    window = glfwCreateWindow(960, 480, "Hello World", NULL, NULL);
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
        100.f, 100.f, 0.0f, 0.0f, // Bottom-left
        200.f, 100.f, 1.0f, 0.0f, // Bottom-right
        200.f, 200.f, 1.0f, 1.0f, // Top-right
        100.f, 200.f, 0.0f, 1.0f // Top-Left
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
    
    glm::mat4 proj = glm::ortho(0.f, 960.0f, 0.f, 540.f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
    
    glm::mat4 mvp = proj * view * model;
    Shader shader("/Users/tuanminh/Documents/Scribbling/GLUT OpenGL/GLUT OpenGL/res/shaders/basic.shader");
    
    shader.bind();
    shader.setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    shader.setUniformMat4f("u_MVP", mvp);
    shader.unbind();
    
    Texture texture("/Users/tuanminh/Documents/Scribbling/GLUT OpenGL/GLUT OpenGL/res/textures/grass.jpg");
    texture.bind(); // Default slot is 0
    shader.setUniform1i("u_Texture", 0); // Matches the slot of the texture
    
    va.unbind();
    vb.unbind();
    ib.unbind();
    
    Renderer renderer;
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup Platform/Renderer backends

    glfwSwapInterval(1);
    
    float r = 0.0f;
    float increment = 0.05f;
    
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();
        
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        shader.bind();
        shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        
        va.bind();
        ib.bind();
        
        renderer.draw(va, ib, shader);

        
        if(r > 1.0f) increment = -0.05f;
        else if (r < 0.0f) increment = 0.05f;
        
        r += increment;
        
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
