#ifndef CPPGAME_COMMON_GAMEPLATFORM_OPENGL_H
#define CPPGAME_COMMON_GAMEPLATFORM_OPENGL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <vector>

#include "BaseApplication.h"
#include "GfxConfiguration.h"

namespace GameEngine
{
    class OpenGLApplication : public BaseApplication
    {
    public:
        OpenGLApplication(GfxConfiguration &config);

        virtual int Initialize();
        virtual void Finalize();
        // One cycle of the main loop
        virtual void Tick(float deltaTime);

        static void MouseInput(GLFWwindow *window, int button, int action, int mods);
        static void KeyInput(GLFWwindow *window, int key, int scancode, int action, int mods);

    private:
        GLFWwindow *window;
    };
}  // namespace GameEngine
#endif  //CPPGAME_COMMON_GAMEPLATFORM_OPENGL_H
