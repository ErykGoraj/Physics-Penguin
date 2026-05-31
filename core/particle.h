#ifndef PARTICLE_H
#define PARTICLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct ParticleS
{
    glm::vec3 position;
    glm::vec3 color;
};

class Particle
{
public:
    Particle();
private:

};

#endif // PARTICLE_H
