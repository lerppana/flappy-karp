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
            src/systems/infinite_scroller.hpp
            src/systems/player_controller.cpp

        INCLUDE_FILES
            src/components/pipe.hpp
            src/components/scrollable.hpp
            src/scenes/game.hpp
            src/scenes/load.hpp
            src/systems/infinite_scroller.cpp
            src/systems/player_controller.cpp
            src/tags.hpp
        )

engine_create_launcher(
        SOURCE_DIR "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include/engine/launcher"
        PROJECT_FILE "${CMAKE_SOURCE_DIR}/flappykarp.project"
)

target_link_libraries(launcher PUBLIC SDL2::SDL2main)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/engine.hxx)

# install
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(CODE "set(PLUGIN_FILE \"$<TARGET_FILE:${PROJECT_NAME}>\")")
install(CODE "set(VCPKG_BIN_DIR \"${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin\")")
install(CODE [[
        # The regexes are a workaround for https://gitlab.kitware.com/cmake/cmake/-/issues/22431
        file(GET_RUNTIME_DEPENDENCIES
            RESOLVED_DEPENDENCIES_VAR RESOLVED_DLLS
            UNRESOLVED_DEPENDENCIES_VAR UNREAOLVED_DLLS
            PRE_EXCLUDE_REGEXES "api-ms-.*" "ext-ms-.*"
            POST_EXCLUDE_REGEXES ".*[Ss][Yy][Ss][Tt][Ee][Mm]32.*"
            LIBRARIES "${PLUGIN_FILE}"
            DIRECTORIES "${VCPKG_BIN_DIR}"
)
        message("Packaging .DLL's:")
        foreach(DLL ${RESOLVED_DLLS})
            file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" FILES "${DLL}")
        endforeach()
    ]])
install(CODE [[
    file(GLOB DATA_FILES "${CMAKE_SOURCE_DIR}/dist/Release/*.data")
    file(INSTALL ${DATA_FILES} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
]])
