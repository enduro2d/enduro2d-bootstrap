/*******************************************************************************
 * This file is part of the "Enduro2D"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2018-2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <enduro2d/enduro2d.hpp>
using namespace e2d;

namespace
{
    class game_system final : public systems::update_system {
    public:
        void process(
            ecs::registry& owner,
            const systems::update_event& event) override
        {
            E2D_UNUSED(owner, event);
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
            {
                ecs::registry_filler(the<world>().registry())
                .feature<struct game_feature>(ecs::feature()
                    .add_system<game_system>());
            }

            {
                prefab scene_prefab;
                scene_prefab.prototype()
                    .component<named>(named()
                        .name("scene"))
                    .component<scene>();

                prefab camera_prefab;
                camera_prefab.prototype()
                    .component<named>(named()
                        .name("camera"))
                    .component<camera>(camera()
                        .background({1.f, 0.4f, 0.f, 1.f}))
                    .component<camera::gizmos>();

                gobject scene_go = the<world>().instantiate(scene_prefab);
                gobject camera_go = the<world>().instantiate(camera_prefab);

                node_iptr scene_node = scene_go.component<actor>()->node();
                node_iptr camera_node = camera_go.component<actor>()->node();

                scene_node->add_child(camera_node);
            }

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
