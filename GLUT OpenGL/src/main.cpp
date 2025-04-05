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


struct ShaderProgramSource{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string &filepath) {
    std::ifstream stream(filepath);
    
    // Check if file opened successfully
    if (!stream.is_open()) {
        std::cerr << "ERROR: Could not open shader file: " << filepath << std::endl;
        return {"", ""};
    }
    
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    
    ShaderType type = ShaderType::NONE;
    std::string line;
    std::stringstream ss[2];
    
    while(getline(stream, line)) {
        if(line.find("#shader") != std::string::npos) {
            if(line.find("vertex") != std::string::npos) {
                // Set mode to vertex
                type = ShaderType::VERTEX;
                std::cout << "Found vertex shader section" << std::endl;
            }
            else if(line.find("fragment") != std::string::npos) {
                // Set mode to fragment
                type = ShaderType::FRAGMENT;
                std::cout << "Found fragment shader section" << std::endl;
            }
        }
        else {
            if (type != ShaderType::NONE) {
                ss[(int)type] << line << '\n';
            }
        }
    }
    
    // Check if shaders were found
    if (ss[0].str().empty()) {
        std::cerr << "WARNING: No vertex shader found in file: " << filepath << std::endl;
    }
    if (ss[1].str().empty()) {
        std::cerr << "WARNING: No fragment shader found in file: " << filepath << std::endl;
    }
    
    return {ss[0].str(), ss[1].str()};
}

static unsigned int compileShader(unsigned int type, const std::string& source){
    unsigned int id =  glCreateShader(type);
    const char* src = source.c_str(); // src is a pointer to the first character of the source string
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader!" <<
                (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    
    return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string fragmentShader){
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

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
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f,
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    // Creating and binding the buffer
    VertexArray* va = new VertexArray();
    VertexBuffer* vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout layout;
    
    layout.push<float>(2);
    va->addBuffer(*vb, layout);


    
    IndexBuffer* ib = new IndexBuffer(indices, 6);
    
    ShaderProgramSource source;
    source = ParseShader("/Users/tuanminh/Documents/Scribbling/GLUT OpenGL/GLUT OpenGL/res/shaders/basic.shader");
    
    std::cout << "VERTEX" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "FRAGMENT" << std::endl;
    std::cout << source.FragmentSource << std::endl;
    
    unsigned int shader = createShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);
    
    GLCall(int location = glGetUniformLocation(shader, "u_Color"));
    ASSERT(location != -1);
    GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));
    
    glfwSwapInterval(1);
    
    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shader);
        GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
        
        va->bind();
        ib->bind();
        
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        

        
        if(r > 1.0f) increment = -0.05f;
        else if (r < 0.0f) increment = 0.05f;
        
        r += increment;
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    delete vb;
    delete ib;
    glDeleteProgram(shader);
    
    glfwTerminate();
    return 0;
}
