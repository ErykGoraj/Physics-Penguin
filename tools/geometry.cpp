#include "geometry.h"

void Geometry::generateSphereData(int stackCount, int sectorCount, float radius)
{
    m_current_vertices.clear();
    m_current_normals.clear();
    m_current_tex_coords.clear();
    m_current_indices.clear();

    float x, y, z, xy;                  // Vertex position
    float nx, ny, nz;                   // Vertex normal
    float lengthInv = 1.0f / radius;    //
    float s, t;                         // Vertex TexCoord
    int k1, k2;                       // Indices indexs


    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    // VERTEX CALCULATIONS
    for (int i = 0; i <= stackCount; i++)
    {
        stackAngle = PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectorCount; j++)
        {
            sectorAngle = j * sectorStep;

            // Vertex position
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            m_current_vertices.push_back(x);
            m_current_vertices.push_back(y);
            m_current_vertices.push_back(z);

            // Vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            m_current_normals.push_back(nx);
            m_current_normals.push_back(ny);
            m_current_normals.push_back(nz);

            // Vertex TexCoord
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            m_current_tex_coords.push_back(s);
            m_current_tex_coords.push_back(t);
        }
    }

    // INDICES CALCULATIONS
    for (int i = 0; i < stackCount; i++)
    {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; j++, k1++, k2++)
        {
            if (i != 0)
            {
                m_current_indices.push_back(k1);
                m_current_indices.push_back(k2);
                m_current_indices.push_back(k1+ 1);
            }

            if (i != (stackCount - 1))
            {
                m_current_indices.push_back(k1 + 1);
                m_current_indices.push_back(k2);
                m_current_indices.push_back(k2 + 1);
            }
        }
    }
}

std::vector<float> Geometry::getVertices()
{
    return m_current_vertices;
}

std::vector<float> Geometry::getTexCoords()
{
    return m_current_tex_coords;
}

std::vector<float> Geometry::getNormals()
{
    return m_current_normals;
}

std::vector<int> Geometry::getIndices()
{
    return m_current_indices;
}
