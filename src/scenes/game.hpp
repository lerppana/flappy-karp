#pragma once

#include <engine.hxx>

#include "systems/infinite_pipe_scroller.hpp"
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
                std::shared_ptr<systems::infinite_pipe_scroller> pipe_scroller,
                std::shared_ptr<systems::player_controller> player_controller) :
                engine::core::scene("fs1://scenes/game.scene"),
                font_manager(std::move(font_manager)),
                pipe_scroller(std::move(pipe_scroller)),
                player_controller(std::move(player_controller))
        {}

        void fixed_update(core::dt_t dt) final;

        void reset();

        void start() final;

        void update(core::dt_t dt) final;

        void on_gui() final;
    private:
        std::shared_ptr<vk::font_manager> font_manager;
        std::shared_ptr<systems::infinite_pipe_scroller> pipe_scroller;
        std::shared_ptr<systems::player_controller> player_controller;

        float score{};

        void m_detect_player_hits();

        void m_gui_draw_score();

        void m_gui_draw_reset_button();

        enum game_state game_state = game_state::stopped;
    };
}