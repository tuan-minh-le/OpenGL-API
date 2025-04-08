//
//  renderer.h
//  GLUT OpenGL
//
//  Created by tuan minh on 5/4/25.
//

#ifndef Renderer_h
#define Renderer_h

#include <GL/glew.h>
#include <signal.h>

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
    x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer{
    public:
        void clear() const;
        void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};


#endif /* Renderer_h */
