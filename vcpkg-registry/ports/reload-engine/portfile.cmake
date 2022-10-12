vcpkg_check_linkage(ONLY_DYNAMIC_LIBRARY)

if (NOT DEFINED ENV{GITHUB_AUTHORIZATION_TOKEN})
    message(FATAL_ERROR "environment variable GITHUB_AUTHORIZATION_TOKEN must be defined")
endif()

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO lerppana/reload-engine
    REF v0.0.144
    SHA512 38db04c35668708c8760ca031f2c36fef4572543ed40c7e980f5ad523fb37134af2dafb28e162ef1a44f2cb6ae1d605d1978201f1cf0a33e40f70a1e096b2e95
    HEAD_REF master
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
        DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")

vcpkg_cmake_install(ADD_BIN_TO_PATH)
vcpkg_cmake_config_fixup(CONFIG_PATH "share/cmake/engine")
vcpkg_copy_tools(TOOL_NAMES launcher reflection resource_compiler resource_compressor asset0.data gltf2_export.py AUTO_CLEAN)
vcpkg_add_to_path("${CURRENT_PACKAGES_DIR}/share/${PORT}")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")