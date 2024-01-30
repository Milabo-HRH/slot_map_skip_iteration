cmake_minimum_required(VERSION 2.8.12)

# if (MSVC)
#   set(CMAKE_VS_GLOBALS "EnableASAN=true")
# endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(PROJ_NAME SlotMapTest)
project(${PROJ_NAME})

set (CMAKE_CXX_STANDARD 20)

set(TEST_SOURCES 
  SlotMapTest01.cpp
  SlotMapTest02.cpp
  SlotMapTest03.cpp
  SlotMapTest04.cpp
)

add_executable(${PROJ_NAME} ${TEST_SOURCES})

if(MSVC)
  target_compile_options(${PROJ_NAME} PRIVATE /W4 /WX)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
  target_compile_options(${PROJ_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# add slot_map
add_subdirectory("${PROJECT_SOURCE_DIR}/slot_map")
target_link_libraries(${PROJ_NAME} slot_map)

# Define the slot_map version
option(LOW_COMPLEXITY "Use low complexity slot map implementation" OFF)
option(ORDERED "Use ordered slot map implementation" OFF)

if(LOW_COMPLEXITY)
  add_definitions(-DLOW_COMPLEXITY)
elseif(ORDERED)
  add_definitions(-DORDERED)
endif()

# add gtest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")
target_link_libraries(${PROJ_NAME} gtest_main)


