#include "render_system.h"

using namespace strife::main;
using namespace strife::common;
using namespace strife::core;
using namespace strife::math;
     
RenderSystem::RenderSystem(const Vector2& windowDimensions) {
    SDL_CreateWindowAndRenderer(windowDimensions.x, windowDimensions.y, 0, &window_, &renderer_);
}

RenderSystem::~RenderSystem() {

}

void RenderSystem::onUpdate(const UpdateEvent& updateEvent) {
    
}