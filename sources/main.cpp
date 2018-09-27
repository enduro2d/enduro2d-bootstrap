/*******************************************************************************
 * This file is part of the "Enduro2D"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2018 Matvey Cherevko
 ******************************************************************************/

#include <enduro2d/enduro2d.hpp>
using namespace e2d;

int e2d_main() {
    input& i = modules::initialize<input>();
    debug& d = modules::initialize<debug>();
    window& w = modules::initialize<window>(
        v2u{640, 480}, "Enduro2D", true, false);

    d.add_sink<debug_console_sink>();
    w.register_event_listener<window_input_source>(i);

    const keyboard& k = i.keyboard();
    while ( !w.should_close() && !k.is_key_just_released(keyboard_key::escape) ) {
        i.frame_tick();
        w.swap_buffers();
        window::frame_tick();
    }
    return 0;
}
