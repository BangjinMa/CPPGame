﻿#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Config.h"
#include "InputManager.h"

namespace GameEngine
{
    class InputManagerWindows : public InputManager
    {
    public:
        virtual int Initialize();
        virtual void Tick(float deltaTime);

        static void mouseInput(GLFWwindow *window, int button, int action, int mods);
        static void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods);

    private:
        GLFWwindow *window;
    };

}  // namespace GameEngine