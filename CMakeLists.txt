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
    src/Renderer/sprite.cpp
    src/Renderer/sprite.h 
    src/Renderer/sprite_animator.cpp
    src/Renderer/sprite_animator.h
    src/Renderer/vertex_buffer.cpp
    src/Renderer/vertex_buffer.h   
    src/Renderer/index_buffer.cpp
    src/Renderer/index_buffer.h
    src/Renderer/vertex_array.cpp
    src/Renderer/vertex_array.h
    src/Renderer/vertex_buffer_layout.cpp
    src/Renderer/vertex_buffer_layout.h
    src/Renderer/renderer.cpp
    src/Renderer/renderer.h

    src/Resources/resource_manager.cpp
    src/Resources/stb_image.h
    src/Resources/resource_manager.h
    
    src/System/timer.h
    src/System/timer.cpp  
    
    src/Physics/physics_engine.h
    src/Physics/physics_engine.cpp

    src/Game/game.cpp
    src/Game/game.h
    src/Game/level.cpp
    src/Game/level.h
    src/Game/GameObjects/game_object_interface.cpp
    src/Game/GameObjects/game_object_interface.h
    src/Game/GameObjects/tank.cpp
    src/Game/GameObjects/tank.h   
    src/Game/GameObjects/brick_wall.cpp
    src/Game/GameObjects/brick_wall.h
    src/Game/GameObjects/beton_wall.cpp
    src/Game/GameObjects/beton_wall.h 
    src/Game/GameObjects/trees.cpp
    src/Game/GameObjects/trees.h
    src/Game/GameObjects/ice.cpp
    src/Game/GameObjects/ice.h  
    src/Game/GameObjects/water.cpp
    src/Game/GameObjects/water.h    
    src/Game/GameObjects/eagle.cpp
    src/Game/GameObjects/eagle.h 
    src/Game/GameObjects/border.cpp
    src/Game/GameObjects/border.h

    res/shaders/sprite_v.vert
    res/shaders/sprite_f.frag
    res/resources.json
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

include_directories(external/rapidjson/include)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)