#include <engine.hxx>

#include "tags.hpp"

#include "scenes/game.hpp"
#include "scenes/load.hpp"
#include "systems/infinite_scroller.hpp"
#include "systems/player_controller.hpp"
#include "generated/reflection.generated.hxx"

using namespace engine;
using namespace lerppana::flappykarp;

struct module_builder : Hypodermic::ContainerBuilder
{
    explicit module_builder()
    {
        registerType<scenes::game>().as<core::scene>().asSelf().singleInstance();

        registerType<scenes::load>().as<core::scene>().asSelf().singleInstance();

        registerType<systems::infinite_scroller>().as<core::system>().asSelf().singleInstance();

        registerType<systems::player_controller>().as<core::system>().asSelf().singleInstance();

        this->addRegistrations(lerppana::generated::generated_builder{});
    }
};

struct FLAPPYKARP_EXPORT flappykarp_plugin : engine::plugin
{
    void addRegistrations(std::shared_ptr<Hypodermic::ContainerBuilder> builder) final
    {
        builder->addRegistrations(module_builder{});
    }

    void setupContainer(std::shared_ptr<Hypodermic::Container> container) final
    {
        engine::vk::imgui_context::set_shared_imgui_context();

#if ENGINE_ENABLE_EDITOR
        container->resolve<engine::editor::tag_editor>()->register_tags<lerppana::flappykarp::tags>();
#endif
    }
};

extern "C" FLAPPYKARP_EXPORT flappykarp_plugin plugin;
flappykarp_plugin plugin;