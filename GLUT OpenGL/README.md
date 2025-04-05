# OpenGL Abstraction Layer

This project implements a modern OpenGL abstraction layer that provides object-oriented wrappers around the low-level OpenGL API. The code is structured following the principles taught in "The Cherno" OpenGL tutorial series on YouTube.

## Overview

The implementation provides abstractions for the core OpenGL concepts:

- **Vertex and Index Buffers**: Manage GPU memory allocation for vertex data and indices
- **Vertex Array Objects**: Organize the layout of vertex attributes
- **Shader Management**: Parse and compile GLSL shaders
- **Error Handling**: Debug and catch OpenGL errors through a robust error checking system

## Core Components

### Vertex Buffer
Handles the creation, binding, and management of OpenGL vertex buffers that store geometric data.

### Index Buffer
Manages element array buffers that store indices for indexed rendering, significantly optimizing draw calls.

### Vertex Buffer Layout
Describes how vertex data is structured in memory, specifying the types, counts, and offsets of vertex attributes.

### Vertex Array Object
Encapsulates the state needed for vertex specification, binding vertex buffers with their layouts.

### Renderer
Provides error handling functionality through macros and utility functions.

### Shader Management
Parses shaders from files and handles compilation and linking of shader programs.

## Usage Example

The `main.cpp` file demonstrates how these abstractions work together:

```cpp
// Create vertex array and buffer objects
VertexArray* va = new VertexArray();
VertexBuffer* vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));

// Set up vertex layout
VertexBufferLayout layout;
layout.push<float>(2);
va->addBuffer(*vb, layout);

// Create index buffer
IndexBuffer* ib = new IndexBuffer(indices, 6);

// Load and compile shaders
ShaderProgramSource source = ParseShader("path/to/shader.shader");
unsigned int shader = createShader(source.VertexSource, source.FragmentSource);

// Drawing
va->bind();
ib->bind();
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
```

## Credits

This implementation is based on "The Cherno" OpenGL tutorial series on YouTube, which provides an excellent foundation for learning modern OpenGL programming with C++. The series demonstrates how to create clean abstractions around the OpenGL API to make rendering code more maintainable and easier to understand.

## Project Structure

- `src/`: Source files implementing the OpenGL abstractions
- `res/shaders/`: GLSL shader files

## Dependencies

- GLEW: OpenGL Extension Wrangler Library
- GLFW: Multi-platform library for creating windows with OpenGL contexts
