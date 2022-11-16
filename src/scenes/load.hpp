#pragma once

#include <engine.hxx>

namespace lerppana::flappykarp::scenes
{
    struct [[le::scene]] FLAPPYKARP_EXPORT load : engine::core::scene
    {
        explicit load(
                std::shared_ptr<resource::resource_loader> resource_loader,
                std::shared_ptr<vk::font_manager> font_manager,
                std::shared_ptr<core::scene_orchestrator_state> scene_orchestrator_state,
                std::shared_ptr<framework::audio_manager> audio_manager) :
                engine::core::scene("fs1://scenes/load.scene"),
                resource_loader(std::move(resource_loader)),
                font_manager(std::move(font_manager)),
                scene_orchestrator_state(std::move(scene_orchestrator_state)),
                audio_manager(std::move(audio_manager))
        {}

        void draw_exit_button();

        void draw_start_button();

        void on_gui() final;

        void start() final;

    private:
        std::shared_ptr<resource::resource_loader> resource_loader;
        std::shared_ptr<vk::font_manager> font_manager;
        std::shared_ptr<core::scene_orchestrator_state> scene_orchestrator_state;
        std::shared_ptr<framework::audio_manager> audio_manager;
    };
}