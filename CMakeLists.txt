cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(PROJECT_NAME BattleCity)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(
        CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} /JMC"
    )
else()
    set(
        CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -pthread -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-implicit-fallthrough"
    )
endif()

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/Renderer/shader_program.cpp
    src/Renderer/shader_program.h
    src/Renderer/texture_2D.cpp
    src/Renderer/texture_2D.h
    src/Resources/resource_manager.cpp
    src/Resources/resource_manager.h
    src/Resources/stb_image.h
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(external/glm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)