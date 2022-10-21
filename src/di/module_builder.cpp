#include "di/module_builder.hpp"

#include "game_state.hpp"
#include "scenes/game.hpp"
#include "scenes/load.hpp"
#include "systems/infinite_pipe_scroller.hpp"
#include "systems/player_controller.hpp"
#include "generated/reflection.generated.hxx"

using namespace engine;

namespace lerppana::flappykarp
{
    module_builder::module_builder()
    {
        registerType<global_game_state>().singleInstance();

        registerType<scenes::game>().as<core::scene>().asSelf().singleInstance();

        registerType<scenes::load>().as<core::scene>().asSelf().singleInstance();

        registerType<systems::infinite_pipe_scroller>().as<core::system>().asSelf().singleInstance();

        registerType<systems::player_controller>().as<core::system>().asSelf().singleInstance();

        this->addRegistrations(lerppana::generated::generated_builder{});
    }
}
