cmake_minimum_required(VERSION 3.16)
project(sdl3_transparent_window)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)
pkg_check_modules(SDL3_IMAGE REQUIRED sdl3-image)

add_executable(sdl3_transparent_window main.cpp)

target_include_directories(sdl3_transparent_window PRIVATE ${SDL3_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS})
target_link_libraries(sdl3_transparent_window PRIVATE ${SDL3_LIBRARIES} ${SDL3_IMAGE_LIBRARIES})

set_target_properties(sdl3_transparent_window PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)

# Install rule to copy the executable to the top-level build directory
install(TARGETS sdl3_transparent_window
        RUNTIME DESTINATION ${CMAKE_BINARY_DIR})
