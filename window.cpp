#include "window.h"

Window::Window(const int &width, const int &height, const char *window_tile)
{
    this->window = glfwCreateWindow(width, height, window_tile, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Wystąpił błąd przy tworzeniu okna!" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(this->window);
}

Window::~Window()
{
    if (window)
    {
        glfwDestroyWindow(window);
    }
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(window);
}

void Window::poolEvents() const
{
    glfwPollEvents();
}

GLFWwindow *Window::getHandle() const
{
    return window;
}
