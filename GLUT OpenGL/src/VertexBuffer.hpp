//
//  VertexBuffer.hpp
//  GLUT OpenGL
//
//  Created by tuan minh on 5/4/25.
//

#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

class VertexBuffer{
    private:
        unsigned int renderer_ID;
    public:
        VertexBuffer(const void* data, unsigned int size); // Size in bytes
        ~VertexBuffer();
        void bind() const;
        void unbind() const;
};

#endif /* VertexBuffer_hpp */
