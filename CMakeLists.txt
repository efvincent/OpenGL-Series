cmake_minimum_required(VERSION 3.30)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)
set (TARGET_NAME ep23)
set (PROJECT_NAME ep23)

project($PROJECT_NAME)

# Add the DEBUG definition for debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(-DDEBUG)
endif()

# Tell CMake where to find vcpkg's CMake toolchain file
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE PATH "")

# options
set(USE_OPENGL "Enable or disable OpenGL dependency" ON)
set(USE_GLIMAGE "Enable GL Image library" ON)

# set up the computation units to be compiled for the target executable
add_executable(${TARGET_NAME}
  src/vendor/stb_image.cpp
  src/main.cpp
  src/bufferLayout.cpp
  src/vertexArray.cpp
  src/vertexBuffer.cpp
  src/indexBuffer.cpp
  src/shader.cpp
  src/shaderCompiler.cpp
  src/renderer.cpp
  src/texture.cpp
  src/glAssert.cpp)

# package management
IF (USE_OPENGL)
  set (CMAKE_TOOLCHAIN_FILE "{VCPKG_ROOT}/scripts/buildsystems/vcpkg.make" CACHE PATH "")
  IF (USE_OPENGL)
    find_package(glfw3 CONFIG REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(GLUT REQUIRED)
    find_package(glm REQUIRED)
    find_package(imgui CONFIG REQUIRED)
  ENDIF()
ENDIF()

# Link your executable to the GLFW3 libraries
target_link_libraries(${TARGET_NAME} PRIVATE
  glfw
  OpenGL::GL
  GLEW::GLEW
  GLUT::GLUT
  imgui::imgui)

target_link_libraries(${TARGET_NAME} PRIVATE glm::glm)

target_include_directories(${TARGET_NAME}
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
