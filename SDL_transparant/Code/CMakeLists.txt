file(GLOB MAIN_SRC "main.cpp")
file(GLOB_RECURSE UTILITIES_SRC "Utilities/*.cpp")
file(GLOB_RECURSE AUDIO_SRC "AudioPlayer/*.cpp")
add_executable(sdl3_transparent_window ${MAIN_SRC} ${UTILITIES_SRC} ${AUDIO_SRC})

# Collect all subdirectories under Utilities (not files)
file(GLOB UTILITIES_SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Utilities/* ${CMAKE_CURRENT_SOURCE_DIR}/AudioPlayer/*)
set(UTILITIES_INCLUDE_DIRS)
foreach(subdir ${UTILITIES_SUBDIRS})
  if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}")
    list(APPEND UTILITIES_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}")
  endif()
endforeach()

target_include_directories(sdl3_transparent_window PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Utilities ${UTILITIES_INCLUDE_DIRS})

# Dependencies Linux/Windows
if(WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(SDL3_WIN_PACKAGE_ROOT "${CMAKE_SOURCE_DIR}/WinInclude/SDL3-devel-3.4.4-mingw/SDL3-3.4.4")
  if(EXISTS "${SDL3_WIN_PACKAGE_ROOT}/cmake/SDL3Config.cmake")
    list(PREPEND CMAKE_PREFIX_PATH "${SDL3_WIN_PACKAGE_ROOT}")
  endif()

  find_package(SDL3 CONFIG REQUIRED)
  target_link_libraries(sdl3_transparent_window PRIVATE SDL3::SDL3)

  find_package(SDL3_image CONFIG QUIET)
  if(TARGET SDL3_image::SDL3_image)
    target_compile_definitions(sdl3_transparent_window PRIVATE HAS_SDL3_IMAGE=1)
    target_link_libraries(sdl3_transparent_window PRIVATE SDL3_image::SDL3_image)
  else()
    message(STATUS "SDL3_image non trouve: fallback BMP uniquement (SDL_LoadBMP)")
  endif()

  # Find and link sqlite3 for Windows (assumes sqlite3 is available in the environment)
  find_package(SQLite3 QUIET)
  if(SQLite3_FOUND)
    target_include_directories(sdl3_transparent_window PRIVATE ${SQLite3_INCLUDE_DIRS})
    target_link_libraries(sdl3_transparent_window PRIVATE ${SQLite3_LIBRARIES})
  else()
    message(STATUS "SQLite3 not found: please ensure sqlite3 is available and set up for Windows builds.")
  endif()
else()
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(SDL3 REQUIRED sdl3)
  pkg_check_modules(SDL3_IMAGE QUIET sdl3-image)
  pkg_check_modules(SQLITE3 REQUIRED sqlite3)

  target_include_directories(sdl3_transparent_window PRIVATE ${SDL3_INCLUDE_DIRS} ${SQLITE3_INCLUDE_DIRS})
  target_link_libraries(sdl3_transparent_window PRIVATE ${SDL3_LIBRARIES} ${SQLITE3_LIBRARIES})

  if(SDL3_IMAGE_FOUND)
    target_compile_definitions(sdl3_transparent_window PRIVATE HAS_SDL3_IMAGE=1)
    target_include_directories(sdl3_transparent_window PRIVATE ${SDL3_IMAGE_INCLUDE_DIRS})
    target_link_libraries(sdl3_transparent_window PRIVATE ${SDL3_IMAGE_LIBRARIES})
  else()
    message(STATUS "sdl3-image non trouve: fallback BMP uniquement (SDL_LoadBMP)")
  endif()
endif()

set_target_properties(sdl3_transparent_window PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)

# Embed absolute Assets root path into the binary
target_compile_definitions(sdl3_transparent_window
  PRIVATE ASSETS_ROOT_PATH="${CMAKE_SOURCE_DIR}/../Assets/"
)

# Copy Assets folder next to the built executable so runtime paths are stable
# add_custom_command(TARGET sdl3_transparent_window POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory
#       ${CMAKE_SOURCE_DIR}/../Assets
#       $<TARGET_FILE_DIR:sdl3_transparent_window>/Assets)

# Install rule to copy the executable to the top-level build directory
install(TARGETS sdl3_transparent_window
  RUNTIME DESTINATION ${CMAKE_BINARY_DIR})
