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
            src/scenes/load.cpp

        INCLUDE_FILES
        src/di/module_builder.hpp
            src/di/plugin.hpp
            src/scenes/load.hpp
            src/tags.hpp
        )

engine_create_launcher(SOURCE_DIR ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include/engine/launcher)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/engine.hxx)

install(TARGETS ${PROJECT_NAME}
    RUNTIME_DEPENDENCIES
    PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
    POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
    DIRECTORIES "$ENV{VULKAN_SDK}/lib;${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib"
    FRAMEWORK DESTINATION install
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
)
