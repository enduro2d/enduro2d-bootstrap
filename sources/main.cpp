/*******************************************************************************
 * This file is part of the "Enduro2D"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2018-2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <enduro2d/enduro2d.hpp>
using namespace e2d;

namespace
{
    class game_system final : public ecs::system {
    public:
        void process(ecs::registry& owner) override {
            E2D_UNUSED(owner);
            const keyboard& k = the<input>().keyboard();

            if ( k.is_key_just_released(keyboard_key::f12) ) {
                the<dbgui>().toggle_visible(!the<dbgui>().visible());
            }

            if ( k.is_key_just_released(keyboard_key::escape) ) {
                the<window>().set_should_close(true);
            }

            if ( k.is_key_pressed(keyboard_key::lsuper) && k.is_key_just_released(keyboard_key::enter) ) {
                the<window>().toggle_fullscreen(!the<window>().fullscreen());
            }
        }
    };

    class game final : public starter::application {
    public:
        bool initialize() final {
            ecs::registry_filler(the<world>().registry())
                .system<game_system>(world::priority_update);

            const gobject_iptr camera_i = the<world>().instantiate();
            camera_i->entity_filler()
                .component<camera>(camera()
                    .background({1.f, 0.4f, 0.f, 1.f}))
                .component<actor>(node::create(camera_i));
            return true;
        }
    };
}

int e2d_main(int argc, char *argv[]) {
    const auto params = starter::parameters(
        engine::parameters("bootstrap", "enduro2d")
            .timer_params(engine::timer_parameters()
                .maximal_framerate(100)));
    modules::initialize<starter>(argc, argv, params).start<game>();
    modules::shutdown<starter>();
    return 0;
}
