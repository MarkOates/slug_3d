#ifndef __SH_HUD_HEADER
#define __SH_HUD_HEADER


#include <allegro_flare/bins/font_bin.h>
#include <allegro_flare/objects/text_object.h>
#include <allegro_flare/motion.h>

//#include "font_bin.h"
#include "program_master.h"
//#include "text_object.h"
//#include "motion_control.h"


class ProgramMaster;

#define NUM_LINES 5

class HUD : public Screen
{
public:
	enum HUD_state_flags_t
	{
		DEBUG_MODE = 0x01,
		SHOWING_BARS = 0x02
	};

	FontBin fonts;
	Motion motion;
	ProgramMaster *of;
	//bool display_debug_data;
	TextObject room_name;
	BitFlags<int> state;

	TextObject paragraph_title;
	TextObject line[NUM_LINES];

	TextObject notification_text;
	float notfication_text_timer;

	HUD(Display *display, ProgramMaster *of);

	void draw_debug_data();
	void show_room_name(std::string name);


	//void set_message_text(std::string title, std::string line1="", std::string line2="", std::string line3="", std::string line4="", std::string line5="");
	void set_message_text(std::string full_message);

	//void 
	
	void receive_signal(int signal, void *data) override;


	void primary_timer_func() override;
	void key_down_func() override;
	void joy_down_func() override;
};







#endif