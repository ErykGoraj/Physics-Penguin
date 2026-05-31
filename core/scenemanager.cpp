#include "scenemanager.h"

void SceneManager::changeScene(std::unique_ptr<Scene> newScene)
{
    this->m_current_scene = std::move(newScene);
    this->m_current_scene->init();
}

void SceneManager::update(float deltaTime)
{
    if (!m_current_scene) return;
    this->m_current_scene->update(deltaTime);
}

void SceneManager::render()
{
    if (!m_current_scene) return;
    this->m_current_scene->render();
}

void SceneManager::processInput(GLFWwindow *window, float deltaTime)
{
    if (!m_current_scene) return;
    this->m_current_scene->processInput(window, deltaTime);
}

void SceneManager::processMouseMovement(double xoffset, double yoffset)
{
    if (!m_current_scene) return;
    this->m_current_scene->processMouseMovement(xoffset, yoffset);
}
