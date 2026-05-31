#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
public:
    Window(const int &width, const int &height, const char *window_tile);
    ~Window();
    bool shouldClose() const;
    void swapBuffers()  const;
    void poolEvents() const;
    GLFWwindow* getHandle() const;

private:
    GLFWwindow* window{nullptr};
};

#endif // WINDOW_H
