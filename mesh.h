#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <cstddef>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct VertexAttribute
{
    unsigned int index;
    int size;
};

class Mesh
{
public:
    unsigned int VBO{0};
    unsigned int VAO{0};

    Mesh(std::size_t vertices_size, const float *vertices, const std::vector<VertexAttribute> &attributes, unsigned int draw_method);
    void bindVao() const;
    void bindVbo() const;
    void unBindVao() const;
    void unBindVbo() const;
private:
    void setUpVao();
    void setUpVbo(std::size_t vertices_size, const float* vertices, unsigned int draw_method);
    void setUpVertexAttributes(const std::vector<VertexAttribute> &attributes);
};

#endif // MESH_H
