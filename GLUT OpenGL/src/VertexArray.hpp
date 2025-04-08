//
//  VertexArray.hpp
//  GLUT OpenGL
//
//  Created by tuan minh on 5/4/25.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

#include "VertexBuffer.hpp"

class VertexBufferLayout;


class VertexArray{
    private:
        unsigned int renderer_id;
    
    public:
        VertexArray();
        ~VertexArray();
        void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void bind() const;
        void unbind() const;
};

#endif /* VertexArray_hpp */
