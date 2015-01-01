#ifndef __SLUG3D_HEADER_GUI_SCREEN
#define __SLUG3D_HEADER_GUI_SCREEN





#include <flare_gui/flare_gui.h>


class GUIScreen : public FGUIScreen
{
public:
	GUIScreen(Display *display)
		: FGUIScreen(display)
	{
		float button_distance = 50;

		FGUIWidget *widget = new FGUIText(this, 20, display->height()-20, fonts["DroidSans.ttf 23"], "Hello GUI!");
		widget->place.align = vec2d(0, 1);

		widget = new FGUIButton(this, "Respawn", fonts["DroidSans.ttf 18"], 20, display->height()-50-button_distance*2, 110, 40);
		widget->place.align = vec2d(0, 1);
		((FGUIButton *)widget)->attr.set("on_click_send_message", "respawn()");

		widget = new FGUIButton(this, "Button2", fonts["DroidSans.ttf 18"], 20, display->height()-50-button_distance*1, 110, 40);
		widget->place.align = vec2d(0, 1);

		widget = new FGUIButton(this, "Button3", fonts["DroidSans.ttf 18"], 20, display->height()-50-button_distance*0, 110, 40);
		widget->place.align = vec2d(0, 1);
	}
};






#endif