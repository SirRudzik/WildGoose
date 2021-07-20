#include "Mesh.h"

WG::Mesh::Mesh(std::uint32_t _vertexNumber, std::uint32_t _triNumber):
    vertexNum(_vertexNumber),
    triNum(_triNumber),
    indices(nullptr),
    vertices(nullptr)
{
    indices = new std::uint32_t[_triNumber * 3];
    vertices = new WG::Vertex[_vertexNumber];
    //ctor
}

WG::Mesh::~Mesh()
{
    delete[] indices;
    indices = nullptr;
    delete[] vertices;
    vertices = nullptr;
    vertexNum = 0;
    triNum = 0;
    //dtor
}
