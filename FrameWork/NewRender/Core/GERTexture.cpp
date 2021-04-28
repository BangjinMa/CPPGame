#include "GERTexture.h"

#include "GERDevice.h"

namespace GameEngine
{
    namespace ger
    {
        Texture::Texture(Device *d) : _device(d) {}

        Texture::~Texture() {}
    }
}
