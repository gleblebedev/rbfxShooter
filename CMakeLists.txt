cmake_minimum_required (VERSION 3.14)

# Name your project. Can be anything.
project (ShooterTemplate)

# Minimal supported C++ version.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set binary output directories. Changing these paths will require you adjusting your resource path configuration!
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include cloned engine directory in a build.
add_subdirectory(rbfx)

# Define executable name.
add_subdirectory (src)

# Link to game engine library.
target_link_libraries(ShooterTemplate Urho3D)