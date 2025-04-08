//
//  VertexArray.cpp
//  GLUT OpenGL
//
//  Created by tuan minh on 5/4/25.
//

#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"


VertexArray::VertexArray(){
    glGenVertexArrays(1, &renderer_id);
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &renderer_id);
}

void VertexArray::bind() const{
    glBindVertexArray(renderer_id);
}

void VertexArray::unbind() const{
    glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout &layout){
    bind();
    vb.bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++){
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
        offset += element.count * VertexBufferElement::getTypeSize(element.type); // Offset represents how many bytes to skip to get to a specific attribute
    }
    
}
