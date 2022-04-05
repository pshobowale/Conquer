cmake_minimum_required(VERSION 3.0.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(Conquer VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS
    "main.cpp"
    "lib/*/*.cpp"
    "lib/*/*.hpp"
    "lib/*/*.c"
)

message("\nFound this files:")
message(${SOURCE_FILES})
message("\n")

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

set(EXECUTABLE_NAME "Conquer")
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})


find_package(SDL2 REQUIRED)
find_package(SDL2_image)
include_directories(${EXECUTABLE_NAME} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

message( ${SDL2_IMAGE_INCLUDE_DIR})

#CPack packaging
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


