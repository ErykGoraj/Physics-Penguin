#include "mesh.h"

Mesh::Mesh(std::size_t vertices_size, const float *vertices, const std::vector<VertexAttribute> &attributes, unsigned int draw_method)
{
    setUpVao();
    bindVao();
    setUpVbo(vertices_size, vertices, draw_method);
    setUpVertexAttributes(attributes);
    unBindVao();
    unBindVbo();
}

void Mesh::bindVao() const
{
    glBindVertexArray(VAO);
}

void Mesh::bindVbo() const
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Mesh::unBindVao() const
{
    glBindVertexArray(0);
}

void Mesh::unBindVbo() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::setUpVao()
{
    glGenVertexArrays(1, &VAO);
}

void Mesh::setUpVbo(std::size_t vertices_size, const float *vertices, unsigned int draw_method)
{
    glGenBuffers(1, &VBO);
    bindVbo();
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, draw_method);
}

void Mesh::setUpVertexAttributes(const std::vector<VertexAttribute> &attributes)
{
    int components_size;

    for (const auto &vertex_attrib : attributes)
    {
        components_size += vertex_attrib.size;
    }
    GLsizei stride = components_size * sizeof(float);

    std::size_t offset = 0;
    for (const auto &vertex_attrib : attributes)
    {
        glVertexAttribPointer(vertex_attrib.index, vertex_attrib.size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
        glEnableVertexAttribArray(vertex_attrib.index);
        offset += vertex_attrib.size * sizeof(float);
    }
}