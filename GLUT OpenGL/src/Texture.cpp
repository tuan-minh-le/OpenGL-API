//
//  Texture.cpp
//  GLUT OpenGL
//
//  Created by tuan minh on 8/4/25.
//

#include "Texture.hpp"

Texture::Texture(const std::string& filepath):renderer_id(0), filepath(filepath), localBuffer(nullptr), width(0), height(0), BPP(0){
    stbi_set_flip_vertically_on_load(1);
    localBuffer = stbi_load(filepath.c_str(), &width, &height, &BPP, 4); // Load the image in the local buffer in 4 channels (RGBA) and filling the attributes
    glGenTextures(1, &renderer_id);
    glBindTexture(GL_TEXTURE_2D, renderer_id);
    
    // OpenGL parameters that needs to be set (scaling and wrapping?)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Set the scaling if the object is bigger than the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbinds texture;
    
    if(localBuffer){
        stbi_image_free(localBuffer);
    }
}

Texture::~Texture(){
    glDeleteTextures(1, &renderer_id);
}

void Texture::bind(unsigned int slot /*Defaults to 0*/) const{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, renderer_id);
}

void Texture::unbind() const{
    glBindTexture(GL_TEXTURE_2D, 0); // Unbinds texture;
}

