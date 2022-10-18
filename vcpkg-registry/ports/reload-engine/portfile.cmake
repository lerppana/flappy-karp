vcpkg_check_linkage(ONLY_DYNAMIC_LIBRARY)

if (NOT DEFINED ENV{GITHUB_AUTHORIZATION_TOKEN})
    message(STATUS "Environment variable GITHUB_AUTHORIZATION_TOKEN is not defined, make sure you have environment that is capable to logging in by itself")
endif()

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO lerppana/reload-engine
    REF 0c0d304694ececeddb87f2158870b8949da6adb8 # v0.0.148
    SHA512 4638a3a74559fa5d2ac04db28f61fd002d19513bef0f85bfa9a5cb11a63622baa14b53ab7db955b9683162fb4b880697336205d53a2a97fded855568a68d7970
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
        "${SOURCE_PATH}/.cmake/copy_dll_to.cmake"
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
        launcher reflection resource_compiler resource_compressor
        DESTINATION ${CURRENT_PACKAGES_DIR}/tools/engine
        AUTO_CLEAN)

file(RENAME "${CURRENT_PACKAGES_DIR}/bin/asset0.data" "${CURRENT_PACKAGES_DIR}/tools/engine/asset0.data")
file(RENAME "${CURRENT_PACKAGES_DIR}/bin/gltf2_export.py" "${CURRENT_PACKAGES_DIR}/tools/engine/gltf2_export.py")

vcpkg_add_to_path("${CURRENT_PACKAGES_DIR}/share/engine")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
