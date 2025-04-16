//
//  Shader.cpp
//  GLUT OpenGL
//
//  Created by tuan minh on 8/4/25.
//

#include "Shader.hpp"
#include "renderer.hpp"



Shader::Shader(const std::string& filepath):filepath(filepath), renderer_id(0){
    ShaderProgramSource source = ParseShader(filepath);
    renderer_id = createShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader(){
    glDeleteProgram(renderer_id);
}

void Shader::bind() const{
    glUseProgram(renderer_id);
}

void Shader::unbind() const{
    glUseProgram(0);
}

void Shader::setUniform1i(const std::string& name, int value){
    int loc = getUniformLocation(name);
    glUniform1i(loc, value);
}
void Shader::setUniform1f(const std::string& name, float value){
    int loc = getUniformLocation(name);
    glUniform1f(loc, value);
}

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3){
    int loc = getUniformLocation(name);
    glUniform4f(loc, v0, v1, v2, v3);
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix){
    int loc = getUniformLocation(name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
}

int Shader::getUniformLocation(const std::string &name){
    if(uniformLocationCache.find(name) != uniformLocationCache.end()){
        return uniformLocationCache[name];
    }
    int loc = glGetUniformLocation(renderer_id, name.c_str());
    if(loc == -1){
        std::cout << "Warning: Uniform" << name << "not found" << std::endl;
    }
    uniformLocationCache[name] = loc;
    return loc;
}

ShaderProgramSource Shader::ParseShader(const std::string &filepath) {
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

unsigned int Shader::compileShader(unsigned int type, const std::string& source){
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


unsigned int Shader::createShader(const std::string& vertexShader, const std::string fragmentShader){
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

