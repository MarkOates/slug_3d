


#include <allegro_flare/allegro_flare.h>


#include "program_master.h"
//#include "allegro_flare.h"

#include "hud.h"



//////// INPUT /////////
//////// INPUT /////////
//////// INPUT /////////
//////// INPUT /////////





void ProgramMaster::mouse_down_func()
{
	if (use_show_mouse_as_cursor) return;


	if (af::current_event->mouse.button == 1)
	{
		player_character.try_frontal_attack();
	}
	if (af::current_event->mouse.button == 2)
	{
		player_character.try_spinning_attack();
	}
}




void ProgramMaster::mouse_axes_func() //override
{
	Entity *primary_camera__entity_is_attached_to_it = player_controlled_entity;

	//if (player_controlled_entity)

	if (!use_show_mouse_as_cursor && primary_camera__entity_is_attached_to_it)
	{
		vec2d point(primary_camera__entity_is_attached_to_it->view_vector.x, primary_camera__entity_is_attached_to_it->view_vector.z);
		point = rotate_point(point, -af::current_event->mouse.dx * 0.008);

		primary_camera__entity_is_attached_to_it->view_vector.x = point.x;
		primary_camera__entity_is_attached_to_it->view_vector.z = point.y;
		//primary_camera.pitch -= af::current_event->mouse.dy * 0.004;
		//primary_camera.pitch = limit<float>(-TAU/4, TAU/4, primary_camera.pitch);

		al_hide_mouse_cursor(al_get_current_display());
		al_set_mouse_xy(al_get_current_display(), al_get_display_width(al_get_current_display())/2, al_get_display_height(al_get_current_display())/2);
	}
}




void ProgramMaster::receive_signal(const std::string &signal, void *data)
{
	if (signal == "respawn()") respawn();
}



void ProgramMaster::key_up_func()
{
	if (player_controlled_entity)
	{
		switch(af::current_event->keyboard.keycode)
		{
		case ALLEGRO_KEY_W:
			player_controlled_entity->move_forward(false);
			break;
		case ALLEGRO_KEY_A:
			player_controlled_entity->strafe_left(false);
			break;
		case ALLEGRO_KEY_S:
			player_controlled_entity->move_backward(false);
			break;
		case ALLEGRO_KEY_D:
			player_controlled_entity->strafe_right(false);
			break;
		case ALLEGRO_KEY_ESCAPE:
			toggle_mouse_as_cursor();
			break;
		}
	}
}



void ProgramMaster::key_down_func()
{
	if (player_controlled_entity)
	{
		// do the player_controlled_entity controls
		switch(af::current_event->keyboard.keycode)
		{
		case ALLEGRO_KEY_W:
			player_controlled_entity->move_forward();
			break;
		case ALLEGRO_KEY_A:
			player_controlled_entity->strafe_left();
			break;
		case ALLEGRO_KEY_S:
			player_controlled_entity->move_backward();
			break;
		case ALLEGRO_KEY_D:
			player_controlled_entity->strafe_right();
			break;
			/*
		case ALLEGRO_KEY_UP:
			if (primary_camera.entity_attached_to)
				primary_camera.entity_attached_to->position.y += 1;
			break;
		case ALLEGRO_KEY_DOWN:
			if (primary_camera.entity_attached_to)
				primary_camera.entity_attached_to->position.y -= 1;
			break;
		case ALLEGRO_KEY_LEFT:
			if (primary_camera.entity_attached_to)
				primary_camera.entity_attached_to->position += primary_camera.entity_attached_to->get_strafe_vector() * 1;
			break;
		case ALLEGRO_KEY_RIGHT:
			if (primary_camera.entity_attached_to)
				primary_camera.entity_attached_to->position -= primary_camera.entity_attached_to->get_strafe_vector() * 1;
			break;
			*/
		case ALLEGRO_KEY_1:
			//player_character.add_to_inventory(Item::ITEM_TYPE_BOTTLE_CAP);//"doll_head32.png");
			//enter_into_door(level.find_door("door1"));
			break;
		case ALLEGRO_KEY_2:
			//player_character.add_to_inventory(Item::ITEM_TYPE_DOLL_HEAD);
			//enter_into_door(level.find_door("door2"));
			break;
		case ALLEGRO_KEY_3:
			//player_character.add_to_inventory(Item::ITEM_TYPE_PAPER_CLIP);
			//enter_into_door(level.find_door("door3"));
			break;
		case ALLEGRO_KEY_0:
			level.list_all_entity2s();
		default:
			break;
		}
	}

	// do the standard keyboard controls
	switch(af::current_event->keyboard.keycode)
	{
	case ALLEGRO_KEY_SPACE:
		if (!player_controlled_entity) return;
		{
			player_controlled_entity->activate_skill("jump");
		}
		// this is just for now, and just for testing
		//{
		//std::cout << "1";
		if (!current_map) break;

			

		//for (unsigned i=0; i<current_map->entities.size(); i++)
		//{
		//	if (primary_camera.entity_attached_to 
		//}
		//std::cout << "2";
		// toggle between a camera-owned entity, to the camera attached to an entity
		/*
		if (primary_camera.entity_attached_to == NULL
			|| primary_camera.entity_attached_to == current_map->entities[0])
		{
			primary_camera.entity_attached_to = new Entity();
			std::cout << "3";
		}
		else if (primary_camera.entity_attached_to && !current_map->entities.empty())
		{
			delete primary_camera.entity_attached_to;
			primary_camera.entity_attached_to = current_map->entities[0];
			std::cout << "4";
		}
		*/
		//std::cout << "5";
		break;
	default:
		break;
	}
}



