#ifndef _RENDERINGPROCESSOR_H_
#define _RENDERINGPROCESSOR_H_
#include <memory>
#include "RenderingCommand.h"

class RenderingProcessor {
public:
    virtual ~RenderingProcessor() = default;
    virtual void process_command(std::shared_ptr<RenderingCommand> rendering_command) = 0;
};

#endif //_RENDERINGPROCESSOR_H_