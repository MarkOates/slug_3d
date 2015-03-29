


#include <allegro_flare/objects/text_object.h>
#include <allegro_flare/color.h>
#include <allegro_flare/allegro_flare.h>

#include <slug_3d/global_defs.h>




#include <slug_3d/hud.h>
//#include "text_object.h"
//#include "color.h"


//#include "allegro_flare.h"


HUD::HUD(Display *display, ProgramMaster *of)
	: Screen(display)
	, of(of)
	//, display_debug_data(false)
	, room_name()
	, paragraph_title("")
	, line()
	, notification_text("")
	, notfication_text_timer(0.0)
{
	state.set(SHOWING_BARS);

	paragraph_title.align(0.5, 0);
	paragraph_title.font(fonts["bankgthd.ttf 50"]);
	paragraph_title.color(color::orange);
	paragraph_title.opacity(0);
	paragraph_title.position(display->width()/2, display->height()/2 - 100);


	for (int i=0; i<NUM_LINES; i++)
	{
		line[i].align(0.5, 0);
		line[i].font(fonts["bankgthd.ttf 30"]);
		line[i].color(color::white);
		line[i].position(display->width()/2, paragraph_title.get_attr("y") + ((i+3)*line[i].h()));
	}

	notification_text.text("notification");
	notification_text.align(1, 1);
	notification_text.font(fonts["bankgthd.ttf 50"]);
	notification_text.color(color::white);
	notification_text.position(display->width()-40, display->height()-60);
	//notification_text.appearance_on();

//*
//
}


/*
void HUD::set_message_text(std::string title, std::string line1, std::string line2, std::string line3, std::string line4, std::string line5)
{
	paragraph_title.text(title);

	line[0].text(line1);
	line[1].text(line2);
	line[2].text(line3);
	line[3].text(line4);
	line[4].text(line5);
}
*/


void HUD::set_message_text(std::string message)
{
	//this->message = message;
	std::vector<std::string> lines = php::explode("/", message);
	paragraph_title.text("");
	if (!lines.empty()) paragraph_title.text(lines[0]);
	for (unsigned i=1; i<6; i++)
	{
		if (i >= lines.size()) line[i-1].text("");
		else line[i-1].text(lines[i]);
	}
}






void HUD::draw_debug_data()
{
	Entity *primary_camera__entity_attached_to = this->of->player_controlled_entity;


	TextObject text("Hello");

	text.position(10, 10).font(fonts["consola.ttf 21"]).color("white");

	if (!primary_camera__entity_attached_to)
	{
		text.position(10, 10).color(color::red).text("The camera is not attached to an Entity*").draw();
		text.position(10, 30).color(color::red).text("Press the spacebar to create/toggle the camera's Entity").draw();
	}
	else
	{
		al_draw_filled_rectangle(0, 0, 600, 120, color::color(color::black, 0.3));
		text.position(10, 10).text("pos" + primary_camera__entity_attached_to->position.GetString()).draw();
		text.position(10, 30).text("view" + primary_camera__entity_attached_to->view_vector.GetString()).draw();
		text.position(10, 50).text("vel" + primary_camera__entity_attached_to->velocity.GetString()).draw();
		//text.position(10, 70).text("pitch: " + tostring(of->primary_camera.pitch)).draw();
		//text.position(10, 90).text("vel_mag: " + tostring(primary_camera__entity_attached_to->velocity.GetMagnitude())).draw();
		//text.position(10, 120).text("num enemies: " + tostring(of->current_map->get_num_enemies())).draw();

		text.position(display->width()-10, 10).align(1.0, 0.0).text("num collision_steps: " + tostring(of->num_collision_steps)).draw();

	}

	//if (of->player_controlled_entity)
	//	text.color(color::yellow).position(10, 120).text("player_pos" + of->player_controlled_entity->position.GetString()).draw();
}


