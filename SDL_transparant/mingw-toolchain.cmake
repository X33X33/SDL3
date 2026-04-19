# Désactive l'utilisation des includes système Linux
set(CMAKE_SYSROOT "")
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

# Chemins SDL3 pour Windows cross-compilation
set(SDL3_WIN_ROOT "${CMAKE_SOURCE_DIR}/WinInclude/SDL3-devel-3.4.4-mingw/SDL3-3.4.4/x86_64-w64-mingw32")
set(CMAKE_INCLUDE_PATH "${SDL3_WIN_ROOT}/include" ${CMAKE_INCLUDE_PATH})
set(CMAKE_LIBRARY_PATH "${SDL3_WIN_ROOT}/lib" ${CMAKE_LIBRARY_PATH})
link_directories("${SDL3_WIN_ROOT}/lib")
include_directories("${SDL3_WIN_ROOT}/include")

# Pour éviter d'utiliser les includes natifs Linux
set(CMAKE_FIND_ROOT_PATH "${SDL3_WIN_ROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Ajout des chemins SDL3 pour Windows
set(SDL3_WIN_ROOT "${CMAKE_SOURCE_DIR}/WinInclude/SDL3-devel-3.4.4-mingw/SDL3-3.4.4/x86_64-w64-mingw32")
set(CMAKE_INCLUDE_PATH "${SDL3_WIN_ROOT}/include" ${CMAKE_INCLUDE_PATH})
set(CMAKE_LIBRARY_PATH "${SDL3_WIN_ROOT}/lib" ${CMAKE_LIBRARY_PATH})
link_directories("${SDL3_WIN_ROOT}/lib")
include_directories("${SDL3_WIN_ROOT}/include")

# Chemins de recherche pour les bibliothèques
set(CMAKE_SYSROOT "")
