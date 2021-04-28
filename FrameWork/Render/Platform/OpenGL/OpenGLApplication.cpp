#include "OpenGLApplication.h"

#include <stdio.h>
#include <tchar.h>

#include "Event/EventDispatcherManager.h"
#include "Event/KeyEventDispatcher.h"
#include "InputManager.h"
#include "Render/GraphicsManager.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"

namespace EventSystem
{
    extern EventDispatcherManager *g_pEventDispatcherManager;
}
using namespace EventSystem;

namespace GameEngine
{
    extern InputManager *g_pInputManager;
    extern GraphicsManager *g_pGraphicsManager;

    OpenGLApplication::OpenGLApplication(GfxConfiguration &config) : BaseApplication(config)
    {
    }

    int OpenGLApplication::Initialize()
    {
        int result = 0;
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // glfw window creation
        // --------------------
        window = glfwCreateWindow(m_Config.screenWidth, m_Config.screenHeight, "CPPGame", NULL, NULL);
        if (window == NULL)
        {
            printf("Failed to create GLFW window");
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            printf("Failed to initialize GLAD");
            return -1;
        }

        auto config = GetGfxConfiguration();
        glViewport(0, 0, config.screenWidth, config.screenHeight);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        // IMGUI_CHECKVERSION();
        // ImGui::CreateContext();
        // ImGui::StyleColorsDark();
        // ImGui_ImplGlfw_InitForOpenGL(window, true);
        // ImGui_ImplOpenGL3_Init("#version 420");

        glfwSetMouseButtonCallback(window, MouseInput);
        glfwSetKeyCallback(window, KeyInput);

        return result;
    }

    void OpenGLApplication::Finalize()
    {
        // Cleanup
        // ImGui_ImplOpenGL3_Shutdown();
        // ImGui_ImplGlfw_Shutdown();
        // ImGui::DestroyContext();
    }

    void OpenGLApplication::Tick(float deltaTime)
    {
        this->m_bQuit = glfwWindowShouldClose(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        g_pGraphicsManager->Draw(deltaTime);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void OpenGLApplication::MouseInput(GLFWwindow *window, int key, int action, int mods)
    {
    }

    void OpenGLApplication::KeyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        KeyEventData *data = new KeyEventData();
        data->key = key;
        data->scancode = scancode;
        data->action = action;
        data->mods = mods;
        g_pEventDispatcherManager->SendEvent(data);
    }

}  // namespace GameEngine