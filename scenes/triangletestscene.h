#ifndef TRIANGLETESTSCENE_H
#define TRIANGLETESTSCENE_H

#include "../core/scene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../core/mesh.h"
#include "../core/shader.h"
#include <iostream>
#include <memory>

class TriangleTestScene : public Scene
{
public:
    TriangleTestScene() = default;
    void init() override;
    void update(float deltaTime) override;
    void render() override;
private:
    std::vector<VertexAttribute> attributes;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Mesh> m_mesh;
};

#endif // TRIANGLETESTSCENE_H
