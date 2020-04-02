#ifndef __MENU_UI_H__
#define __MENU_UI_H__

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_events.h>
#include <memory>
#include "GraphicsEngine.h"
#include "EventEngine.h"

class Button {
private:
	SDL_Rect shape; //Create button shape.

	/*TTF_Font* fontChosen;
	std::string textChosen;
	TTF_Font *fontChosen;
	const char *textChosen;
	SDL_Color textColor;*/

	SDL_Color idleColorChosen;
	SDL_Color hoverColorChosen;
	SDL_Color activeColorChosen;

	bool isHovering = false;
	bool isClicked = false;
public:
	Button(float x, float y, float width, float height,
		//SDL_Surface *TTF_RenderText_Solid (TTF_Font *fontChosen, const char *textChosen, SDL_Color textColor),
		//TTF_Font* font, std::string text,
		SDL_Color idleColor, SDL_Color hoverColor, SDL_Color activeColor
	); //Construct button.
	~Button();

	//Functions
	void handleEventUpdates(std::shared_ptr<EventEngine> eventSystem);
	void render(std::shared_ptr<GraphicsEngine> gfx);
	Point2 getMousePos();
};

#endif
