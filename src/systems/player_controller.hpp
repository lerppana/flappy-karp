#pragma once

#include <engine.hxx>

namespace lerppana::flappykarp::systems
{
    struct player_controller : core::system
    {
        // todo replace this with enabled state in system
        bool enabled = false;

        explicit player_controller(
                std::shared_ptr<engine::system::sdl_input_manager> input_manager) :
                input_manager(std::move(input_manager))
        {
        }

        bool can_splash();

        void fixed_update(core::scene& scene, core::dt_t dt) final;

        void started(core::scene& scene) final;

        void splash(core::scene& scene, float jump_force);

    private:
        std::shared_ptr<engine::system::sdl_input_manager> input_manager;
        std::chrono::system_clock::time_point last_splash = std::chrono::system_clock::time_point::min();
    };
}