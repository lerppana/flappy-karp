#pragma once

#include "systems/infinite_scroller.hpp"
#include "systems/player_controller.hpp"

#include <engine.hxx>

namespace lerppana::flappykarp::scenes
{
    enum game_state : uint8_t
    {
        stopped,
        running
    };

    struct FLAPPYKARP_EXPORT game : core::scene
    {
        explicit game(
            std::shared_ptr<vk::font_manager> font_manager,
            std::shared_ptr<core::scene_orchestrator_state> scene_orchestrator_state,
            std::shared_ptr<framework::audio_manager> audio_manager,
            std::shared_ptr<systems::infinite_scroller> pipe_scroller,
            std::shared_ptr<systems::player_controller> player_controller,
            std::shared_ptr<system::sdl_input_manager> input_manager,
            std::shared_ptr<core::time> time) :
            engine::core::scene("fs1://scenes/game.scene"),
            font_manager(std::move(font_manager)),
            scene_orchestrator_state(std::move(scene_orchestrator_state)),
            audio_manager(std::move(audio_manager)),
            pipe_scroller(std::move(pipe_scroller)),
            player_controller(std::move(player_controller)),
            input_manager(std::move(input_manager)),
            time(std::move(time))
        {
        }

        void draw_exit_button();

        void draw_fps_counter();

        void draw_hint_text();

        void draw_start_button();

        void fixed_update(core::dt_t dt) final;

        void reset();

        void start() final;

        void update(core::dt_t dt) final;

        void on_gui() final;

      private:
        std::shared_ptr<vk::font_manager> font_manager;
        std::shared_ptr<core::scene_orchestrator_state> scene_orchestrator_state;
        std::shared_ptr<framework::audio_manager> audio_manager;
        std::shared_ptr<systems::infinite_scroller> pipe_scroller;
        std::shared_ptr<systems::player_controller> player_controller;
        std::shared_ptr<system::sdl_input_manager> input_manager;
        std::shared_ptr<core::time> time;

        float score{};

        void m_detect_player_hits();

        bool m_draw_button(std::string_view button_text, float padding, bool is_active);

        void m_gui_draw_score();

        enum game_state game_state = game_state::stopped;
        bool show_fps_counter = false;
    };
}