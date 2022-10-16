vcpkg_check_linkage(ONLY_DYNAMIC_LIBRARY)

if (NOT DEFINED ENV{GITHUB_AUTHORIZATION_TOKEN})
    message(FATAL_ERROR "environment variable GITHUB_AUTHORIZATION_TOKEN must be defined")
endif()

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO lerppana/reload-engine
    REF e074e673ebdf7114044962ab68dc6141980a3e17
    SHA512 0e70e32faf69e89c6a8d84f31f3a4d8e8b4ae6dd670c28636981a63f5a328221b434c765f36ce2eae851c24b5d900a20c53ef45dc83d3f5b424ce06935b97e68
    HEAD_REF bugfixing
    AUTHORIZATION_TOKEN $ENV{GITHUB_AUTHORIZATION_TOKEN}
)

vcpkg_check_features(
    OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES "editor"    ENGINE_ENABLE_EDITOR)

vcpkg_cmake_configure(
    SOURCE_PATH ${SOURCE_PATH}
    OPTIONS
        ${FEATURE_OPTIONS}
        -DENGINE_ENABLE_SAMPLES=OFF
        -DENGINE_ENABLE_TESTS=OFF
        -DENGINE_ENABLE_TOOLS=ON
)

file(INSTALL
        "${SOURCE_PATH}/.cmake/date_to_version.cmake"
        "${SOURCE_PATH}/.cmake/engine_create.cmake"
        "${SOURCE_PATH}/.cmake/engine_create_launcher.cmake"
        "${SOURCE_PATH}/.cmake/engine_create_plugin.cmake"
        "${SOURCE_PATH}/.cmake/FindVulkan.cmake"
        DESTINATION "${CURRENT_PACKAGES_DIR}/share/engine")

vcpkg_cmake_install(ADD_BIN_TO_PATH)

vcpkg_cmake_config_fixup(
        PACKAGE_NAME engine
        CONFIG_PATH "share/cmake/engine"
        TOOLS_PATH ${CURRENT_PACKAGES_DIR}/tools/engine)

vcpkg_copy_tools(TOOL_NAMES
        launcher reflection resource_compiler resource_compressor asset0.data gltf2_export.py
        DESTINATION ${CURRENT_PACKAGES_DIR}/tools/engine
        AUTO_CLEAN)

vcpkg_add_to_path("${CURRENT_PACKAGES_DIR}/share/engine")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")