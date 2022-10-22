#pragma once

#include <engine.hxx>

namespace lerppana::flappykarp::systems
{
    struct player_controller : core::system
    {
        explicit player_controller(
                std::shared_ptr<engine::system::sdl_input_manager> input_manager) :
                input_manager(std::move(input_manager))
        {
        }

        void fixed_update(core::scene& scene, core::dt_t dt) final;

        void started(core::scene& scene) final;

    private:
        std::shared_ptr<engine::system::sdl_input_manager> input_manager;

        float jump_force = 6.0f;
        std::chrono::system_clock::time_point last_splash = std::chrono::system_clock::time_point::min();
    };
}