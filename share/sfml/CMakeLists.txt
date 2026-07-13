message(STATUS "Fetching SFML...")

set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_NETWORK FALSE)
set(SFML_BUILD_AUDIO FALSE)
FetchContent_MakeAvailable(sfml)
