#include "Circle.h"

WG::Circle::Circle(float _radius, std::uint32_t _interpolation):
    Mesh(1 + (_interpolation < 3 ? 3 : _interpolation), _interpolation < 3 ? 3 : _interpolation)
{
    #ifdef WG_DEBUG
    std::cout << "Circle::Constructor - create circle with:" << vertexNum << " vertices," << triNum << " triangles" << '\n';
    #endif

    double step = 360.0 / _interpolation;
    #ifdef WG_DEBUG
    std::cout << step << '\n';
    #endif
    vertices[0] = {{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.5, 0.5, 0.0}, {1.0, 1.0, 1.0}};
    for(std::uint32_t i = 1; i <= _interpolation; i++ )
    {
        double angle = i * step;
        #ifdef WG_DEBUG
        std::cout << angle << '\n';
        #endif
        vertices[i].pos.x = glm::cos(glm::radians(angle)) * _radius;
        vertices[i].pos.y = glm::sin(glm::radians(angle)) * _radius;
        vertices[i].pos.z = 0.0f;
        vertices[i].normal.x = 0.0f;
        vertices[i].normal.y = 0.0f;
        vertices[i].normal.z = 1.0f;
        vertices[i].texCoord.x = (vertices[i].pos.x / _radius / 2.0) + 0.5;
        vertices[i].texCoord.y = (vertices[i].pos.y / _radius / 2.0) + 0.5;
        vertices[i].texCoord.z = 0.0f;
        vertices[i].color.r = 1.0f;
        vertices[i].color.g = 1.0f;
        vertices[i].color.b = 1.0f;
    }

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = vertexNum - 1;
    for(std::uint32_t i = 1; i < triNum; i++)
    {
        indices[i * 3] = 0;
        indices[i * 3 + 1] = i + 1;
        indices[i * 3 + 2] = i;
    }
}

WG::Circle::~Circle()
{
    delete[] indices;
    indices = nullptr;
    delete[] vertices;
    vertices = nullptr;
    vertexNum = 0;
    triNum = 0;
}
