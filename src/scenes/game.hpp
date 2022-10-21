#pragma once

#include <engine.hxx>

namespace lerppana::flappykarp::scenes
{
    struct FLAPPYKARP_EXPORT game : core::scene
    {
        explicit game(std::shared_ptr<vk::font_manager> font_manager) :
                engine::core::scene("fs1://scenes/game.scene"),
                font_manager(std::move(font_manager))
        {}

        void start() final;

        void update(core::dt_t dt) final;

        void on_gui() final;
    private:
        std::shared_ptr<vk::font_manager> font_manager;

        float score{};
    };
}