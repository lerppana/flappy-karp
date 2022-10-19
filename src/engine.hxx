#pragma once

#include "flappykarp_export.h"

// engine
#include <core/scene.hpp>
#include <engine/plugin.hpp>
#include <plugin.hpp>
#include <system/sdl_input_manager.hpp>
#include <vk/imgui_context.hpp>

// editor
#if ENGINE_ENABLE_EDITOR
#include <editor/tag_editor.hpp>
#endif

// 3rd party
#include <Hypodermic/Container.h>
#include <SDL2/SDL_keycode.h>

// STL
#include <chrono>
#include <memory>

using namespace engine;