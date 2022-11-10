#pragma once

#include <engine.hxx>

namespace lerppana::flappykarp::systems
{
    enum pipe_direction
    {
        top,
        bottom
    };

    struct infinite_scroller : core::system
    {
        // todo replace this with enabled state in system
        bool enabled = true;

        explicit infinite_scroller(
                std::shared_ptr<resource::resource_loader> resource_loader) :
                resource_loader(std::move(resource_loader))
        {}

        void reset_system(core::scene& scene);

        void fixed_update(core::scene& scene, core::dt_t dt) final;

        void started(core::scene& scene) final;

    private:
        std::shared_ptr<resource::resource_loader> resource_loader;

        uint32_t pipe_column_count = 5u;
        float pipe_column_offset = 8.f;
        float pipe_distance = 2.f;
        float pipe_start_offset = 14.f;

        void m_generate_pipes(core::scene& scene);

        void m_set_pipe_position(
                component::transform& transform,
                uint32_t i,
                pipe_direction direction,
                float y_offset,
                component::physics_3d& physics);
    };
}