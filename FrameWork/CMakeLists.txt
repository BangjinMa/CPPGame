set(FRAMEWORK_HEADER
ModuleConfig.h
)
set(FRAMEWORK_SRC
main.cpp)

add_subdirectory(NewRender)

include(Common/CMakeLists.txt)
include(Scene/CMakeLists.txt)
include(File/CMakeLists.txt)
include(Math/CMakeLists.txt)
include(Render/CMakeLists.txt)
include(Logger/CMakeLists.txt)
include(Memory/CMakeLists.txt)
include(Utils/CMakeLists.txt)
include(Event/CMakeLists.txt)

list(APPEND FRAMEWORK_SRC ${FRAMEWORK_HEADER})

add_library(Framework ${FRAMEWORK_SRC})

find_package(glm CONFIG REQUIRED)
find_package(cjson CONFIG REQUIRED)

target_link_libraries(Framework PRIVATE cjson glm GLSL)
