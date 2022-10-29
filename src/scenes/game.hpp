#pragma once

#include <engine.hxx>

#include "systems/infinite_scroller.hpp"
#include "systems/player_controller.hpp"

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
                std::shared_ptr<systems::player_controller> player_controller) :
                engine::core::scene("fs1://scenes/game.scene"),
                font_manager(std::move(font_manager)),
                scene_orchestrator_state(std::move(scene_orchestrator_state)),
                audio_manager(std::move(audio_manager)),
                pipe_scroller(std::move(pipe_scroller)),
                player_controller(std::move(player_controller))
        {
        }

        void draw_exit_button();

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

        float score{};

        void m_detect_player_hits();

        void m_gui_draw_score();

        void m_gui_draw_reset_button();

        enum game_state game_state = game_state::stopped;
    };
}