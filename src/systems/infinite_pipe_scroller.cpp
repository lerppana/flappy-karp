#include "systems/infinite_pipe_scroller.hpp"

#include "components/pipe.hpp"

namespace lerppana::flappykarp::systems
{
    void infinite_pipe_scroller::started(core::scene& scene)
    {
        resource_loader->request_load<resource::mesh_resource>("fs1://models/pipe.model.mesh");
        resource_loader->request_load<resource::texture_resource>("fs1://textures/pipe.png");

        // this is ugly hack
        while (!resource_loader->idle()) {};

        for (auto i = 0u; i < pipe_column_count; i++)
        {
            m_generate_pipe(scene, i, pipe_direction::bottom);
            m_generate_pipe(scene, i, pipe_direction::top);
        }
    }

    void infinite_pipe_scroller::fixed_update(core::scene& scene, core::dt_t dt)
    {
        core::view<component::physics_3d, components::pipe>(scene.objects).for_each(
                [&](auto entity, auto& physics, auto& _)
                {
                    auto* obj = (btRigidBody*)physics.get();
                    if (obj == nullptr)
                    {
                        return;
                    }

                    // btTransform tr{};
                    auto& tr = obj->getWorldTransform();
                    auto& origin = tr.getOrigin();
                    origin.setX(origin.getX() + dt.count() * pipe_speed);
                    obj->setWorldTransform(tr);

                    obj->setLinearVelocity(btVector3{-1.f, 0.f, 0.f});
                });
    }

    void infinite_pipe_scroller::m_generate_pipe(core::scene& scene, uint32_t i, pipe_direction direction)
    {
        auto entity = scene.objects->add_gameobject();
        auto& transform = scene.objects->add_component<component::transform>(entity);
        auto euler = glm::vec3(0.f, 0.f, glm::radians(180.f));
        transform.set_position(i * -pipe_column_offset, direction == pipe_direction::top ? pipe_distance : 0.f, 0.f);
        if (direction == pipe_direction::top)
        {
            transform.set_rotation(glm::quat(euler));
        }

        auto& basic_material = scene.objects->add_component<component::basic_material>(
                entity,
                component::basic_material { .texture_ref = "fs1://textures/pipe.png" });

        auto& mesh_filter = scene.objects->add_component<component::mesh_filter>(
                entity,
                component::mesh_filter { .mesh = "fs1://models/pipe.model.mesh" });

        scene.objects->add_component<component::physics_3d>(
                entity,
                component::physics_3d{
                    .physics_body_type = engine::component::physics_body_type::rigid_body,
                    .collision_object_type = physics::collision_object_type::static_triangle_shape,
                    .mesh_key = "fs1://models/pipe.model.mesh"
                });

        scene.objects->add_component<components::pipe>(entity);
    }
}