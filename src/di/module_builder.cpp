#include "di/module_builder.hpp"

#include "scenes/load.hpp"
#include "generated/reflection.generated.hxx"

using namespace engine;

namespace lerppana::flappykarp
{
    module_builder::module_builder()
    {
        registerType<scenes::load>().as<engine::core::scene>().asSelf().singleInstance();

        this->addRegistrations(lerppana::generated::generated_builder{});
    }
}
