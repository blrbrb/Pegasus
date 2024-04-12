cmake_minimum_required(VERSION 3.0)

# Set the project name
project(libnewpipe)

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define your source files
set(SOURCES 
    src/libnewpipe.cpp
    src/exceptions.cpp 
    src/linkhandler.cpp 
    src/mediainfo.cpp 
)
# Create the shared library
add_library(libnewpipe SHARED ${SOURCES})

# Set include directories
target_include_directories(Pegasus PUBLIC include)

if(WIN32)
    # Windows-specific settings
    target_compile_options(MyLibrary PRIVATE -Wall -Wextra -pedantic /Dll)
elseif(APPLE) # set the LIBRARY_PATH env variable for clang by supplying it with -L, should be default global idk
    # macOS-specific settings
    target_compile_options(libnewpipe PRIVATE -Wall  -pedantic -L "")
else() 
    # Set the compiler to g++
    set(CMAKE_CXX_COMPILER g++)
    # Linux-specific settings 
    target_compile_options(libnewpipe PRIVATE -Wall -pedantic )
endif()





# Optionally, set compiler flags
# For example, to enable all warnings:
#target_compile_options(MyLibrary PRIVATE -Wall -Wextra -pedantic)

# Optionally, set installation rules
# For example:
# install(TARGETS libnewpipe DESTINATION lib)
# install(DIRECTORY include/ DESTINATION include)
