#ifndef GameEngine_Common_Scene_RendererCommand_H
#define GameEngine_Common_Scene_RendererCommand_H

#include "Component.h"
namespace GameEngine
{
    class RendererCommand 
    {
    public:
        RendererCommand() {}
        virtual void excecute() = 0;
    };
} // namespace GameEngine
#endif