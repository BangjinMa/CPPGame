#pragma once

#include <iostream>

#include <glad/glad.h>
#include "Config.h"

namespace GameEngine
{
    class OpenGLDebugger
    {
    public:
        static GLenum glCheckError(const char *file = __FILE__, int line = __LINE__)
        {
            GLenum errorCode;
            while ((errorCode = glGetError()) != GL_NO_ERROR)
            {
                std::string error;
                switch (errorCode)
                {
                case GL_INVALID_ENUM:
                    error = "INVALID_ENUM";
                    break;
                case GL_INVALID_VALUE:
                    error = "INVALID_VALUE";
                    break;
                case GL_INVALID_OPERATION:
                    error = "INVALID_OPERATION";
                    break;
                case GL_STACK_OVERFLOW:
                    error = "STACK_OVERFLOW";
                    break;
                case GL_STACK_UNDERFLOW:
                    error = "STACK_UNDERFLOW";
                    break;
                case GL_OUT_OF_MEMORY:
                    error = "OUT_OF_MEMORY";
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    error = "INVALID_FRAMEBUFFER_OPERATION";
                    break;
                }
                std::cout << error.c_str() << " | " << file << " (" << line << ")" << std::endl;
            }
            return errorCode;
        }

    public:
#define glCheckError() glCheckError(__FILE__, __LINE__)

	//
};

}  // namespace GameEngine  // namespace GameEngine
