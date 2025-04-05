//
//  VertexBuffer.cpp
//  GLUT OpenGL
//
//  Created by tuan minh on 5/4/25.
//

#include "VertexBuffer.hpp"
#include "renderer.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    glGenBuffers(1, &renderer_ID);
    glBindBuffer(GL_ARRAY_BUFFER, renderer_ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    
}

VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &renderer_ID);
}

void VertexBuffer::bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, renderer_ID);
}

void VertexBuffer::unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
