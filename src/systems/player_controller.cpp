#include "systems/player_controller.hpp"

namespace lerppana::flappykarp::systems
{
    void player_controller::fixed_update(core::scene& scene, core::dt_t dt)
    {
        if (!scene.objects->tagged_has_component<component::physics_3d>(core::tag::player_1))
        {
            return;
        }

        auto& physics_component = scene.objects->get_tagged_component<component::physics_3d>(core::tag::player_1);

        auto splash_reload_delay = std::chrono::milliseconds (400);
        auto splash_reloaded = last_splash + splash_reload_delay < std::chrono::system_clock::now();
        if (input_manager->is_key_pressed(SDL_SCANCODE_SPACE) && splash_reloaded)
        {
            last_splash = std::chrono::system_clock::now();
            auto* rigid_body = (btRigidBody*)physics_component.get();
            rigid_body->setLinearVelocity({0.f, jump_force, 0.f});
            rigid_body->setAngularVelocity(
                    {
                        util::random_value(-1.0f, 1.f),
                        util::random_value(-1.0f, 1.f),
                        util::random_value(-1.0f, 1.f)});
        }
    }

    void player_controller::started(core::scene& scene)
    {
        scene.physics_world->set_gravity(0.0f, -9.8f, 0.f);

        if (!scene.objects->tagged_has_component<component::physics_3d>(core::tag::player_1))
        {
            return;
        }

        auto& physics_component = scene.objects->get_tagged_component<component::physics_3d>(core::tag::player_1);
        auto* rigid_body = (btRigidBody*)physics_component.get();
        rigid_body->setLinearFactor(btVector3{0.f, 1.f, 0.f});
    }
}