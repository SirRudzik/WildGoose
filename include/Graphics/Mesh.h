#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include "../Debug.h"

namespace WG
{

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 texCoord;
    glm::vec3 color;
};

class Mesh
{
    public:
        Mesh(std::uint32_t _vertexNumber = 0, std::uint32_t _triNumber = 0);
        virtual ~Mesh();
        Vertex* GetVertices() {return vertices;}
        std::uint32_t GetVerticesNumber() {return vertexNum;}
        std::uint32_t* GetIndices() {return indices;}
        std::uint32_t GetTrianglesNumber() {return triNum;}

    protected:
        std::uint32_t vertexNum;
        std::uint32_t triNum;
        std::uint32_t* indices;
        Vertex* vertices;

};
}

#endif // MESH_H
