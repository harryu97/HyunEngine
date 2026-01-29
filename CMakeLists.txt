# Projects Settings
cmake_minimum_required (VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project (MyProject)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(engine)



# The main executable
add_executable(myapp
  src/main.cpp
  src/Game.h 
  src/Game.cpp
  src/TestObject.h 
  src/TestObject.cpp
  src/Player.h 
  src/Player.cpp
  src/Bullet.h 
  src/Bullet.cpp
  #add more source files in futures
)

target_link_libraries(myapp PRIVATE Engine)
include_directories(engine/lib/stb_image)
include_directories(engine/lib/json)


target_include_directories(myapp
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/engine/source
)
