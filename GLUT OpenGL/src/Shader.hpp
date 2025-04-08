//
//  Shader.hpp
//  GLUT OpenGL
//
//  Created by tuan minh on 8/4/25.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <unordered_map>


struct ShaderProgramSource{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader{
    private:
    
        std::string filepath;
        unsigned int renderer_id;
        std::unordered_map<std::string, int> uniformLocationCache;
    
        int getUniformLocation(const std::string& name);
        unsigned int createShader(const std::string& vertexShader, const std::string fragmentShader);
        unsigned int compileShader(unsigned int type, const std::string& source);
        ShaderProgramSource ParseShader(const std::string &filepath);
        bool compileShader();
    public:
    Shader(const std::string& filename);
    ~Shader();
    
    void bind() const;
    void unbind() const;
    
    // Set uniforms
    void setUniform1i(const std::string& name, int value);
    void setUniform1f(const std::string& name, float value);
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
};



#endif /* Shader_hpp */
