cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

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

add_library(
  ghoulies_launcher_lib OBJECT
  source/lib.cpp source/file.cpp
  # source/graphics/model.cpp source/ghoulies/nd.cpp
  source/graphics/graphics.cpp source/ghoulies/bnl.cpp)

target_include_directories(
  ghoulies_launcher_lib ${warning_guard}
  PUBLIC "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>")

target_include_directories(ghoulies_launcher_lib
                           PRIVATE ${PROJECT_SOURCE_DIR}/source)

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
