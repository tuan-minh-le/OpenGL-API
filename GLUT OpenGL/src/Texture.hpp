//
//  Texture.hpp
//  GLUT OpenGL
//
//  Created by tuan minh on 8/4/25.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "renderer.hpp"
#include <stb_image/stb_image.h>

class Texture{
    private:
        unsigned int renderer_id;
        std::string filepath;
        unsigned char* localBuffer;
        int width, height, BPP; // bit per pixel
    public:
        Texture(const std::string& path);
        ~Texture();
        void bind(unsigned int slot = 0) const;
        void unbind() const;
    
        int getWidth() const;
        int getHeight() const;
};

#endif /* Texture_hpp */
