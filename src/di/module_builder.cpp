#include "di/module_builder.hpp"

#include "scenes/game.hpp"
#include "scenes/load.hpp"
#include "systems/infinite_scroller.hpp"
#include "systems/player_controller.hpp"
#include "generated/reflection.generated.hxx"

using namespace engine;

namespace lerppana::flappykarp
{
    module_builder::module_builder()
    {
        registerType<scenes::game>().as<core::scene>().asSelf().singleInstance();

        registerType<scenes::load>().as<core::scene>().asSelf().singleInstance();

        registerType<systems::infinite_scroller>().as<core::system>().asSelf().singleInstance();

        registerType<systems::player_controller>().as<core::system>().asSelf().singleInstance();

        this->addRegistrations(lerppana::generated::generated_builder{});
    }
}
