#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include "Mesh.h"
#include "../Debug.h"

namespace WG
{
class Rectangle : public Mesh
{
    public:
        Rectangle(float _sizeX = 1.0f, float _sizeY = 1.0f);
        virtual ~Rectangle();

};
}

#endif // RECTANGLE_H
