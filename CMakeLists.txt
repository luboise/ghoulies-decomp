cmake_minimum_required(VERSION 3.14)

add_compile_definitions(GLM_FORCE_LEFT_HANDED)

include(cmake/prelude.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  ghoulies_launcher
  VERSION 0.1.0
  DESCRIPTION
    "Launcher and player for Rare's Grabbed by The Ghoulies asset files"
  HOMEPAGE_URL "https://example.com/"
  LANGUAGES CXX)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

set(IMGUI_SOURCES
    external/imgui/backends/imgui_impl_sdl3.cpp
    external/imgui/backends/imgui_impl_sdlgpu3.cpp
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_demo.cpp)

add_library(ghoulies_launcher_lib # OBJECT
)

target_include_directories(ghoulies_launcher_lib
                           PRIVATE "${PROJECT_SOURCE_DIR}/external/imgui")

target_sources(
  ghoulies_launcher_lib
  PRIVATE source/lib.cpp
          source/file.cpp
          source/graphics/material.cpp
          source/graphics/model.cpp
          source/graphics/graphics.cpp
          source/graphics/model.cpp
          source/ghoulies/bnl.cpp
          source/ghoulies/game.cpp
          source/ghoulies/model.cpp
          source/ghoulies/nd.cpp
          source/ghoulies/script.cpp
          source/ghoulies/assets/marker.cpp
          source/ghoulies/objects/actor/actor.cpp
          source/ghoulies/objects/avatar/avatar.cpp
          source/ghoulies/objects/weapon/weapon.cpp
          # utils
          source/utils/images.cpp
          source/menu/menu.cpp
          ${IMGUI_SOURCES})

target_include_directories(
  ghoulies_launcher_lib ${warning_guard}
  PUBLIC "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
         PRIVATE"${PROJECT_SOURCE_DIR}/source")

target_compile_features(ghoulies_launcher_lib PUBLIC cxx_std_23)

find_package(fmt REQUIRED)
find_package(glm REQUIRED)
find_package(libdeflate REQUIRED)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

target_link_libraries(
  ghoulies_launcher_lib PRIVATE fmt::fmt SDL3::SDL3 glm::glm
                                libdeflate::libdeflate_shared)

# ---- Declare executable ----

add_executable(ghoulies_launcher_exe source/main.cpp)
add_executable(ghoulies_launcher::exe ALIAS ghoulies_launcher_exe)

set_property(TARGET ghoulies_launcher_exe PROPERTY OUTPUT_NAME
                                                   ghoulies_launcher)

target_compile_features(ghoulies_launcher_exe PRIVATE cxx_std_23)

target_link_libraries(ghoulies_launcher_exe PRIVATE ghoulies_launcher_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT ghoulies_launcher_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
    AUTHOR_WARNING
      "Developer mode is intended for developers of ghoulies_launcher")
endif()

include(cmake/dev-mode.cmake)

if(GHOULIES_LAUNCHER_TESTS)
  add_subdirectory(test)
endif()
