SET(FRAMEWORK_COMMON_HEADER 
Common/BaseApplication.h
Common/Config.h
Common/GfxConfiguration.h
Common/GfxConfiguration.h
Common/InputManager.h
Common/ShaderManager.h
Common/IApplication.h
Common/IRuntimeModule.h
Common/IShaderManager.h
Common/IBehaviour.h
Common/ISerializable.h
)

SET(FRAMEWORK_COMMON_SRC 
Common/InputManager.cpp
Common/BaseApplication.cpp
)

list(APPEND FRAMEWORK_HEADER ${FRAMEWORK_COMMON_HEADER})
list(APPEND FRAMEWORK_SRC ${FRAMEWORK_COMMON_SRC})


