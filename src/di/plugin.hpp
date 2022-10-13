#pragma once

#include <engine.hxx>

struct FLAPPYKARP_EXPORT flappykarp_plugin : engine::plugin
{
    void addRegistrations(std::shared_ptr<Hypodermic::ContainerBuilder> builder) final;

    void setupContainer(std::shared_ptr<Hypodermic::Container> container) final;
};

extern "C" FLAPPYKARP_EXPORT flappykarp_plugin plugin;
flappykarp_plugin plugin;
