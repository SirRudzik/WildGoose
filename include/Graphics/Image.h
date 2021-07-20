#ifndef IMAGE_H
#define IMAGE_H

#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include "../Debug.h"

namespace WG
{
class Image
{
    public:
        Image();
        virtual ~Image();

        bool Load(const char* _name);
        bool Save(const char* _name);
        bool Create(int _xSize, int _ySize, int _bbp);
        bool Clear();
        bool IsEmpty() const {return isEmpty;}
        std::uint8_t* Data() const {return data;}
        std::uint32_t Width() const {return width;}
        std::uint32_t Height() const {return height;}
        std::uint8_t Bpp() const {return bpp;}

    private:
        bool BlueRedChannelSwap();
        std::uint8_t* data;
        std::uint32_t bufferSize;
        std::uint8_t bpp;
        std::uint32_t height;
        std::uint32_t width;
        std::uint32_t texelsNumber;
        bool isEmpty;

};
}

#endif // IMAGE_H
