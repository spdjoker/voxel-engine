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

find_path(EXTERNAL_PATH NAMES glfw-3.3.8/)
set(GLFW_PATH ${EXTERNAL_PATH}/glfw-3.3.8)
set(GLFW_LIBRARIES ${GLFW_PATH}/lib/x64/libglfw3.a)
include_directories(${GLFW_PATH}/include)

set(GLEW_PATH ${EXTERNAL_PATH}/glew-2.1.0)
set(GLEW_LIBRARIES ${GLEW_PATH}/lib/x64/libglew32s.a)
include_directories(${GLEW_PATH}/include)

set(FMT_PATH ${EXTERNAL_PATH}/fmt-10.1.0)
set(FMT_LIBRARIES ${FMT_PATH}/build/libfmt.a)
include_directories(${FMT_PATH}/include)

# file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

set(SOURCES
  src/main.cpp

  # SRC/JKR/ENGINE
  # src/jkr/components/camera.cpp
  # src/jkr/components/camera.hpp
  # src/jkr/components/transform.cpp
  # src/jkr/components/transform.hpp

  # SRC/JKR/ENGINE
  src/jkr/engine/application.cpp
  src/jkr/engine/application.hpp
  src/jkr/engine/input.cpp
  src/jkr/engine/input.hpp
  src/jkr/engine/input_enums.hpp
  
  # SRC/JKR/GRAPHICS
  src/jkr/graphics/shader.cpp
  src/jkr/graphics/shader.hpp
  # src/jkr/graphics/texture.cpp
  # src/jkr/graphics/texture.hpp
  src/jkr/graphics/objects/ebo.cpp
  src/jkr/graphics/objects/ebo.hpp
  src/jkr/graphics/objects/vao.cpp
  src/jkr/graphics/objects/vao.hpp
  src/jkr/graphics/objects/vbo.cpp
  src/jkr/graphics/objects/vbo.hpp

  # SRC/JKR/TYPES
  src/jkr/types/common.hpp

  # SRC/JKR/UTIL
  src/jkr/util/event_flags.hpp
  src/jkr/util/stb_image.h
  )

# Preprocessor Definitions 
add_definitions(-DSTB_IMAGE_IMPLEMENTATION)

# Console Build (DEBUG)
add_executable(${BUILD_NAME} ${SOURCES})

# Add the paths to the dependency libraries
target_link_libraries(${BUILD_NAME} PRIVATE ${GLEW_LIBRARIES})
target_link_libraries(${BUILD_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${BUILD_NAME} PRIVATE ${GLFW_LIBRARIES})
target_link_libraries(${BUILD_NAME} PRIVATE ${FMT_LIBRARIES})
target_include_directories(${BUILD_NAME} PUBLIC ${EXTERNAL_PATH}/glm-master)
target_compile_definitions(${BUILD_NAME} PRIVATE GLEW_STATIC)
