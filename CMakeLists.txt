cmake_minimum_required(VERSION 3.28)


#for clangd, and code editors like Kate
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Set the project name
project("Pegasus" LANGUAGES CXX)

# Fetch SFML
add_subdirectory(share)
add_subdirectory(src)
