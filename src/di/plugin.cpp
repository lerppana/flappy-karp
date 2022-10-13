#include "plugin.hpp"

#include "di/module_builder.hpp"

#include "tags.hpp"

void flappykarp_plugin::addRegistrations(std::shared_ptr<Hypodermic::ContainerBuilder> builder)
{
    builder->addRegistrations(lerppana::flappykarp::module_builder{});
}

void flappykarp_plugin::setupContainer(std::shared_ptr<Hypodermic::Container> container)
{
    engine::vk::imgui_context::set_shared_imgui_context();

#if ENGINE_ENABLE_EDITOR
    container->resolve<engine::editor::tag_editor>()->register_tags<lerppana::flappykarp::tags>();
#endif
}