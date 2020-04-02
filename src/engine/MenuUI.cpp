#include "MenuUI.h"

Button::Button(float x, float y, float width, float height,
	//SDL_Surface *TTF_RenderText_Solid (TTF_Font *fontChosen, const char *text, SDL_Color tColor),
	//TTF_Font* font, std::string text,
	SDL_Color idleColor, SDL_Color hoverColor, SDL_Color activeColor
)
{
	shape.x = x;
	shape.y = y;
	shape.w = width;
	shape.h = height;
	/*fontChosen = TTF_OpenFont("arial.ttf", 28);
	font = TTF_OpenFont("arial.ttf", 28);
	textChosen = text;
	text = "Button";*/
	idleColorChosen = idleColor;
	idleColor.r = 255, idleColor.g = 255, idleColor.b = 255, idleColor.a = 0;
	hoverColorChosen = hoverColor;
	hoverColor.r = 232, hoverColor.g = 110, hoverColor.b = 36, hoverColor.a = 45;
	activeColorChosen = activeColor;
	activeColor.r = 185, activeColor.g = 0, activeColor.b = 0, activeColor.a = 63;
};

Button::~Button() {

}

Point2 Button::getMousePos() {
	Point2 pos;
	SDL_GetMouseState(&pos.x, &pos.y);
	return pos;
}

void Button::handleEventUpdates(std::shared_ptr<EventEngine> eventSystem) { //Check to see if mouse is hovering or clicked.
	if ((getMousePos().x > shape.x) && (getMousePos().x < shape.x + shape.w) && (getMousePos().y > shape.y) && (getMousePos().y < shape.y + shape.h)) {
		isHovering = true;
	}
	else {
		isHovering = false;
	}
	if (isHovering && eventSystem->isPressed(BTN_LEFT)) {
		isClicked = true;
	}
	else {
		isClicked = false;
	}
}

void Button::render(std::shared_ptr<GraphicsEngine> gfx) { //Render the right colour based on mouse condition.
	std::shared_ptr<EventEngine> eventSystem;
	gfx->setDrawColor(idleColorChosen);
	if (isClicked) {
		gfx->setDrawColor(activeColorChosen);
		//std::cout << "Click Working\n";
	} else if (isHovering) {
		gfx->setDrawColor(hoverColorChosen);
		//std::cout << "Hover Working\n";
	}
	else {
		gfx->setDrawColor(idleColorChosen);
	}

	gfx->fillRect(shape.x, shape.y, shape.w, shape.h);
	gfx->drawRect(shape.x, shape.y, shape.w, shape.h); //Render and fill button.
}