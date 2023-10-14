cmake_minimum_required(VERSION 3.12)
project(world VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(BUILD_NAME world)

# Include the source directory
include_directories(src)
# Include dependencies Configure and add OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_path(GLFW_PATH NAMES glfw-3.3.8/)
set(GLFW_PATH ${GLFW_PATH}/glfw-3.3.8)
set(GLFW_LIBRARIES ${GLFW_PATH}/lib/x64/libglfw3.a)
include_directories(${GLFW_PATH}/include)

find_path(GLEW_PATH NAMES glew-2.1.0/)
set(GLEW_PATH ${GLEW_PATH}/glew-2.1.0)
set(GLEW_LIBRARIES ${GLEW_PATH}/lib/x64/libglew32s.a)
include_directories(${GLEW_PATH}/include)

message(${GLFW_LIBRARIES})
# file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

set(SOURCES
  src/main.cpp

  src/application.hpp
  src/application.cpp

  src/engine/input_enums.hpp
  src/engine/input.hpp
  src/engine/input.cpp

  src/types/vector2i.hpp
  src/types/vector2i.cpp
  )

# Console Build (DEBUG)
add_executable(${BUILD_NAME} ${SOURCES})

# Add the paths to the dependency libraries
target_link_libraries(${BUILD_NAME} PRIVATE ${GLEW_LIBRARIES})
target_link_libraries(${BUILD_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${BUILD_NAME} PRIVATE ${GLFW_LIBRARIES})
target_compile_definitions(${BUILD_NAME} PRIVATE GLEW_STATIC)
