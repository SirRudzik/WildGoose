#include "../../include/Graphics/Image.h"

WG::Image::Image():
    data(nullptr),
    bufferSize(0),
    bpp(0),
    height(0),
    width(0),
    texelsNumber(0),
    isEmpty(true)
{
    #ifdef WG_DEBUG
    std::cout << "Image::Konstruktor \n";
    #endif
}

WG::Image::~Image()
{
    #ifdef WG_DEBUG
    std::cout << "Image::Destruktor \n";
    #endif
    Clear();
}


bool WG::Image::Load(const char* _name)
{
    #ifdef WG_DEBUG
    std::cout << "Image::Load - Start \n";
    #endif

    if(!isEmpty)
        return false;

    std::uint8_t header[18];
    std::fstream file(_name, std::ios::in | std::ios::binary);
    if(!file.good())
    {
        file.close();
        return false;
    }

    #ifdef WG_DEBUG
    std::cout << "Image::Load - File open OK \n";
    #endif

    file.seekg(0, std::ios_base::beg);
    file.read((char*) &header, sizeof(header));

    if(!((header[2] == 2 ||  header[2] == 3) && (header[16] == 24 || header[16] == 32 || header[16] == 8)))
    {
        #ifdef WG_DEBUG
        std::cout << "close bbp - " <<(header[16] + 0) << std::endl;
        std::cout << "close bbp - " <<(header[2] + 0) << std::endl;
        #endif
        file.close();
        return false;
    }

    bpp = header[16];
    width = header[12] + (header[13] << 8);
    height = header[14] + (header[15] << 8);
    texelsNumber = width * height;
    bufferSize = texelsNumber * (bpp / 8);

    #ifdef WG_DEBUG
    std::cout << "bbp - " <<(bpp + 0) << std::endl;
    #endif

    data = new std::uint8_t[bufferSize];
    isEmpty = false;
    file.read((char*) data, bufferSize);

    file.close();
    if(bpp != 8)
        BlueRedChannelSwap();
    #ifdef WG_DEBUG
    std::cout << "Image::Load - Image Load successful \n";
    #endif
    return true;
}

bool WG::Image::Save(const char* _name)
{
    #ifdef WG_DEBUG
    std::cout << "Image::Load - Start \n";
    #endif
    if(isEmpty)
        return false;

    std::uint8_t header[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    std::fstream file;
    file.open(_name, std::ios::out | std::ios::binary);
    if(!file.good())
    {
        file.close();
        return false;
    }
    #ifdef WG_DEBUG
    std::cout << "Image::Load - File open OK \n";
    #endif

    header[2] = (bpp / 8 == 1 ? 3 : 2);
    header[12] = width & 0xff;
    header[13] = (width >> 8) & 0xff;
    header[14] = height & 0xff;
    header[15] = (height >> 8) & 0xff;
    header[16] = bpp;

    if(bpp != 8)
        BlueRedChannelSwap();

    file.seekp(0, std::ios_base::beg);
    file.write((char*) &header, sizeof(header));
    file.write((char*) data, bufferSize);
    file.close();

    #ifdef WG_DEBUG
    std::cout << "Image::Load - Image Save successful \n";
    #endif

    return true;
}

bool WG::Image::Create(int _xSize, int _ySize, int _bpp)
{
    #ifdef WG_DEBUG
    std::cout << "Image::Create \n";
    #endif
    if(_xSize <= 0 || _ySize <= 0 || (_bpp != 24 && _bpp != 32 && _bpp !=8) || isEmpty == false)
        return false;
    bpp = _bpp;
    width = _xSize;
    height = _ySize;
    texelsNumber = width * height;
    bufferSize = texelsNumber * (bpp / 8);
    data = new std::uint8_t[bufferSize];
    isEmpty = false;
    return true;
}

bool WG::Image::Clear()
{
    #ifdef WG_DEBUG
    std::cout << "Image::Clear \n";
    #endif
    delete[] data;
    bufferSize = 0;
    bpp = 0;
    height = 0;
    width = 0;
    texelsNumber = 0;
    isEmpty = true;
    return 0;
}

bool WG::Image::BlueRedChannelSwap()
{
    #ifdef WG_DEBUG
    std::cout << "Image::BlueRedChannelSwap\n";
    #endif
    if(isEmpty || bpp == 8)
        return false;
    std::uint8_t temp;
    for(unsigned int i = 0; i < bufferSize; i+= (bpp / 8))
    {
        temp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = temp;
    }
    return true;
}
