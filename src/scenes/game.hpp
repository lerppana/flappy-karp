#pragma once

#include <engine.hxx>

namespace lerppana::flappykarp::scenes
{
    struct game : core::scene
    {
        explicit game() :
            core::scene("fs1://scenes/game.scene")
        {}
    };
}