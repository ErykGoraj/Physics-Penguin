#include "mesh.h"

Mesh::Mesh(std::size_t vertices_size, const std::vector<float> vertices, const std::vector<VertexAttribute> &attributes, unsigned int draw_method, std::size_t indices_size, const std::vector<int> indices)
{
    setUpVao();
    bindVao();
    setUpVbo(vertices_size, vertices, draw_method);
    if (!indices.empty()) setUpEbo(indices_size, indices, draw_method);

    setUpVertexAttributes(attributes);
    unBindVao();
    unBindVbo();
    if (!indices.empty()) unBindEbo();
}

void Mesh::bindVao() const
{
    glBindVertexArray(VAO);
}

void Mesh::bindVbo() const
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Mesh::bindEbo() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void Mesh::unBindVao() const
{
    glBindVertexArray(0);
}

void Mesh::unBindVbo() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::unBindEbo() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::setUpVao()
{
    glGenVertexArrays(1, &VAO);
}

void Mesh::setUpVbo(std::size_t vertices_size, const std::vector<float> vertices, unsigned int draw_method)
{
    glGenBuffers(1, &VBO);
    bindVbo();
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices.data(), draw_method);
}

void Mesh::setUpEbo(std::size_t indices_size, const std::vector<int> indices, unsigned int draw_method)
{
    glGenBuffers(1, &EBO);
    bindEbo();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices.data(), draw_method);
}

void Mesh::setUpVertexAttributes(const std::vector<VertexAttribute> &attributes)
{
    int components_size = 0;

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