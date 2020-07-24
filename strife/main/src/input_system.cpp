#include "input_system.h"

using namespace strife::main;
using namespace strife::common;
using namespace strife::core;
     
void InputSystem::onUpdate(const UpdateEvent& updateEvent) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        process(event);
    }
}

void InputSystem::process(const SDL_Event& event)
{
    
}