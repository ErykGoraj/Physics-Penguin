#ifndef CUBESCENE3D_H
#define CUBESCENE3D_H

#include "../core/scene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../core/mesh.h"
#include "../core/shader.h"
#include <iostream>
#include <memory>
#include "../core/texture.h"
#include "../core/camera.h"
#include <glm/glm.hpp>
#include "../core/controller.h"

class CubeScene3D : public Scene
{
public:
    CubeScene3D() = default;
    void init() override;
    void update(float deltaTime) override;
    void render() override;
    void processInput(GLFWwindow* window, float deltaTime) override;
    void processMouseMovement(double xoffset, double yoffset) override;
    bool newScene() override;
private:
    std::vector<VertexAttribute> attributes;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Mesh> m_mesh;
    std::unique_ptr<Texture> m_wood_wall_texture;
    std::unique_ptr<Camera> m_camera;
    Controller m_controller;
    SendData sendData;
    bool CHANGE_SCENE = false;
};

#endif // CUBESCENE3D_H
