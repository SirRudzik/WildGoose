#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include "Mesh.h"
#include "../Debug.h"

namespace WG
{
class Circle : public Mesh
{
    public:
        Circle(float _radius = 1.0f, std::uint32_t _interpolation = 8);
        virtual ~Circle();

    protected:

    private:
};
}

#endif // CIRCLE_H
