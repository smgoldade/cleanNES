#ifndef _RENDERINGCOMMAND_H_
#define _RENDERINGCOMMAND_H_

#include "Texture.h"

enum class RenderingCommandType {
    CLEAR_COLOR,
    CLEAR,
    CREATE,
    DESTROY,
    DRAW_FRAME,
    UPDATE_VIEWPORT,
    CREATE_TEXTURE,
    DELETE_TEXTURE,
    APPLY_TEXTURE,
    UPDATE_TEXTURE
};

struct RenderingCommand {
    RenderingCommandType type;
    bool executed { false };
    bool error { false };
    bool color_clear { false };
    bool depth_clear { false };
    texture_id texture_id { -1 };
    const Color* color = nullptr;
    const Texture* texture = nullptr;
    const vec2i* position = nullptr;
    const vec2i* size = nullptr;
};

#endif //_RENDERINGCOMMAND_H_