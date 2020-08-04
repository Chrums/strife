#include "engine.h"

#include "events.h"

using namespace strife::core;
using namespace strife::common;
using namespace std;
    
void loop(void* context) {
	Engine* const engine = static_cast<Engine*>(context);
	engine->update();
}

Engine::Scenes::Scenes(Engine& engine)
	: engine_(engine)
	, active_(nullptr) {}

Scene& Engine::Scenes::load(const string path) {
	Scene& scene = scenes_.emplace(path, Scene {}).first->second;
	
	SceneLoadEvent sceneLoadEvent(scene);
	engine_.dispatcher.emit(sceneLoadEvent);
	
	return scene;
}

void Engine::Scenes::unload(const string path) {
	Scene& scene = scenes_.find(path)->second;
	
	SceneUnloadEvent sceneUnloadEvent(scene);
	engine_.dispatcher.emit(sceneUnloadEvent);
	
	scenes_.erase(path);
}

void Engine::Scenes::swap(const string path) {
	Scene* const from = active_;
	Scene* const to = &scenes_.find(path)->second;
	
	SceneSwapEvent sceneSwapEvent(from, to);
	engine_.dispatcher.emit(sceneSwapEvent);
	
	active_ = to;
}

Engine::Systems::Systems(Engine& engine)
	: engine_(engine) {}

Engine::Systems::~Systems() {
	for (auto [type, system] : systems_) {
        delete system;
    }
}

Engine& Engine::Instance() {
	if (Engine::instance_ == nullptr) {
		Engine::instance_ = new Engine();
	}
	
	return *Engine::instance_;
}

void Engine::run() {
    emscripten_set_main_loop_arg(loop, this, -1, 1);
}

void Engine::update() {
	time = timer_.update();

	SDL_Event event;
    while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			// TODO: Implement this...
		}

        inputEvent(event);
    }
	
	UpdateEvent updatEvent;
	dispatcher.emit(updatEvent);
}

Engine* Engine::instance_ = nullptr;

Engine::Engine()
    : scenes(*this)
    , systems(*this) {
	SDL_Init(SDL_INIT_EVERYTHING);
}