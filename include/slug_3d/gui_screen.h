#ifndef __SLUG3D_HEADER_GUI_SCREEN
#define __SLUG3D_HEADER_GUI_SCREEN





#include <flare_gui/flare_gui.h>
#include <allegro_flare/timeline.h>






class GUIScreen : public FGUIScreen
{
public:
	bool showing_dialogue;
	float dialogue_motion_timer;
	FGUITextBox *dialogue_box;

	GUIScreen(Display *display);
	void receive_signal(int signal_type, void *data) override;
	void on_draw() override;
	void show_dialogue(std::string script);
	void hide_dialogue();
};






#endif
