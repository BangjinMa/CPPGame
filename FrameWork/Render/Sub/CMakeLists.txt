SET(FRAMEWORK_RENDER_SUB_HEADER 
Render/Sub/ForwardPass.h
Render/Sub/DeferredPass.h
Render/Sub/CubPass.h
Render/Sub/ShadowPass.h
Render/Sub/CSMTest.h
)

SET(FRAMEWORK_RENDER_SUB_SRC 
Render/Sub/ShadowPass.cpp
)

list(APPEND FRAMEWORK_HEADER ${FRAMEWORK_RENDER_SUB_HEADER})
list(APPEND FRAMEWORK_SRC ${FRAMEWORK_RENDER_SUB_SRC})