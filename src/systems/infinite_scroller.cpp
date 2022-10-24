#include "systems/infinite_scroller.hpp"

#include "components/pipe.hpp"
#include "components/scrollable.hpp"

namespace lerppana::flappykarp::systems
{
    void infinite_scroller::started(core::scene& scene)
    {
        resource_loader->get<resource::vk_mesh_resource>("fs1://models/pipe.model.mesh");
        resource_loader->get<resource::texture_resource>("fs1://textures/pipe.png");

        m_generate_pipes(scene);
    }

    void infinite_scroller::fixed_update(core::scene& scene, core::dt_t dt)
    {
        if (!enabled) return;

        auto random_y_offset = util::random_value(-2.0f, 6.0f);
        core::view<component::physics_3d, components::scrollable, component::transform>(scene.objects).for_each(
                [&](auto entity, auto& physics, auto& scrollable, auto& transform)
                {
                    auto* obj = (btRigidBody*)physics.get();
                    if (obj != nullptr)
                    {
                        btTransform tr(obj->getWorldTransform());
                        auto& origin = tr.getOrigin();
                        auto rot = tr.getRotation();

                        if (tr.getOrigin().getX() >= scrollable.reset_x_offset)
                        {
                            auto count = 1u;
                            if (scene.objects->has_component<components::pipe>(entity))
                            {
                                auto dir = rot.getIdentity() == rot ? -1.f : 1.f;
                                origin.setY(random_y_offset + pipe_distance * dir);
                                count = pipe_column_count;
                            }

                            origin.setX(origin.getX() - scrollable.create_offset * count);
                        }
                        else
                        {
                            origin.setX(origin.getX() + dt.count() * scrollable.speed);
                        }


                        obj->setWorldTransform(tr);
                        obj->getMotionState()->setWorldTransform(tr);
                    }
                    else
                    {
                        auto pos = transform.get_position();
                        if (pos.x >= scrollable.reset_x_offset)
                        {
                            pos.x = pos.x - scrollable.create_offset;
                        }
                        else
                        {
                            pos.x = pos.x + dt.count() * scrollable.speed;
                        }
                        transform.set_position(pos);
                    }
                });
    }

    void infinite_scroller::reset_system(core::scene& scene)
    {
        auto i = 0u;
        core::view<components::pipe, component::physics_3d, component::transform>(scene.objects)
                .for_each([&](auto entity, auto& _, auto& physics, auto& transform)
                {
                    static auto random_y_offset = 0.f;
                    if (i % 2 == 0)
                    {
                        random_y_offset = util::random_value(-2.f, 6.f);
                    }
                    physics.require_sync = true;
                    m_set_pipe_position(
                            transform,
                            i / 2,
                            i % 2 == 0 ? pipe_direction::bottom : pipe_direction::top,
                            random_y_offset,
                            physics.bt_rigid_body);
                    i++;
                });
    }

    void infinite_scroller::m_generate_pipes(core::scene& scene)
    {
        for (auto i = 0u; i < pipe_column_count; i++)
        {
            auto random_y_offset = util::random_value(-2.0f, 6.0f);
            common::console::log(random_y_offset);
            m_generate_pipe(scene, i, pipe_direction::bottom, random_y_offset);
            m_generate_pipe(scene, i, pipe_direction::top, random_y_offset);
        }
    }

    void infinite_scroller::m_generate_pipe(core::scene& scene, uint32_t i, pipe_direction direction, float y_offset)
    {
        auto entity = scene.objects->add_gameobject();
        auto& transform = scene.objects->add_component<component::transform>(entity);

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
                    .activation_state = engine::physics::activation_state::disable_deactivation
                });

        scene.objects->add_component<components::pipe>(entity);
        scene.objects->add_component<components::scrollable>(entity);
        m_set_pipe_position(
                transform,
                i,
                direction,
                y_offset,
                physics_component.bt_rigid_body);
    }

    void infinite_scroller::m_set_pipe_position(
            component::transform& transform,
            uint32_t i,
            pipe_direction direction,
            float y_offset,
            btRigidBody* rigid_body)
    {
        auto euler = glm::vec3(0.f, 0.f, glm::radians(180.f));
        auto pipe_y = direction == pipe_direction::top ? pipe_distance + y_offset : -pipe_distance + y_offset;
        transform.set_position(-pipe_start_offset + i * -pipe_column_offset, pipe_y, 0.f);
        if (direction == pipe_direction::top)
        {
            transform.set_rotation(glm::quat(euler));
        }

        auto& tr = rigid_body->getWorldTransform();
        tr.setOrigin(engine::util::glm_to_bt_vector3(transform.get_position()));
        tr.setRotation(engine::util::glm_to_bt_quaternion(transform.get_rotation()));
        rigid_body->setWorldTransform(tr);
    }
}