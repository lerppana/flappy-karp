cmake_minimum_required(VERSION 3.21.2)

project(flappykarp CXX)

find_package(engine CONFIG REQUIRED)

include(engine_create)

engine_create_plugin(flappykarp
        PROJECT_FILE
        "${CMAKE_CURRENT_LIST_DIR}/flappykarp.project"

        SOURCE_FILES
            src/plugin.cpp
            src/scenes/game.cpp
            src/scenes/load.cpp
            src/systems/infinite_scroller.cpp
            src/systems/player_controller.cpp

        INCLUDE_FILES
            src/components/pipe.hpp
            src/components/scrollable.hpp
            src/scenes/game.hpp
            src/scenes/load.hpp
            src/systems/infinite_scroller.hpp
            src/systems/player_controller.hpp
            src/tags.hpp
        )

engine_create_launcher(
        SOURCE_DIR "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include/engine/launcher"
        PROJECT_FILE "${CMAKE_SOURCE_DIR}/flappykarp.project"
)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/engine.hxx)

engine_install_plugin(${PROJECT_NAME})