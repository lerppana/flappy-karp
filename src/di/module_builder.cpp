#include "di/module_builder.hpp"

#include "scenes/load.hpp"
#include "systems/player_controller.hpp"
#include "generated/reflection.generated.hxx"

using namespace engine;

namespace lerppana::flappykarp
{
    module_builder::module_builder()
    {
        registerType<scenes::load>().as<core::scene>().asSelf().singleInstance();

        registerType<systems::player_controller>().as<core::system>().asSelf().singleInstance();

        this->addRegistrations(lerppana::generated::generated_builder{});
    }
}
