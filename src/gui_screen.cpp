#include <slug_3d/gui_screen.h>







#include <allegro_flare/text.h>
#include <allegro_flare/button.h>
#include <allegro_flare/framework.h>
#include <AllegroFlare/Color.hpp>




	GUIScreen::GUIScreen(allegro_flare::Display *display)
		: allegro_flare::UIScreen(display)
		, showing_dialogue(false)
		, dialogue_motion_timer(0.0)
		, dialogue_box(NULL)
	{
		set("id", "GUIScreen");


		float button_distance = 50;
		float button_width = 170;

		UIWidget *widget = new allegro_flare::UIText(this, 20, display->height()-20, "press ESC to toggle cursor");
		widget->place.align = AllegroFlare::vec2d(0, 1);
		((allegro_flare::UIText *)widget)->set_font(allegro_flare::Framework::font("DroidSans.ttf 20"));//->place.align = AllegroFlare::vec2d(0, 1);
		((allegro_flare::UIText *)widget)->set_font_color(AllegroFlare::color::black);//->place.align = AllegroFlare::vec2d(0, 1);

		widget = new allegro_flare::UIButton(this, 20, display->height()-50-button_distance*2, button_width, 40, "Respawn");
		widget->place.align = AllegroFlare::vec2d(0, 1);
		//((FGUIButton *)widget)->set_font(af::fonts["DroidSans.ttf 18"]);//->place.align = AllegroFlare::vec2d(0, 1);
		((allegro_flare::UIButton *)widget)->set("on_click_send_message", "respawn()");

		widget = new allegro_flare::UIButton(this, 20, display->height()-50-button_distance*1, button_width, 40, "dialogue up");
		widget->place.align = AllegroFlare::vec2d(0, 1);
		((allegro_flare::UIButton *)widget)->set("on_click_send_message", "show_dialogue");

		widget = new allegro_flare::UIButton(this, 20, display->height()-50-button_distance*0, button_width, 40, "dialogue down");
		widget->place.align = AllegroFlare::vec2d(0, 1);
		((allegro_flare::UIButton *)widget)->set("on_click_send_message", "hide_dialogue");


		// text box
		dialogue_box = new allegro_flare::UITextBox(this, display->width()/2, display->height()/3, display->width()/4*2, display->height()/4, "");
		dialogue_box->set("id", "dialogue_box");
	}
	void GUIScreen::receive_signal(int message_type, void *data)
	{
		//if (message_type == 0)
		{
			//show_dialogue((*(std::string *)(data)));
//		if (message == "hide_dialogue") hide_dialogue();
//		if (message == "show_dialogue") show_dialogue(message);
		}
	}
	void GUIScreen::on_draw()
	{
		if (!showing_dialogue) return;

		// black bars
		float bar_height = 80 * allegro_flare::interpolator::fast_in(dialogue_motion_timer);
		al_draw_filled_rectangle(0, 0, display->width(), bar_height, AllegroFlare::color::black);
		al_draw_filled_rectangle(0, display->height()-bar_height, display->width(), display->height(), AllegroFlare::color::black);

		// draw a dialogue box behind the script
		dialogue_box->set_text_color(AllegroFlare::color::black);
		dialogue_box->place.position.y += 3;
      AllegroFlare::vec2d padding = AllegroFlare::vec2d(40, 30);
		dialogue_box->place.start_transform();
		al_draw_filled_rectangle(0 - padding.x, 0 - padding.y,
			dialogue_box->place.size.x + padding.x,
			dialogue_box->place.size.y + padding.y,
			AllegroFlare::color::color(AllegroFlare::color::mix(AllegroFlare::color::black, AllegroFlare::color::dodgerblue, 0.2), 0.4));
		al_draw_rectangle(0 - padding.x, 0 - padding.y,
			dialogue_box->place.size.x + padding.x,
			dialogue_box->place.size.y + padding.y,
			AllegroFlare::color::color(AllegroFlare::color::mix(AllegroFlare::color::white, AllegroFlare::color::dodgerblue, 0.2), 0.4), 2.0);
		padding += AllegroFlare::vec2d(6, 6);
		al_draw_rectangle(0 - padding.x, 0 - padding.y,
			dialogue_box->place.size.x + padding.x,
			dialogue_box->place.size.y + padding.y,
			AllegroFlare::color::color(AllegroFlare::color::mix(AllegroFlare::color::white, AllegroFlare::color::dodgerblue, 0.2), 0.4), 4.0);

		// hmm.. drawing the black shadow text too
		dialogue_box->on_draw();

		dialogue_box->place.position.y -= 3;
		dialogue_box->set_text_color(AllegroFlare::color::white);

		dialogue_box->place.restore_transform();
	}
	void GUIScreen::show_dialogue(std::string script)
	{
		showing_dialogue = true;

		dialogue_box->set_text(script);
      allegro_flare::Framework::motion().cmove_to(&dialogue_motion_timer, 1.0, 0.6, allegro_flare::interpolator::linear);
	}
	void GUIScreen::hide_dialogue()
	{
		if (!showing_dialogue) return;

		showing_dialogue = false;
      allegro_flare::Framework::motion().cmove_to(&dialogue_motion_timer, 0.0, 0.6, allegro_flare::interpolator::linear);
		dialogue_box->set_text_color(AllegroFlare::color::transparent);
	}
