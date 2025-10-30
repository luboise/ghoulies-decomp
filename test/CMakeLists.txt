# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(ghoulies_launcherTests LANGUAGES CXX)

# ---- Dependencies ----

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(ghoulies_launcher_test source/ghoulies_launcher_test.cpp)
target_link_libraries(ghoulies_launcher_test PRIVATE ghoulies_launcher_lib
                                                     Catch2::Catch2WithMain)
target_compile_features(ghoulies_launcher_test PRIVATE cxx_std_23)

target_include_directories(ghoulies_launcher_test PRIVATE "../source")

catch_discover_tests(ghoulies_launcher_test)

# target_sources(ghoulies_launcher_test PRIVATE ../source/graphics/graphics.cpp)

# ---- End-of-file commands ----

add_folders(Test)
