#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void init() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void processInput(GLFWwindow* window, float deltaTime) = 0;
    virtual void processMouseMovement(double xoffset, double yoffset) = 0;
    virtual bool newScene() = 0;
};

#endif // SCENE_H