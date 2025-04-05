//
//  VertexBufferElements.h
//  GLUT OpenGL
//
//  Created by tuan minh on 5/4/25.
//

#ifndef VertexBufferLayout_hpp
#define VertexBufferLayout_hpp

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "renderer.hpp"

struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    
    static unsigned int getTypeSize(unsigned int type){
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout{
    private:
        std::vector<VertexBufferElement> elements;
        unsigned int stride; // Step size to get from one vertex to another (sum of number of elements and its size in bytes)
    public:
        VertexBufferLayout():stride(0){
            
        };
        
        template<typename T>
        void push(unsigned int count){
            static_assert(false, "Unsupported type");
        }
    
        template<>
        void push<float>(unsigned int count){
            elements.push_back({GL_FLOAT, count, GL_FALSE});
            stride += VertexBufferElement::getTypeSize(GL_FLOAT) * count;
        }
    
        template<>
        void push<unsigned int>(unsigned int count){
            elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
            stride += VertexBufferElement::getTypeSize(GL_UNSIGNED_INT) * count;
        }
    
        template<>
        void push<unsigned char>(unsigned int count){
            elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
            stride += VertexBufferElement::getTypeSize(GL_UNSIGNED_BYTE) * count;
        }
        
        const std::vector<VertexBufferElement>& getElements() const{
            return elements;
        }
        
        unsigned int getStride() const{
            return stride;
        }
};


#endif /* VertexBufferLayout_hpp */
