#pragma once

#include <engine.hxx>

namespace lerppana::flappykarp::scenes
{
    struct FLAPPYKARP_EXPORT load : engine::core::scene
    {
        explicit load();

        void start() final;
    };
}