#ifndef CORE_H
#define CORE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

#include "shader.h"
#include "mesh.h"
#include "events.h"
#include "window.h"

class Core
{
public:
    Core(const int &version_major, const int &version_minor, const int &width, const int &height, const char *window_tile);
    ~Core();
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void gameLoop();
private:
    std::unique_ptr<Mesh> m_mesh;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Window> m_window;
    Events m_events;

    int initGlad();
};

#endif // CORE_H