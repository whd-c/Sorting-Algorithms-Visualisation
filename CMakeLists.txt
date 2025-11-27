cmake_minimum_required(VERSION 3.28)

project(SAV C CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(RAYLIB_VERSION 5.5)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG ${RAYLIB_VERSION}
    CMAKE_ARGS -DBUILD_EXAMPLES=OFF
)

FetchContent_MakeAvailable(raylib)

set(SOURCE_FILES
    src/main.cpp
    src/program.cpp
    src/textbox.cpp
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    ${RAYLIB_PLATFORM_DEFINITIONS}
)