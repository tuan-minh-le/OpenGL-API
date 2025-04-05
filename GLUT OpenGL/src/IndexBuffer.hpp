//
//  VertexBuffer.hpp
//  GLUT OpenGL
//
//  Created by tuan minh on 5/4/25.
//

#ifndef IndexBuffer_hpp
#define IndexBuffer_hpp

class IndexBuffer{
    private:
        unsigned int renderer_ID;
        unsigned int count; // Element count
    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();
        void bind() const;
        void unbind() const;
        unsigned int getCount();
};

#endif /* IndexBuffer_hpp */
