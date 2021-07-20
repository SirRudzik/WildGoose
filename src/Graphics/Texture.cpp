#include "Texture.h"

WG::Texture::Texture(WG::Image* _image):
    id(0)
{
    #ifdef WG_DEBUG
    std::cout << "Texture::Konstruktor \n";
    #endif
    Create(_image);
    //ctor
}

WG::Texture::~Texture()
{
    #ifdef WG_DEBUG
    std::cout << "Texture::Destruktor \n";
    #endif
    Unbind();
    glDeleteTextures(1, &id);
    //dtor
}

bool WG::Texture::Create(WG::Image* _image)
{
    #ifdef WG_DEBUG
    std::cout << "Texture::Create \n";
    #endif
    if(!_image)
        return false;

    GLenum format;
    std::uint8_t bbp = _image->Bpp();
    switch(bbp)
    {
    case 8:
        format = GL_LUMINANCE;
        break;
    case 24:
        format = GL_RGB;
        break;
    case 32:
        format = GL_RGBA;
        break;
    }
    #ifdef WG_DEBUG
    std::cout << format << " format \n";
    #endif

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image->Width(), _image->Height(), 0, format, GL_UNSIGNED_BYTE, _image->Data());
    glGenerateMipmap(GL_TEXTURE_2D);
    #ifdef WG_DEBUG
    std::cout << "Texture::Bind \n";
    #endif
    return true;
}

bool WG::Texture::Bind(unsigned int unit)
{
    #ifdef WG_DEBUG
    std::cout << "Texture::Bind \n";
    #endif
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
    return true;
}

bool WG::Texture::Unbind()
{
    #ifdef WG_DEBUG
    std::cout << "Texture::Unbind \n";
    #endif
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}
