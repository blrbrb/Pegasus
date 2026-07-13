
file(GLOB Pegasus_SRC "*.cpp" ".c")
#add_compile_options(-fsanitize=address -g -fno-omit-frame-pointer)
#add_link_options(-fsanitize=address -g)
add_executable(Pegasus ${Pegasus_SRC})


#apply GTK3 compiler flags, and suppress return local address warnings.
# (for code in animationcomponent. Yes, it's supposed to do that)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wno-return-local-addr")

target_compile_features(Pegasus PRIVATE cxx_std_17)


target_link_libraries(Pegasus PRIVATE ImGui-SFML::ImGui-SFML SFML::Graphics SFML::Window SFML::System)
