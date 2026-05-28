#ifndef EVENTS_H
#define EVENTS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Events
{
public:
    Events();
    void processInput(GLFWwindow* window);
};

#endif // EVENTS_H
