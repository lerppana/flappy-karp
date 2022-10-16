vcpkg_check_linkage(ONLY_DYNAMIC_LIBRARY)

if (NOT DEFINED ENV{GITHUB_AUTHORIZATION_TOKEN})
    message(FATAL_ERROR "environment variable GITHUB_AUTHORIZATION_TOKEN must be defined")
endif()

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO lerppana/reload-engine
    REF c3c4e742cb2a787f54277872b0b1b6deb2b7179d
    SHA512 cff781c981265f87e1170edcd258441709a9a6de9bf315cc29679c361fd582c75588519c415d0958c7d5b974639917693560bdb833c49170215f4863339bef35
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
        launcher reflection resource_compiler resource_compressor
        DESTINATION ${CURRENT_PACKAGES_DIR}/tools/engine
        AUTO_CLEAN)

file(RENAME "${CURRENT_PACKAGES_DIR}/bin/asset0.data" "${CURRENT_PACKAGES_DIR}/tools/engine/asset0.data")
file(RENAME "${CURRENT_PACKAGES_DIR}/bin/gltf2_export.py" "${CURRENT_PACKAGES_DIR}/tools/engine/gltf2_export.py")

vcpkg_add_to_path("${CURRENT_PACKAGES_DIR}/share/engine")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
