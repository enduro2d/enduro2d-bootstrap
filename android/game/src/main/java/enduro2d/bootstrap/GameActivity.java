/*******************************************************************************
 * This file is part of the "Enduro2D"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2018-2019, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

package enduro2d.bootstrap;

import android.os.Bundle;

public class GameActivity
        extends enduro2d.engine.E2DActivity
{
    static {
        System.loadLibrary("enduro2d-bootstrap");
    }

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        create();
    }
}
