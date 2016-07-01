project(lame_task)
cmake_minimum_required(VERSION 2.8)

set(LAME ../include)

add_definitions(
  -O0
  -Wall
  -g3
  -std=c++11
)
aux_source_directory(. SRC_LIST)
include_directories(
  ${LAME}
)
add_library(libmp3lame STATIC IMPORTED)
if (WIN32)
set_target_properties(libmp3lame PROPERTIES IMPORTED_LOCATION ../lib/libmp3lame.lib)
else()
set_target_properties(libmp3lame PROPERTIES IMPORTED_LOCATION ../lib/libmp3lame.a)
endif()
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}
  libmp3lame
  pthread
)

