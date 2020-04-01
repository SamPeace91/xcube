#include "XCube2d.h"

std::shared_ptr<XCube2Engine> XCube2Engine::instance = nullptr;

XCube2Engine::XCube2Engine() {
	std::cout << "Initializing X-CUBE 2D v" << _ENGINE_VERSION_MAJOR << "." << _ENGINE_VERSION_MINOR << std::endl;

#ifdef __DEBUG
	#if defined(_WIN32)
		debug("WIN32");
	#elif defined(__linux__)
		debug("LINUX");
	#elif defined(__APPLE__)
		debug("MACOSX");
	#endif
#endif

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		throw EngineException("SDL_Init()", SDL_GetError());

#ifdef __DEBUG
	debug("SDL_Init() successful");
#endif

	std::cout << "Logical CPU cores: " << SDL_GetCPUCount() << std::endl;
	std::cout << "System RAM: " << SDL_GetSystemRAM() << " MB" << std::endl;
	std::cout << "Running on: " << SDL_GetPlatform() << std::endl;

	SDL_version compiled, linked;
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);

	printf("Compiled against SDL %d.%d.%d\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("Linked against SDL %d.%d.%d\n",
		linked.major, linked.minor, linked.patch);

	Uint32 ticks = SDL_GetTicks();
	srand(ticks);	// init random seed

#ifdef __DEBUG
	debug("Inited srand() with", ticks);
#endif

	// init subsystems

	gfxInstance = std::shared_ptr<GraphicsEngine>(new GraphicsEngine());

#ifdef __DEBUG
	debug("GraphicsEngine() successful");
#endif

	audioInstance = std::shared_ptr<AudioEngine>(new AudioEngine());

#ifdef __DEBUG
	debug("AudioEngine() successful");
#endif

	eventInstance = std::shared_ptr<EventEngine>(new EventEngine());

#ifdef __DEBUG
	debug("EventEngine() successful");
#endif

	physicsInstance = std::shared_ptr<PhysicsEngine>(new PhysicsEngine());
}

XCube2Engine::~XCube2Engine() {
#ifdef __DEBUG
	debug("XCube2Engine::~XCube2Engine() started");
#endif

	ResourceManager::freeResources();

	eventInstance.reset();
	gfxInstance.reset();

#ifdef __DEBUG
	debug("XCube2Engine::~XCube2Engine() finished");
#endif
}

void XCube2Engine::quit() {
	if (instance)
		instance.reset();
}

std::shared_ptr<XCube2Engine> XCube2Engine::getInstance() {
	if (!instance)
		instance = std::shared_ptr<XCube2Engine>(new XCube2Engine());
	return instance;
}

/*Button::Button(float x, float y, float width, float height,
	TTF_Font* font, std::string text,
	SDL_Color idleColor, SDL_Color hoverColor, SDL_Color activeColor) {

	this->shape.setPosition(SDL_Point(x, y));
	this->shape.setSize(SDL::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(SDL_COLOR_WHITE);
	this->text.setCharacterSize(12);
	this->text.setPosition(
		this->shape.getPosition().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y / 2.f - this->text.getGlobalBounds().height / 2.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button() {

}

void Button::update(const SDL::Vector2f mousePos) {
	//Update the booleans for hover and pressed.

	if (this->shape.getGlobalBounds().contains(mousePos)) {

	}
}

void Button::render(SDL::RenderTarget * target) {
	target->draw(this->shape);
}*/