#include "triangletestscene.h"

void TriangleTestScene::init()
{
    // !!! Konfiguracja danych
    std::vector<float> vertices = {
        // pozycja
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
    };

    std::vector<VertexAttribute> attributes = {
        {0, 3}
    };

    const char* vs_path = "/home/erykgoraj/Projekty/PhysicsPenguin/shaders/test_triangle.vert";
    const char* fr_path = "/home/erykgoraj/Projekty/PhysicsPenguin/shaders/test_triangle.frag";
    m_mesh = std::make_unique<Mesh>(sizeof(vertices), vertices, attributes, GL_STATIC_DRAW);
    m_shader = std::make_unique<Shader>(vs_path, fr_path);
}

void TriangleTestScene::update(float deltaTime)
{

}

void TriangleTestScene::render()
{
    this->m_shader->use();
    this->m_mesh->bindVao();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
