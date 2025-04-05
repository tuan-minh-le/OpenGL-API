//
//  IndexBuffer.cpp
//  GLUT OpenGL
//
//  Created by tuan minh on 5/4/25.
//

#include "IndexBuffer.hpp"
#include "renderer.hpp"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):count(count){
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    glGenBuffers(1, &renderer_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1, &renderer_ID);
}

void IndexBuffer::bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_ID);
}

void IndexBuffer::unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getCount(){
    return count;
}
