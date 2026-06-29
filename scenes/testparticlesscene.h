#ifndef TESTPARTICLESSCENE_H
#define TESTPARTICLESSCENE_H

#include "../core/scene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../core/mesh.h"
#include "../core/shader.h"
#include <iostream>
#include <memory>
#include "../core/camera.h"
#include <glm/glm.hpp>
#include "../core/controller.h"
#include <vector>
#include "../tools/geometry.h"
#include <cstdlib>

struct ParticleTest {
    float speed;
    glm::vec3 position;
    glm::vec3 direction;
    ParticleTest(float s, glm::vec3 p, glm::vec3 d) : speed(s), position(p), direction(d) {}
};

class TestParticlesScene : public Scene
{
public:
    TestParticlesScene() = default;
    void init() override;
    void render() override;
    void update(float deltaTime) override;
    void processInput(GLFWwindow* window, float deltaTime) override;
    void processMouseMovement(double xoffset, double yoffset) override;
    bool newScene() override;
private:
    void generateSphereVertices();
    float LAST_X = 800.0f / 2.0f;
    float LAST_Y = 800.0f / 2.0f;
    bool FIRST_MOUSE = true;
    bool CHANGE_SCENE = false;
    Geometry m_geometry;

    std::vector<float> m_particle_vertices;
    std::vector<int> m_particle_indices;

    std::unique_ptr<Mesh> m_mesh;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Camera> m_camera;
    Controller m_controller;
    SendData sendData;
    const glm::vec3 PARTCILE_COLOR {1.0f, 1.0f, 0.0f};
    std::vector<ParticleTest> particleTest;

    float clock = 0.0f;
};

#endif // TESTPARTICLESSCENE_H
