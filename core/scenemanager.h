#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <memory>

#include "scene.h"

class SceneManager
{
public:
    SceneManager() = default;

    std::unique_ptr<Scene> m_current_scene;
    void changeScene(std::unique_ptr<Scene> newScene);
    void update(float deltaTime);
    void render();
    void processInput(GLFWwindow* window, float deltaTime);
    void processMouseMovement(double xoffset, double yoffset);
};

#endif // SCENEMANAGER_H
