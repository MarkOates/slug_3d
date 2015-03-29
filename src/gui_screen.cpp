#include <slug_3d/gui_screen.h>











	GUIScreen::GUIScreen(Display *display)
		: FGUIScreen(display)
		, showing_dialogue(false)
		, dialogue_motion_timer(0.0)
		, dialogue_box(NULL)
	{
		attr.set("id", "GUIScreen");


		float button_distance = 50;
		float button_width = 170;

		FGUIWidget *widget = new FGUIText(this, 20, display->height()-20, fonts["DroidSans.ttf 20"], "press ESC to toggle cursor");
		widget->place.align = vec2d(0, 1);
		((FGUIText *)widget)->set_font_color(color::black);//->place.align = vec2d(0, 1);

		widget = new FGUIButton(this, "Respawn", fonts["DroidSans.ttf 18"], 20, display->height()-50-button_distance*2, button_width, 40);
		widget->place.align = vec2d(0, 1);
		((FGUIButton *)widget)->attr.set("on_click_send_message", "respawn()");

		widget = new FGUIButton(this, "dialogue up", fonts["DroidSans.ttf 18"], 20, display->height()-50-button_distance*1, button_width, 40);
		widget->place.align = vec2d(0, 1);
		((FGUIButton *)widget)->attr.set("on_click_send_message", "show_dialogue");

		widget = new FGUIButton(this, "dialogue down", fonts["DroidSans.ttf 18"], 20, display->height()-50-button_distance*0, button_width, 40);
		widget->place.align = vec2d(0, 1);
		((FGUIButton *)widget)->attr.set("on_click_send_message", "hide_dialogue");


		// text box
		dialogue_box = new FGUITextBox(this, fonts["DroidSerif.ttf 34"], "", display->width()/2, display->height()/3, display->width()/4*2, display->height()/4);
		dialogue_box->attr.set("id", "dialogue_box");
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
		float bar_height = 80 * interpolator::fastIn(dialogue_motion_timer);
		al_draw_filled_rectangle(0, 0, display->width(), bar_height, color::black);
		al_draw_filled_rectangle(0, display->height()-bar_height, display->width(), display->height(), color::black);

		// draw a dialogue box behind the script
		dialogue_box->set_text_color(color::black);
		dialogue_box->place.position.y += 3;
		vec2d padding = vec2d(40, 30);
		dialogue_box->place.start_transform();
		al_draw_filled_rectangle(0 - padding.x, 0 - padding.y,
			dialogue_box->place.size.x + padding.x,
			dialogue_box->place.size.y + padding.y,
			color::color(color::mix(color::black, color::dodgerblue, 0.2), 0.4));
		al_draw_rectangle(0 - padding.x, 0 - padding.y,
			dialogue_box->place.size.x + padding.x,
			dialogue_box->place.size.y + padding.y,
			color::color(color::mix(color::white, color::dodgerblue, 0.2), 0.4), 2.0);
		padding += vec2d(6, 6);
		al_draw_rectangle(0 - padding.x, 0 - padding.y,
			dialogue_box->place.size.x + padding.x,
			dialogue_box->place.size.y + padding.y,
			color::color(color::mix(color::white, color::dodgerblue, 0.2), 0.4), 4.0);

		// hmm.. drawing the black shadow text too
		dialogue_box->on_draw();

		dialogue_box->place.position.y -= 3;
		dialogue_box->set_text_color(color::white);

		dialogue_box->place.restore_transform();
	}
	void GUIScreen::show_dialogue(std::string script)
	{
		showing_dialogue = true;

		dialogue_box->set_text(script);
		motion.cmove_to(&dialogue_motion_timer, 1.0, 0.6, interpolator::linear);
	}
	void GUIScreen::hide_dialogue()
	{
		if (!showing_dialogue) return;

		showing_dialogue = false;
		motion.cmove_to(&dialogue_motion_timer, 0.0, 0.6, interpolator::linear);
		dialogue_box->set_text_color(color::transparent);
	}
