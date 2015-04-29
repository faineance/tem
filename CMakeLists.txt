project(tem C)

cmake_minimum_required(VERSION 2.6)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules (VTE REQUIRED vte-2.91)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

link_directories (${VTE_LIBRARY_DIRS})
include_directories (${VTE_INCLUDE_DIRS})

add_executable(tem tem.c)

target_link_libraries(tem ${GTK3_LIBRARIES} ${VTE_LIBRARIES})