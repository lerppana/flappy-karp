#include "systems/infinite_pipe_scroller.hpp"

#include "components/pipe.hpp"

namespace lerppana::flappykarp::systems
{
    void infinite_pipe_scroller::started(core::scene& scene)
    {
        resource_loader->get<resource::vk_mesh_resource>("fs1://models/pipe.model.mesh");
        resource_loader->get<resource::texture_resource>("fs1://textures/pipe.png");

        for (auto i = 0u; i < pipe_column_count; i++)
        {
            auto random_y_offset = util::random_value(-2.0f, 6.0f);
            common::console::log(random_y_offset);
            m_generate_pipe(scene, i, pipe_direction::bottom, random_y_offset);
            m_generate_pipe(scene, i, pipe_direction::top, random_y_offset);
        }
    }

    void infinite_pipe_scroller::fixed_update(core::scene& scene, core::dt_t dt)
    {
        auto random_y_offset = util::random_value(-2.0f, 6.0f);
        core::view<component::physics_3d, components::pipe>(scene.objects).for_each(
                [&](auto entity, auto& physics, auto& _)
                {
                    auto* obj = (btRigidBody*)physics.get();
                    if (obj == nullptr)
                    {
                        return;
                    }

                    btTransform tr(obj->getWorldTransform());
                    auto& origin = tr.getOrigin();
                    auto rot = tr.getRotation();

                    if (tr.getOrigin().getX() >= 15.f)
                    {
                        auto dir = rot.getIdentity() == rot ? -1.f : 1.f;
                        origin.setY(random_y_offset + pipe_distance * dir);
                        origin.setX(origin.getX() - pipe_column_offset * (pipe_column_count));
                    }
                    else
                    {
                        origin.setX(origin.getX() + dt.count() * pipe_speed);
                    }


                    obj->setWorldTransform(tr);
                    obj->getMotionState()->setWorldTransform(tr);
                });
    }

    void infinite_pipe_scroller::m_generate_pipe(core::scene& scene, uint32_t i, pipe_direction direction, float y_offset)
    {
        auto entity = scene.objects->add_gameobject();
        auto& transform = scene.objects->add_component<component::transform>(entity);
        auto euler = glm::vec3(0.f, 0.f, glm::radians(180.f));
        auto pipe_y = direction == pipe_direction::top ? pipe_distance + y_offset : -pipe_distance + y_offset;
        transform.set_position(-pipe_start_offset + i * -pipe_column_offset, pipe_y, 0.f);
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

        auto& physics_component = scene.objects->add_component<component::physics_3d>(
                entity,
                component::physics_3d{
                    .collision_object_type = physics::collision_object_type::static_triangle_shape,
                    .mesh_key = "fs1://models/pipe.model.mesh",
                    .activation_state = engine::physics::activation_state::disable_deactivation,
                });

        scene.objects->add_component<components::pipe>(entity);
    }
}