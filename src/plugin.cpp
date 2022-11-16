#include <engine.hxx>

#include "generated/reflection.generated.hxx"

struct FLAPPYKARP_EXPORT flappykarp_plugin : engine::plugin
{
    void addRegistrations(std::shared_ptr<Hypodermic::ContainerBuilder> builder) final
    {
      builder->addRegistrations(lerppana::generated::generated_builder{});
    }

    void setupContainer(std::shared_ptr<Hypodermic::Container> container) final
    {
        lerppana::generated::generated_builder::setup_container(container);
    }
};

extern "C" FLAPPYKARP_EXPORT flappykarp_plugin plugin;
flappykarp_plugin plugin;