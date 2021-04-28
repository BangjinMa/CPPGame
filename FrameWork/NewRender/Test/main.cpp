
#include "../GLSL/GLSLDevice.h"
#include "../GLSL/GLSLFunc.h"
#include "../GLSL/GLSLTexture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace GameEngine::ger;
int main(int argc, char *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(1024, 1024, "CPPGame", NULL, NULL);
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

    Device *device = new GLSLDevice();
    TextureInfo info = {TextureType::TEX2D, Format::RGBA8, 1024, 1024};
    Texture *texture = device->CreateTexture(info);
    unsigned char *c = new unsigned char[1024 * 1024 * 4 * 8];
    GLSLFuncCopyBuffersToTexture((GLSLDevice *)device, c, ((GLSLTexture *)texture)->GetGPUTexture());
    texture->Destroy();
    delete texture;
    delete device;
    delete c;
    return 0;
}