void HUD::show_room_name(std::string name)
{
	//php::strtoupper()
	room_name.text("- " + php::strtoupper(name) + " -");
	room_name.position(display->width()/2, display->height()/5*4).align(0.5, 0.5).font(fonts["Building_Typeface.ttf 50"]).color(color::lightcyan);

	float start_time = af::time_now + 5.0;
	float end_time = start_time + 1.4;

	room_name.get_attr("opacity") = 1.0;

	// coming in
	motion.canimate(&room_name.get_attr("scale_x"), 1.1, 1, af::time_now, start_time, interpolator::quadrupleFastIn, NULL, NULL);
	motion.canimate(&room_name.get_attr("scale_y"), 1.1, 1, af::time_now, start_time, interpolator::quadrupleFastIn, NULL, NULL);


	// fade out
	motion.canimate(&room_name.get_attr("opacity"), 1, 0.0, af::time_now + 5.0, end_time, interpolator::fastIn, NULL, NULL);
}







void HUD::primary_timer_func()
{
	motion.update(af::time_now);




	notfication_text_timer -= 1.0/60.0;
	if (notfication_text_timer < 0)
	{
		notfication_text_timer = 0;
		notification_text.opacity(0);
	}





	// the dialogue text from an info-pod
	float hw = display->width()/5*3 / 2;
	float hh = display->height()/2 / 2;
	al_draw_filled_rounded_rectangle(display->width()/2-hw, display->height()/2-hh,
		display->width()/2+hw, display->height()/2+hh, 8, 8,
		color::color(color::midnightblue, 0.5 * paragraph_title.get_attr("opacity")));
	al_draw_rounded_rectangle(display->width()/2-hw, display->height()/2-hh,
		display->width()/2+hw, display->height()/2+hh, 8, 8,
		color::color(color::white, 0.5 * paragraph_title.get_attr("opacity")), 3.0);

	paragraph_title.draw();
	for (int i=0; i<NUM_LINES; i++)
	{
		line[i].draw();
	}






	notification_text.draw();





	if (state.has(SHOWING_BARS) && !state.has(DEBUG_MODE))
	{
		// draw the bars

		float bar_y_spacing = 40;
		vec2d roundness = vec2d(5, 5);

		al_draw_filled_circle(60, 40, 90, color::color(color::black, 0.1));

		float player_hydration_max = of->player_character.max_hydration;
		float player_hydration = of->player_character.hydration;
		vec2d hyd_bar = vec2d(60, 50);
		vec2d hyd_bar_size = vec2d(player_hydration_max*30, 20);
		float hyd_bar_now = player_hydration*30;
		float hydration_unit = player_hydration / player_hydration_max;
		float inset = 4;
		al_draw_filled_rounded_rectangle(hyd_bar.x, hyd_bar.y, hyd_bar.x+hyd_bar_size.x, hyd_bar.y+hyd_bar_size.y, roundness.x, roundness.y, color::color(color::black, 0.5));
		al_draw_rounded_rectangle(hyd_bar.x, hyd_bar.y, hyd_bar.x+hyd_bar_size.x, hyd_bar.y+hyd_bar_size.y, roundness.x, roundness.y, (::basically_equal(hydration_unit, 1.0)) ? color::white : color::aqua, 2);
		al_draw_filled_rounded_rectangle(hyd_bar.x+inset, hyd_bar.y+inset, hyd_bar.x+hyd_bar_now-inset, hyd_bar.y+hyd_bar_size.y-inset, roundness.x, roundness.y, color::color(color::aqua, 0.8));


		player_hydration_max = of->player_character.max_health;
		player_hydration = of->player_character.health;
		hyd_bar = hyd_bar + vec2d(0, bar_y_spacing);
		hyd_bar_size = vec2d(player_hydration_max*30, 20);
		hyd_bar_now = player_hydration*30;
		al_draw_filled_rounded_rectangle(hyd_bar.x, hyd_bar.y, hyd_bar.x+hyd_bar_size.x, hyd_bar.y+hyd_bar_size.y, roundness.x, roundness.y, color::color(color::black, 0.5));
		al_draw_rounded_rectangle(hyd_bar.x, hyd_bar.y, hyd_bar.x+hyd_bar_size.x, hyd_bar.y+hyd_bar_size.y, roundness.x, roundness.y, (::basically_equal(hydration_unit, 1.0)) ? color::white : color::hex("ff798f"), 2);
		al_draw_filled_rounded_rectangle(hyd_bar.x+inset, hyd_bar.y+inset, hyd_bar.x+hyd_bar_now-inset, hyd_bar.y+hyd_bar_size.y-inset, roundness.x, roundness.y, color::color(color::hex("ff798f"), 0.8));


		// draw the text

		TextObject text("hydration");
		text.font(fonts["bankgthd.ttf 30"]);

		text.text("hydration");
		text.position(22, 27+bar_y_spacing*0).color(color::black).draw();
		text.position(20, 24+bar_y_spacing*0).color(color::white).draw();

		text.text("health");
		text.position(22, 27+bar_y_spacing*1).color(color::black).draw();
		text.position(20, 24+bar_y_spacing*1).color(color::white).draw();


		//TextObject text2("Health");
		//text2.position(20, 26+bar_y_spacing).font(fonts[MASTER_FONT_NAME + " 40"]).color(color::white);
		//text2.draw();

		//TextObject text3("Lvl: " + tostring(of->player_character.num_level_ups) + " / Till: " + tostring(of->player_character.experience_left_to_strengh_up));
		//text3.position(20, 26+bar_y_spacing*2+10).font(fonts[MASTER_FONT_NAME + " 30"]).color(color::color(color::white, 0.5));
		//text3.draw();
	}



	room_name.draw();



	al_draw_textf(fonts["bankgthd.ttf 26"], color::black, display->width()-30, display->height()-80, ALLEGRO_ALIGN_RIGHT,
		"x: %f", of->player_controlled_entity->position.x);
	al_draw_textf(fonts["bankgthd.ttf 26"], color::black, display->width()-30, display->height()-60, ALLEGRO_ALIGN_RIGHT,
		"y: %f", of->player_controlled_entity->position.y);
	al_draw_textf(fonts["bankgthd.ttf 26"], color::black, display->width()-30, display->height()-40, ALLEGRO_ALIGN_RIGHT,
		"z: %f", of->player_controlled_entity->position.z);



	if (state.has(DEBUG_MODE)) draw_debug_data();
}





