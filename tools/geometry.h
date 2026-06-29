#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <iostream>
#include <math.h>

class Geometry
{
public:
    Geometry() = default;
    void generateSphereData(int stackCount, int sectorCount, float radius);
    std::vector<float> getVertices();
    std::vector<float> getTexCoords();
    std::vector<float> getNormals();
    std::vector<int> getIndices();
private:
    std::vector<float> m_current_vertices;
    std::vector<float> m_current_tex_coords;
    std::vector<float> m_current_normals;
    std::vector<int> m_current_indices;

    float PI = 3.14f;
};

#endif // GEOMETRY_H
