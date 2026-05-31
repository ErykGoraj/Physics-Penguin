#include "core.h"

Core::Core(const int &version_major, const int &version_minor, const int &width, const int &height, const char *window_tile)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = std::make_unique<Window>(800, 800, "Physics Penguin");
    glfwSetWindowUserPointer(m_window->getHandle(), this);

    initGlad();
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(m_window->getHandle(), framebuffer_size_callback);
    glfwSetCursorPosCallback(m_window->getHandle(), mouseCallBack);
    glfwSetInputMode(m_window->getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    this->m_scene_manager.changeScene(std::make_unique<CubeScene3D>());
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

void Core::mouseCallBack(GLFWwindow *window, double xposIn, double yposIn)
{
    Core* core = static_cast<Core*>(glfwGetWindowUserPointer(window));
    if (!core) return;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (core->m_first_mouse)
    {
        core->m_last_x = xpos;
        core->m_last_y = ypos;
        core->m_first_mouse = false;
    }

    float xoffset = xpos - core->m_last_x;
    float yoffset = core->m_last_y - ypos;

    core->m_last_x = xpos;
    core->m_last_y = ypos;

    core->m_scene_manager.processMouseMovement(xoffset, yoffset);
}

void Core::gameLoop()
{
    float lastFrame = 0.0f;
    while (!m_window->shouldClose())
    {
        float currentFrame = glfwGetTime();
        m_delta_time = currentFrame - lastFrame;
        lastFrame = currentFrame;

        m_scene_manager.processInput(m_window->getHandle(), m_delta_time);

        glClearColor(0.6f, 0.2f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        this->m_scene_manager.update(m_delta_time);
        this->m_scene_manager.render();

        m_window->swapBuffers();
        m_window->poolEvents();
    }
}