#include "dirty_signal_send.h"


void HUD::receive_signal(int signal, void *data)
{
	float *opacity_attr = NULL;

	switch(signal)
	{
	case SIGNAL_SET_DIALOGUE_TEXT:
		{
			// set the message string
			std::cout << "[[setting message]]";
			set_message_text(*static_cast<std::string *>(data));

			// put the text elements that we want to animate into a container
			std::vector<float *> opacity_attrs;
			opacity_attrs.push_back(&paragraph_title.get_attr("opacity"));
			for (unsigned l=0; l<NUM_LINES; l++)
				opacity_attrs.push_back(&line[l].get_attr("opacity"));

			// apply animations to each of the text elements
			for (unsigned i=0; i<opacity_attrs.size(); i++)
				motion.canimate(opacity_attrs[i], 0, 1, af::time_now, af::time_now+0.4, interpolator::slowIn, NULL, NULL);

			break;
		}
	case SIGNAL_SET_NOTIFICATION_TEXT:
		{
			std::cout << "notification text \"" << *static_cast<std::string *>(data) << "\"";
			notfication_text_timer = 4;
			notification_text.text(*static_cast<std::string *>(data));
			//notification_text.opacity(1);
			break;
		}
	case SIGNAL_HIDE_DIALOGUE_TEXT:
		{
			// put the text elements that we want to animate into a container
			std::vector<float *> opacity_attrs;
			opacity_attrs.push_back(&paragraph_title.get_attr("opacity"));
			for (unsigned l=0; l<NUM_LINES; l++)
				opacity_attrs.push_back(&line[l].get_attr("opacity"));

			// apply animations to each of the text elements
			for (unsigned i=0; i<opacity_attrs.size(); i++)
				motion.canimate(opacity_attrs[i], 1, 0, af::time_now, af::time_now+0.4, interpolator::slowIn, NULL, NULL);
		}
		break;
	}
}



void HUD::joy_down_func()
{
	//set_message_text(""); // dirty

}


void HUD::key_down_func()
{
	//set_message_text(""); // dirty
	if (af::current_event->keyboard.keycode == ALLEGRO_KEY_F1)
	{
		state.toggle(DEBUG_MODE);
	}
}