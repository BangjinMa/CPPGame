#pragma once

#include "GERObject.h"
#include <string>

namespace GameEngine
{
    namespace ger
    {
        class Device;
        class Shader
        {
        public:
            Shader(Device *d);
            ~Shader();

        public:
            virtual bool Initialize(const ShaderInfo &info) = 0;
            virtual void Destroy() = 0;

        protected:
            uint _shaderID = 0;
            Device *_device;
            ShaderInfo shaderInfo;
            std::string _name;
        };
    }
}