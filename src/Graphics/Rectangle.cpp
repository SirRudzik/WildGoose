#include "Rectangle.h"

WG::Rectangle::Rectangle(float _sizeX, float _sizeY):
    Mesh(4, 2)
{
    #ifdef WG_DEBUG
    std::cout << "Rectangle::Constructor - create rectangle with:"  << vertexNum << " vertices," << triNum << " triangles" << '\n';
    #endif

    float hX = _sizeX / 2;
    float hY = _sizeY / 2;
    vertices[0] = {{hX, hY, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};
    vertices[1] = {{-hX, hY, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
    vertices[2] = {{hX, -hY, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
    vertices[3] = {{-hX, -hY, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}};

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 1;
    indices[4] = 3;
    indices[5] = 2;
    //ctor
}

WG::Rectangle::~Rectangle()
{
    delete[] indices;
    indices = nullptr;
    delete[] vertices;
    vertices = nullptr;
    vertexNum = 0;
    triNum = 0;
    //dtor
}
