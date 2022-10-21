#pragma once

#include <engine.hxx>

namespace lerppana::flappykarp::systems
{
    enum pipe_direction
    {
        top,
        bottom
    };

    struct infinite_pipe_scroller : core::system
    {
        explicit infinite_pipe_scroller(std::shared_ptr<resource::resource_loader> resource_loader) :
            resource_loader(std::move(resource_loader))
        {}

        void fixed_update(core::scene& scene, core::dt_t dt) final;

        void started(core::scene& scene) final;

    private:
        std::shared_ptr<resource::resource_loader> resource_loader;

        uint32_t pipe_column_count = 5u;
        float pipe_column_offset = 8.f;
        float pipe_distance = 2.f;
        float pipe_speed = 0.0015f;
        float pipe_start_offset = 14.f;

        void m_generate_pipe(
                core::scene& scene,
                uint32_t i,
                pipe_direction direction,
                float y_offset);
    };
}