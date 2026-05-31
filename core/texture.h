#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

class Texture
{
public:
    unsigned int m_id = 0;
    Texture(const std::string &texturePath);
    ~Texture();

    void bindTexture(unsigned int unit = 0) const;
};

#endif // TEXTURE_H
