cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Engine)

set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../assets/")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
                ${PROJECT_BINARY_DIR}/config.h
)
set(PROJECT_SOURCE_FILES
 source/Engine.h
 source/Engine.cpp
 source/Application.h
 source/Application.cpp 
 source/input/InputManager.h 
 source/input/InputManager.cpp
 source/graphics/ShaderProgram.h 
 source/graphics/ShaderProgram.cpp
 source/graphics/GraphicsAPI.h 
 source/graphics/GraphicsAPI.cpp
 source/render/Material.h  
 source/render/Material.cpp 
 source/render/Mesh.cpp
 source/render/Mesh.h 
 source/graphics/VertexLayout.h
 source/render/RenderQueue.h 
 source/render/RenderQueue.cpp
 source/scene/GameObject.h 
 source/scene/GameObject.cpp 
 source/scene/Scene.h 
 source/scene/Scene.cpp
 source/scene/Component.h 
 source/scene/Component.cpp
 source/scene/components/MeshComponent.h 
 source/scene/components/MeshComponent.cpp
 source/scene/components/CameraComponent.h 
 source/scene/components/CameraComponent.cpp
 source/scene/components/PlayerControllerComponent.h
 source/scene/components/PlayerControllerComponent.cpp
 source/io/FileSystem.h 
 source/io/FileSystem.cpp
 source/graphics/Texture.h 
 source/graphics/Texture.cpp
 source/scene/components/LightComponent.h 
 source/scene/components/LightComponent.cpp
 source/Common.h 
 source/scene/components/AnimationComponent.h 
 source/scene/components/AnimationComponent.cpp
 source/physics/Collider.h 
 source/physics/Collider.cpp
 source/physics/PhysicsManager.h
 source/physics/PhysicsManager.cpp
 source/physics/RigidBody.h
 source/physics/RigidBody.cpp 
 source/scene/components/PhysicsComponent.h 
 source/scene/components/PhysicsComponent.cpp
 source/physics/KinematicCharacterController.h 
 source/physics/KinematicCharacterController.cpp
 source/audio/AudioManager.h 
 source/audio/AudioManager.cpp
 source/audio/Audio.h 
 source/audio/Audio.cpp
 source/scene/components/AudioComponent.h 
 source/scene/components/AudioComponent.cpp
 source/scene/components/AudioListenerComponent.h 
 source/scene/components/AudioListenerComponent.cpp


)

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})


add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

add_subdirectory(lib/bullet3-3.25 EXCLUDE_FROM_ALL)
#include_directories(lib/stb_image)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR} )

add_library(miniaudio INTERFACE)
if(UNIX AND NOT APPLE)
  target_link_libraries(miniaudio INTERFACE dl pthread m)
endif()
if(WIN32)
  target_link_libraries(miniaudio INTERFACE winmm user32 ole32)
endif()
if(APPLE)
  find_library(COREAUDIO_FRAMEWORK CoreAudio)
  find_library(AUDIOTOOLBOX_FRAMEWORK AudioToolBox)
  find_library(AUDIOUNIT_FRAMEWORK AudioUnit)
  find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)
  target_link_libraries(miniaudio INTERFACE
    ${COREAUDIO_FRAMEWORK}
    ${AUDIOUNIT_FRAMEWORK}
    ${AUDIOTOOLBOX_FRAMEWORK}
    ${COREFOUNDATION_FRAMEWORK}
  )
endif()

#Bullet 
option(BUILD_UNIT_TESTS OFF)
option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_SHARED_LIBS OFF)


target_link_libraries(Engine 
  PUBLIC glfw
  PUBLIC libglew_static
  PUBLIC glm

  PUBLIC BulletDynamics
  PUBLIC BulletCollision
  PUBLIC LinearMath
  PUBLIC miniaudio
)


# Make Engine headers available (PUBLIC so myapp can use them)
target_include_directories(Engine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/stb_image
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/json 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/cgltf
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/bullet3-3.25/src
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/miniaudio 
  )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${ASSETS_DIR}
  ${CMAKE_BINARY_DIR}/../assets
)
