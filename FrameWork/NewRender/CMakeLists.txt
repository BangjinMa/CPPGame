add_subdirectory(Core)

if(WIN32)
    add_subdirectory(GLSL)
endif()

add_subdirectory(Test)