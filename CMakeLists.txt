cmake_minimum_required(VERSION 3.21.2)

project(flappykarp CXX)

find_package(engine CONFIG REQUIRED)

include(engine_create)

engine_create_plugin(flappykarp
        PROJECT_FILE
        "${CMAKE_CURRENT_LIST_DIR}/flappykarp.project"

        SOURCE_FILES
            src/di/module_builder.cpp
            src/di/plugin.cpp
            src/scenes/game.cpp
            src/scenes/load.cpp
            src/systems/infinite_pipe_scroller.hpp
            src/systems/player_controller.cpp

        INCLUDE_FILES
            src/components/pipe.hpp
            src/di/module_builder.hpp
            src/di/plugin.hpp
            src/scenes/game.hpp
            src/scenes/load.hpp
            src/systems/infinite_pipe_scroller.cpp
            src/systems/player_controller.cpp
            src/tags.hpp
        )

engine_create_launcher(SOURCE_DIR ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include/engine/launcher)

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
            file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}" FILES "${DLL}")
        endforeach()
    ]])

FILE(GLOB DATA_FILES "$<TARGET_FILE_DIR:${PROJECT_NAME}>/*.data")
install(FILES ${DATA_FILES} DESTINATION bin)
install(FILES "${CMAKE_CURRENT_LIST_DIR}/flappykarp.project" DESTINATION bin)
