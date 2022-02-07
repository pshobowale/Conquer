cmake_minimum_required(VERSION 3.0.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(Conquer VERSION 0.1.0)

file(GLOB source_files CONFIGURE_DEPENDS
    "main.cpp"
    "lib/*/*.cpp"
    "lib/*/*.h"
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

set(EXECUTABLE_NAME "Conquer")
add_executable(${EXECUTABLE_NAME} main.cpp)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

#CPack packaging
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


