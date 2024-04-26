cmake_minimum_required(VERSION 3.0)

# Set the project name
project(Pegasus)
set(CMAKE_CXX_FLAGS "-Wreturn-local-addr ")


# Add include directories from the fetched content
include_directories(
    ${boost_property_tree_SOURCE_DIR}/include
    ${boost_bimap_SOURCE_DIR}/include
    ${SFML_SOURCE_DIR}/include
    ${imgui_sfml_SOURCE_DIR}/include
    ${MiguelMJ_Candle_SOURCE_DIR}/include
    ${Pegasus_SOURCE_DIR}/src/include
    
)

#Define the sources 
set(SOURCES
    ${Pegasus_SOURCE_DIR}/src/State.cpp
    ${Pegasus_SOURCE_DIR}/src/MainMenuState.cpp
    ${Pegasus_SOURCE_DIR}/src/GameState.cpp
    ${Pegasus_SOURCE_DIR}/src/BattleState.cpp
    ${Pegasus_SOURCE_DIR}/src/Entity.cpp
    ${Pegasus_SOURCE_DIR}/src/Enemy.cpp
    ${Pegasus_SOURCE_DIR}/src/animationComponet.cpp
    ${Pegasus_SOURCE_DIR}/src/BattleGUI.cpp
    ${Pegasus_SOURCE_DIR}/src/Blerb.cpp
    ${Pegasus_SOURCE_DIR}/src/Blrb.cpp
    ${Pegasus_SOURCE_DIR}/src/CharacterEditorState.cpp
    ${Pegasus_SOURCE_DIR}/src/CharacterTab.cpp
    ${Pegasus_SOURCE_DIR}/src/DefaultMode.cpp
    ${Pegasus_SOURCE_DIR}/src/DialougeSystem.cpp
    ${Pegasus_SOURCE_DIR}/src/easylogging++.cc
    ${Pegasus_SOURCE_DIR}/src/EditorModes.cpp
    ${Pegasus_SOURCE_DIR}/src/EditorState.cpp
    ${Pegasus_SOURCE_DIR}/src/EnemyEditorMode.cpp
    ${Pegasus_SOURCE_DIR}/src/EnemySpawner.cpp
    ${Pegasus_SOURCE_DIR}/src/EnviornmentalMode.cpp
    ${Pegasus_SOURCE_DIR}/src/Game.cpp
    ${Pegasus_SOURCE_DIR}/src/GraphicsSettings.cpp
    ${Pegasus_SOURCE_DIR}/src/GUI.cpp
    ${Pegasus_SOURCE_DIR}/src/hitboxcomponet.cpp
    ${Pegasus_SOURCE_DIR}/src/imgui_draw.cpp
    ${Pegasus_SOURCE_DIR}/src/imgui_impl_opengl3.cpp
    ${Pegasus_SOURCE_DIR}/src/imgui_stdlib.cpp
    ${Pegasus_SOURCE_DIR}/src/imgui_tables.cpp
    ${Pegasus_SOURCE_DIR}/src/imgui_widgets.cpp
    ${Pegasus_SOURCE_DIR}/src/imgui-SFML.cpp
    ${Pegasus_SOURCE_DIR}/src/imgui.cpp
    ${Pegasus_SOURCE_DIR}/src/Inventory.cpp
    ${Pegasus_SOURCE_DIR}/src/Lantern.cpp
    ${Pegasus_SOURCE_DIR}/src/Level.cpp
    ${Pegasus_SOURCE_DIR}/src/Levels.cpp
    ${Pegasus_SOURCE_DIR}/src/Line.cpp
    ${Pegasus_SOURCE_DIR}/src/main.cpp
    ${Pegasus_SOURCE_DIR}/src/NormalTile.cpp
    ${Pegasus_SOURCE_DIR}/src/ObjectTile.cpp
    ${Pegasus_SOURCE_DIR}/src/PauseMenu.cpp
    ${Pegasus_SOURCE_DIR}/src/PhysicsComponents.cpp
    ${Pegasus_SOURCE_DIR}/src/PlayerGUITabs.cpp
    ${Pegasus_SOURCE_DIR}/src/PlayerGUI.cpp
    ${Pegasus_SOURCE_DIR}/src/SettingsState.cpp
    ${Pegasus_SOURCE_DIR}/src/ShaderEditorMode.cpp
    ${Pegasus_SOURCE_DIR}/src/SkillComponent.cpp
    ${Pegasus_SOURCE_DIR}/src/StatusComponet.cpp
    ${Pegasus_SOURCE_DIR}/src/Tab.cpp
    ${Pegasus_SOURCE_DIR}/src/Tile.cpp
    ${Pegasus_SOURCE_DIR}/src/TileMap.cpp
    ${Pegasus_SOURCE_DIR}/src/Player.cpp
    ${Pegasus_SOURCE_DIR}/src/EnemySystem.cpp
)

add_executable(Pegasus ${SOURCES})

# Link libraries built from the fetched content to your project

target_link_libraries(Pegasus 
  sfml-system 
  sfml-window 
  sfml-graphics
  sfml-audio 
  GL
  -l:libCandle-s.a
)

target_compile_features(Pegasus PRIVATE cxx_std_20)





