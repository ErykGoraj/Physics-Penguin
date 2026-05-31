#include "cubescene3d.h"

// ============================================
float lastX = 800.0f / 2.0f;
float lastY = 800.0f / 2.0f;
bool firstMouse = true;
// ============================================


void CubeScene3D::init()
{
    float vertices[] = {
        // Trójkąt 1
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // bottom left
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // bottom right
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // top right

        // Trójkąt 2
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // bottom left
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // top right
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f   // top left
    };

    std::vector<VertexAttribute> attributes = {
        {0, 3},
        {1, 3},
        {2, 2}
    };

    const char* vs_path = "/home/erykgoraj/Projekty/PhysicsPenguin/shaders/wood_wall.vert";
    const char* fr_path = "/home/erykgoraj/Projekty/PhysicsPenguin/shaders/wood_wall.frag";

    const std::string wood_wall_image = "/home/erykgoraj/Projekty/PhysicsPenguin/resources/container.jpg";
    m_mesh = std::make_unique<Mesh>(sizeof(vertices), vertices, attributes, GL_STATIC_DRAW);
    m_shader = std::make_unique<Shader>(vs_path, fr_path);
    m_wood_wall_texture = std::make_unique<Texture>(wood_wall_image);
    m_shader->use();
    m_shader->setInt("ourTexture", 0);
    m_camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
}

void CubeScene3D::update(float deltaTime)
{
    glm::mat4 projection = glm::perspective(glm::radians(m_camera->m_zoom), (float)800/(float)800, 0.1f, 100.0f);
    m_shader->setMat4("projection", projection);

    glm::mat4 view = m_camera->getViewMatrix();
    m_shader->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    m_shader->setMat4("model", model);
}

void CubeScene3D::render()
{
    this->m_shader->use();
    this->m_mesh->bindVao();
    this->m_wood_wall_texture->bindTexture(0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void CubeScene3D::processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera->processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera->processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera->processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera->processKeyboard(RIGHT, deltaTime);
}

void CubeScene3D::processMouseMovement(double xoffset, double yoffset)
{
    m_camera->processMouseMovement(static_cast<float>(xoffset), static_cast<float>(yoffset));
}
