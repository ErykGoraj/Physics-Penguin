#include "testparticlesscene.h"

void TestParticlesScene::init()
{
    // Vertices && Normals && TexCoords && Attributes
    // Use geometry tool to calculate vertex data
    m_geometry.generateSphereData(36, 18, 1);
    m_particle_vertices = m_geometry.getVertices();
    m_particle_indices = m_geometry.getIndices();
    std::vector<VertexAttribute> attributes = {
        {0, 3}
    };

    // Shaders
    const char* vs_path = "/home/erykgoraj/Projekty/PhysicsPenguin/shaders/particle.vert";
    const char* fr_path = "/home/erykgoraj/Projekty/PhysicsPenguin/shaders/particle.frag";

    const std::string wood_image = "/home/erykgoraj/Projekty/PhysicsPenguin/resources/wood.jpg";
    m_mesh = std::make_unique<Mesh>(sizeof(float) * m_particle_vertices.size(), m_particle_vertices, attributes, GL_STATIC_DRAW, sizeof(int) * m_particle_indices.size(), m_particle_indices);
    m_shader = std::make_unique<Shader>(vs_path, fr_path);
    m_shader->use();
    m_camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    m_controller.init();
    glEnable(GL_DEPTH_TEST);

    for (int i = 0; i < 100; i++)
    {
        particleTest.emplace_back(4.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f));
    }
    std::srand(time(0));
}

void TestParticlesScene::render()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    this->m_shader->use();
    this->m_mesh->bindVao();

    for (int i = 0; i < particleTest.size(); i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, particleTest[i].position);
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        m_shader->setMat4("model", model);
        glDrawElements(GL_TRIANGLES, m_particle_indices.size(), GL_UNSIGNED_INT, 0);
    }
}

void TestParticlesScene::update(float deltaTime)
{
    glClearColor(0.0f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    clock += deltaTime;

    sendData = m_controller.getData();
    glm::mat4 projection = glm::perspective(glm::radians(m_camera->m_zoom), (float)800/(float)800, 0.1f, 100.0f);
    m_shader->setMat4("projection", projection);

    glm::mat4 view = m_camera->getViewMatrix();
    m_shader->setMat4("view", view);

    if (clock >= 3)
    {
        clock = 0.0f;
        for (int i = 0; i < particleTest.size(); i++)
        {
            particleTest[i].direction.x = static_cast<float>(std::rand())/RAND_MAX * 2.0f - 1.0f;
            particleTest[i].direction.y = static_cast<float>(std::rand())/RAND_MAX * 2.0f - 1.0f;
            particleTest[i].direction.z = static_cast<float>(std::rand())/RAND_MAX * 2.0f - 1.0f;
            particleTest[i].direction = glm::normalize(particleTest[i].direction);
        }
    }

    for (int i = 0; i < particleTest.size(); i++)
    {
        particleTest[i].position.x += particleTest[i].speed * deltaTime * particleTest[i].direction.x;
        particleTest[i].position.y += particleTest[i].speed * deltaTime * particleTest[i].direction.y;
        particleTest[i].position.z += particleTest[i].speed * deltaTime * particleTest[i].direction.z;
    }

    this->m_shader->setVec3("particleColor", PARTCILE_COLOR);
}

void TestParticlesScene::processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        CHANGE_SCENE = true;
    }

    // CONTROLLER AND KEYBOARD MOVEMENT
    m_controller.movement(*m_camera, window, deltaTime);
}

void TestParticlesScene::processMouseMovement(double xoffset, double yoffset)
{
    m_camera->processMouseMovement(static_cast<float>(xoffset), static_cast<float>(yoffset));
}

bool TestParticlesScene::newScene()
{
    return CHANGE_SCENE;
}
