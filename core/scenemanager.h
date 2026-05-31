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
};

#endif // SCENEMANAGER_H