void ProgramMaster::joy_axis_func()
{
	if (!player_controlled_entity) return;

	if (af::current_event->joystick.stick == 0)
	{
		if (af::current_event->joystick.axis == 0)
		{
			//player_controlled_entity->_dirty_velocity_normal.x = af::current_event->joystick.pos * 0.05;
			//player_controlled_entity->add_force(vec3d(af::current_event->joystick.pos * 0.05, 0, 0));
			//player_controlled_entity->strafe_right(false);
			//player_controlled_entity->strafe_left(false);

			//if (af::current_event->joystick.pos)
			player_controlled_entity->turning(-af::current_event->joystick.pos * 0.05);

			//epos.x = af::current_event->joystick.pos * 3;
		}
		if (af::current_event->joystick.axis == 1)
		{
			//player_controlled_entity->_dirty_velocity_normal.z = -af::current_event->joystick.pos * 0.05;
			//player_controlled_entity->add_force(vec3d(0, 0, af::current_event->joystick.pos * 0.05));
			player_controlled_entity->move_forward(false);
			player_controlled_entity->move_backward(false);

			if (af::current_event->joystick.pos > 0) player_controlled_entity->move_backward();
			if (af::current_event->joystick.pos < 0) player_controlled_entity->move_forward();

			//epos.y = -af::current_event->joystick.pos * 3;

		}
	}
	else if (af::current_event->joystick.stick == 1)
	{
		if (af::current_event->joystick.axis == 0)
		{
			// strafeing goes here, too
		}
		if (af::current_event->joystick.axis == 1)
		{
			Entity *primary_camera__entity_is_attached_to_it = this->player_controlled_entity;;

			if (primary_camera__entity_is_attached_to_it)
			{
				primary_camera.pitch = default_camera_pitch + af::current_event->joystick.pos * 1.0;
				primary_camera.pitch = limit<float>(-TAU/4, TAU/4, primary_camera.pitch);

				//epos.z = -af::current_event->joystick.pos * 3;
			}
		}
	}
}



void ProgramMaster::joy_down_func()
{
	if (!player_controlled_entity) return;

	std::cout << "BUTTON" << af::current_event->joystick.button << std::endl;

	switch(af::current_event->joystick.button)
	{
	case 0:
		player_controlled_entity->activate_skill("jump");
		break;
	case 1:
		player_character.try_spinning_attack();
		break;
	case 2:
		player_character.try_frontal_attack();
		break;
	case 3:
		this->toggle_mouse_as_cursor();
		//respawn();
		break;
	case 4:
		player_controlled_entity->strafe_left();
		break;
	case 5:
		player_controlled_entity->strafe_right();
		break;
	default:
		break;
	}
}




void ProgramMaster::joy_up_func()
{
	if (!player_controlled_entity) return;


	switch(af::current_event->joystick.button)
	{
	case 4:
		player_controlled_entity->strafe_left(false);
		break;
	case 5:
		player_controlled_entity->strafe_right(false);
		break;
	default:
		break;
	}
}
