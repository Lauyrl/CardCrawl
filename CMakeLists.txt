cmake_minimum_required(VERSION 3.22)
project(MyGame LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Debug Symbols in Debug Mode
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:/CS/CardCrawl/bin")

# Find SDL2
find_package(SDL2 REQUIRED CONFIG)
message(STATUS "SDL2 found at: ${SDL2_DIR}")

find_package(SDL2_image REQUIRED CONFIG)

# Add source files (Modify this if you have multiple files)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "source/*.cpp" "source/*/*.cpp")
add_executable(cc ${SOURCES})

set_target_properties(cc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "C:/CS/CardCrawl/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "C:/CS/CardCrawl/bin/Release"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "C:/CS/CardCrawl/bin/RelWithDebInfo"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "C:/CS/CardCrawl/bin/MinSizeRel"
)

target_link_libraries(cc PRIVATE SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image)

# Set output directory
set_target_properties(cc PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Enable warnings (optional but recommended)
if (MSVC)
    target_compile_options(cc PRIVATE /W4)
else()
    target_compile_options(cc PRIVATE -Wall -Wextra -Wpedantic)
endif()
