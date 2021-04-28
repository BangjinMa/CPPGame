
SET(FRAMEWORK_RENDER_PLATFORM_WINDOWS_HEADER 
Render/Platform/OpenGL/OpenGLApplication.h
Render/Platform/OpenGL/Shader.h
Render/Platform/OpenGL/OpenGLShaderManager.h
Render/Platform/OpenGL/GraphicsFunc.h
Render/Platform/OpenGL/imgui_impl_glfw.h
# Render/Platform/OpenGL/imgui_impl_opengl3.h
Render/Platform/OpenGL/SpecialModuleConfig.h
)

SET(FRAMEWORK_RENDER_PLATFORM_WINDOWS_SRC 
Render/Platform/OpenGL/Shader.cpp
Render/Platform/OpenGL/OpenGLApplication.cpp
Render/Platform/OpenGL/GraphicsFunc.cpp
Render/Platform/OpenGL/imgui_impl_glfw.cpp
# Render/Platform/OpenGL/imgui_impl_opengl3.cpp
Render/Platform/OpenGL/OpenGLShaderManager.cpp
)

list(APPEND FRAMEWORK_HEADER ${FRAMEWORK_RENDER_PLATFORM_WINDOWS_HEADER})
list(APPEND FRAMEWORK_SRC ${FRAMEWORK_RENDER_PLATFORM_WINDOWS_SRC})

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

link_libraries(imgui::imgui glfw glad::glad)