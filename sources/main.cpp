/*******************************************************************************
 * This file is part of the "Enduro2D"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2018 Matvey Cherevko
 ******************************************************************************/

#include <enduro2d/enduro2d.hpp>
using namespace e2d;

namespace
{
    class game final : public application {
    public:
        bool frame_tick() final {
            const keyboard& k = the<input>().keyboard();
            while ( the<window>().should_close() || k.is_key_just_released(keyboard_key::escape) ) {
                return false;
            }
            the<render>().execute(render::command_block<64>()
                .add_command(render::clear_command()
                    .color_value({1.f, 0.4f, 0.f, 1.f}))
                .add_command(render::swap_command(true)));
            return true;
        }
    };
}

int e2d_main(int argc, char *argv[]) {
    auto params = engine::parameters("bootstrap", "enduro2d")
        .timer_params(engine::timer_parameters()
            .maximal_framerate(100));
    modules::initialize<engine>(argc, argv, params).start<game>();
    return 0;
}
