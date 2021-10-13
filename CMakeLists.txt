cmake_minimum_required(VERSION 3.12)

project(Pacman2D)

find_package(OpenGL REQUIRED)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)

add_executable(Pacman2D main.cpp "shaders/GameShader.h" "headers/Application.h" "headers/Map.h" "headers/Map.cpp" "headers/Libraries.h" "headers/Wall.h" "headers/Wall.cpp" "headers/Pellet.h" "headers/Pellet.cpp" "headers/Window.h" "headers/Window.cpp" "headers/Pacman.h" "headers/Ghost.h" "headers/Pacman.cpp" "headers/Ghost.cpp" "headers/GameObject.h" "headers/GameObject.cpp" "headers/stb_image.h" "headers/Texture.h" "headers/Shader.h" "headers/Shader.cpp")
target_link_libraries(Pacman2D glfw glad glm OpenGL::GL ${CMAKE_DL_LIBS})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/level0
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/textures
  ${CMAKE_CURRENT_BINARY_DIR}/textures)

