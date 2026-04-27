# Toolchain MinGW (cross-compilation Linux -> Windows)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc CACHE FILEPATH "")
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++ CACHE FILEPATH "")
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres CACHE FILEPATH "")

# Prefix SDL3 local (package devel MinGW dans le repo)
set(SDL3_WIN_PACKAGE_ROOT "${CMAKE_CURRENT_LIST_DIR}/WinInclude/SDL3-devel-3.4.4-mingw/SDL3-3.4.4")
set(SDL3_WIN_ROOT "${SDL3_WIN_PACKAGE_ROOT}/x86_64-w64-mingw32")

# Permet a find_package(SDL3 CONFIG) de trouver WinInclude/.../cmake/SDL3Config.cmake
if(EXISTS "${SDL3_WIN_PACKAGE_ROOT}/cmake/SDL3Config.cmake")
	list(PREPEND CMAKE_PREFIX_PATH "${SDL3_WIN_PACKAGE_ROOT}")
endif()

# Evite de melanger includes/libs Linux avec la cible Windows
set(CMAKE_FIND_ROOT_PATH "${SDL3_WIN_ROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)

# Ajout du chemin WinInclude/ pour SQLite3
include_directories("${CMAKE_CURRENT_LIST_DIR}/WinInclude")

# SQLite3 include and library for Windows cross-compilation
set(SQLITE3_WIN_ROOT "${CMAKE_CURRENT_LIST_DIR}/WinInclude/sqlite-amalgamation-3530000")
include_directories("${SQLITE3_WIN_ROOT}")
link_directories("${SQLITE3_WIN_ROOT}")