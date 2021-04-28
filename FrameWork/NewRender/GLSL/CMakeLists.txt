
file(GLOB_RECURSE HEADER_FILES *.h)
file(GLOB_RECURSE SOURCE_CPP_FILES *.cpp *.cc)
file(GLOB_RECURSE SOURCE_C_FILES *.c)

set(ALL_FILES
    ${HEADER_FILES}
    ${SOURCE_CPP_FILES}
    ${SOURCE_C_FILES}
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
link_libraries(glfw glad::glad Core)

add_library(GLSL ${HEADER_FILES} ${ALL_FILES})