cmake_minimum_required(VERSION 3.16)
project(sdl3_transparent_window)


# Utilisation conditionnelle de pkg-config :
if(NOT CMAKE_CROSSCOMPILING)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(SDL3 REQUIRED sdl3)
  pkg_check_modules(SDL3_IMAGE REQUIRED sdl3-image)
endif()

file(GLOB MAIN_SRC "main.cpp")
file(GLOB_RECURSE UTILITIES_SRC "Utilities/*.cpp")
add_executable(${PROJECT_NAME} ${MAIN_SRC} ${UTILITIES_SRC})



# Collect all subdirectories under Utilities (not files)
file(GLOB UTILITIES_SUBDIRS RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Utilities/*)
set(UTILITIES_INCLUDE_DIRS)
foreach(subdir ${UTILITIES_SUBDIRS})
  if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${subdir}")
    list(APPEND UTILITIES_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/${subdir}")
  endif()
endforeach()



# Pour la cross-compilation Windows, inclure et linker manuellement
if(CMAKE_CROSSCOMPILING)
  set(SDL3_WIN_ROOT "${CMAKE_SOURCE_DIR}/WinInclude/SDL3-devel-3.4.4-mingw/SDL3-3.4.4/x86_64-w64-mingw32")
  target_include_directories(sdl3_transparent_window PRIVATE ${SDL3_WIN_ROOT}/include ${CMAKE_SOURCE_DIR}/Utilities ${UTILITIES_INCLUDE_DIRS})
  target_link_libraries(sdl3_transparent_window PRIVATE -L${SDL3_WIN_ROOT}/lib -lSDL3)
else()
  target_include_directories(sdl3_transparent_window PRIVATE ${SDL3_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/Utilities ${UTILITIES_INCLUDE_DIRS})
  target_link_libraries(sdl3_transparent_window PRIVATE ${SDL3_LIBRARIES} ${SDL3_IMAGE_LIBRARIES})
endif()

set_target_properties(sdl3_transparent_window PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)

# Embed absolute Assets root path into the binary
target_compile_definitions(${PROJECT_NAME}
    PRIVATE ASSETS_ROOT_PATH="${CMAKE_SOURCE_DIR}/Assets/"
)

# Copy Assets folder next to the built executable so runtime paths are stable
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Assets
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/Assets)


# Install rule to copy the executable to the top-level build directory
install(TARGETS sdl3_transparent_window
        RUNTIME DESTINATION ${CMAKE_BINARY_DIR})
