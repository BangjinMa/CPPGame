#include "GERShader.h"
#include "GERDevice.h"
namespace GameEngine
{
    namespace ger
    {
        Shader::Shader(Device *d) : _device(d)
        {
            _shaderID = _device->GetShaderID();
        }

        Shader::~Shader()
        {
        }
    }
}
