/*******************************************************************************
 * This file is part of the "Enduro2D"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2018 Matvey Cherevko
 ******************************************************************************/

#include <enduro2d/enduro2d.hpp>
using namespace e2d;

int e2d_main() {
    {
        modules::initialize<vfs>()
            .register_scheme<filesystem_file_source>("file");
        modules::initialize<debug>()
            .register_sink<debug_console_sink>();
        modules::initialize<input>();
        modules::initialize<window>(v2u{640, 480}, "Enduro2D", false)
            .register_event_listener<window_input_source>(the<input>());
        modules::initialize<render>(the<debug>(), the<window>());
    }
    {
        const keyboard& k = the<input>().keyboard();
        while ( !the<window>().should_close() && !k.is_key_just_released(keyboard_key::escape) ) {
            the<render>().execute(render::command_block<64>()
                .add_command(render::clear_command()
                    .color_value({1.f, 0.4f, 0.f, 1.f}))
                .add_command(render::swap_command(true)));
            the<input>().frame_tick();
            window::poll_events();
        }
    }
    return 0;
}
