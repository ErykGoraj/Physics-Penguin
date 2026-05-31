#include "core.h"

Core::Core(const int &version_major, const int &version_minor, const int &width, const int &height, const char *window_tile)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = std::make_unique<Window>(800, 800, "Physics Penguin");

    initGlad();
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(m_window->getHandle(), framebuffer_size_callback);

    this->m_scene_manager.changeScene(std::make_unique<TriangleTestScene>());
}

Core::~Core()
{
    glfwTerminate();
}

void Core::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int Core::initGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Wystąpił błąd podczas inicjalizacji GLAD!" << std::endl;
        return -1;
    }
    return 0;
}

void Core::gameLoop()
{
    while (!m_window->shouldClose())
    {
        m_events.processInput(m_window->getHandle());

        glClearColor(0.6f, 0.2f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        this->m_scene_manager.update(2.0f);
        this->m_scene_manager.render();

        m_window->swapBuffers();
        m_window->poolEvents();
    }
}

