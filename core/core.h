#ifndef CORE_H
#define CORE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

#include "shader.h"
#include "mesh.h"
#include "window.h"
#include "scenemanager.h"
#include "../scenes/triangletestscene.h"
#include "../scenes/cubescene3d.h"

class Core
{
public:
    Core(const int &version_major, const int &version_minor, const int &width, const int &height, const char *window_tile);
    ~Core();
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void gameLoop();
    static void mouseCallBack(GLFWwindow* window, double xposIn, double yposIn);
private:
    std::unique_ptr<Window> m_window;
    SceneManager m_scene_manager;
    float m_delta_time = 0.0f;
    bool m_first_mouse = true;
    float m_last_x = 0.0f;
    float m_last_y = 0.0f;

    int initGlad();
};

#endif // CORE_H