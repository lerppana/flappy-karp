#pragma once

namespace lerppana::flappykarp
{
    enum class game_state : int
    {
        stopped,
        running
    };

    struct global_game_state
    {
        game_state state = game_state::stopped;
    };
}
