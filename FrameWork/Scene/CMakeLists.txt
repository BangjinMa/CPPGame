include(Scene/Parser/CMakeLists.txt)

SET(FRAMEWORK_SCENE_HEADER 
Scene/Camera.h
Scene/ClassIDs.h
Scene/Component.h
Scene/GameObject.h
Scene/Light.h
Scene/Mesh.h
Scene/Object.h
Scene/Renderer.h
Scene/Scene.h
Scene/SceneManager.h
Scene/Texture.h
Scene/Transform.h
Scene/Cube.h
Scene/AssetManager.h
Scene/BoundingBox.h
Scene/Frustum.h
Scene/IntersectionTests.h
)

SET(FRAMEWORK_SCENE_SRC 
Scene/Camera.cpp
Scene/GameObject.cpp
Scene/Renderer.cpp
Scene/Scene.cpp
Scene/SceneManager.cpp
Scene/Transform.cpp
Scene/Cube.cpp
Scene/Component.cpp
Scene/AssetManager.cpp
Scene/BoundingBox.cpp
)

list(APPEND FRAMEWORK_HEADER ${FRAMEWORK_SCENE_HEADER})
list(APPEND FRAMEWORK_SRC ${FRAMEWORK_SCENE_SRC})