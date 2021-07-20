#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GL/gl.h>
#include "Image.h"
#include "../Debug.h"

namespace WG
{
class Texture
{
    public:
        Texture(WG::Image* _image);
        virtual ~Texture();
        bool Bind(unsigned int unit = 0);
        bool Unbind();

    protected:
        bool Create(WG::Image* _image);
        GLuint id;
};
}
#endif // TEXTURE_H
