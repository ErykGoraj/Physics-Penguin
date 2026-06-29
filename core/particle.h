#ifndef PARTICLE_H
#define PARTICLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <map>
#include "../tools/geometry.h"
#include "mesh.h"
#include "shader.h"

struct ParticleData {
    Mesh mesh;
    Shader shader;
    glm::vec3 position;
    glm::vec3 color;
};

class Particle
{
public:
    Particle() = default;

private:
};

#endif // PARTICLE_H
