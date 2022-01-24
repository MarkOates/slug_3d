#ifndef __SH_HUD_HEADER
#define __SH_HUD_HEADER


#include <AllegroFlare/FontBin.hpp>
#include <allegro_flare/text_object.h>
#include <AllegroFlare/Motion.hpp>

//#include "font_bin.h"
#include <slug_3d/program_master.h>
//#include "text_object.h"
//#include "motion_control.h"


class ProgramMaster;

#define NUM_LINES 5

class HUD : public allegro_flare::Screen
{
public:
	enum HUD_state_flags_t
	{
		DEBUG_MODE = 0x01,
		SHOWING_BARS = 0x02
	};

   AllegroFlare::FontBin fonts;
   AllegroFlare::Motion motion;
	ProgramMaster *of;
	//bool display_debug_data;
   allegro_flare::TextObject room_name;
   allegro_flare::BitFlags<int> state;

   allegro_flare::TextObject paragraph_title;
   allegro_flare::TextObject line[NUM_LINES];

   allegro_flare::TextObject notification_text;
	float notfication_text_timer;

	HUD(allegro_flare::Display *display, ProgramMaster *of);

	void draw_debug_data();
	void show_room_name(std::string name);


	//void set_message_text(std::string title, std::string line1="", std::string line2="", std::string line3="", std::string line4="", std::string line5="");
	void set_message_text(std::string full_message);

	//void 
	
	void receive_signal(int signal, void *data) override;


	void primary_timer_func() override;
	void key_down_func() override;
	void joy_button_down_func() override;
};







#endif
