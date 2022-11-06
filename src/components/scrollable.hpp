#pragma once

namespace lerppana::flappykarp::components
{
    struct [[le::component]] scrollable
    {
        [[le::property]] float speed = 2.f;
        [[le::property]] float create_offset = 8.0f;
        [[le::property]] float reset_x_offset = 15.0f;
    };
}