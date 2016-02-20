#include <allegro_flare/allegro_flare.h>



#include <slug_3d/program_master.h>
//#include "allegro_flare.h"

#include <slug_3d/hud.h>
#include <slug_3d/info_pod.h>

#include <slug_3d/dirty_signal_send.h>



#include <flare_gui/flare_gui.h>





//Door *home_door = NULL;


ProgramMaster::ProgramMaster(Display *display)
	: Screen(display)
	, current_map(NULL)
	//, player_controlled_entity2(new Entity2(NULL, Entity2::PLAYER, models["hero-02.obj"], ""))
	//, primary_camera(display->width(), display->height(), NULL)
	, primary_camera(vec3d(0, 0, 0))
	, num_collision_steps(0)
	, default_camera_pitch(-0.5)
	//, epos(0)
	, level()
	, player_character(level.maps.back()) // yikes
	, player_controlled_entity(player_character.entity)
	, hud(NULL)
	//, gui_screen(NULL)
	, use_show_mouse_as_cursor(false)
{
	std::cout << "In Program Master" << std::endl;

	primary_camera.pitch = default_camera_pitch;



	//gui_screen = new GUIScreen(display);
	//gui_screen->clear_to_background_color = false;








	hud = new HUD(display, this);


	//hud = ;




	//maps.push_back(terrain_map());


	//start_map(small_room_map());
	player_controlled_entity = player_character.entity;





	//Entity *player_entity = new Entity(NULL);

	Entity *primary_camera__entity_attached_to = player_controlled_entity;


	primary_camera__entity_attached_to = player_controlled_entity;
	primary_camera__entity_attached_to->position = vec3d(0, 8, 0);

	//primary_camera.stepback = vec3d(0, 1, 0); // a *decent* first person view, but pitches strangely :/
	primary_camera.stepback = vec3d(0, 2, -5); // a good 3rd person backward view
	primary_camera.stepback_pitch = 0;


	//primary_camera.update_camera_tracking(vec3d(0, 0, 0), primary_camera__entity_attached_to->view_vector, Camera3D::CAMERA_VIEW_TRACK_ALONG_X);


	// 0.4 REVISION:
	/*
	primary_camera.stepback_default = vec3d(0, 2, -5); // a good 3rd person backward view
	primary_camera.stepback_pitch_default = 0;
	*/
	//primary_camera.update_camera_tracking(


	//primary_camera.entity_attached_to = player_controlled_entity;


//	player_stats = new PlayerStats();


	if (!level.maps.empty()) start_map(level.maps.back());
}




void ProgramMaster::toggle_mouse_as_cursor()
{
	this->use_show_mouse_as_cursor = !this->use_show_mouse_as_cursor;
	if (use_show_mouse_as_cursor) al_show_mouse_cursor(display->al_display);
	else al_hide_mouse_cursor(display->al_display);
}




void ProgramMaster::start_map(Map *map)
{
	current_map = map;
	//attach_entity_to_map(map, player_controlled_entity);
	player_character.put_in_map(map, vec3d(0, 22, 0));
//venus4_rgb_cyl_www.jpg
	hud->show_room_name(current_map->name);

	// make sure the player is spawned in the correct location

	std::cout << "num entities: " << current_map->entities.size() << std::endl;
	std::cout << "num entity2s: " << current_map->entity2s.size() << std::endl;
}




#include <allegro_flare/interpolators.h>


//#include "interpolators.h"
#include <slug_3d/pickup_trinket.h>


bool ProgramMaster::enter_into_door(Door *door)
{
	if (!door) return false;
	current_map = door->map;


	//std::cout << "ENTERED ENTERED ENTERED ENTERED ENTERED ENTERED ENTERED ENTERED " << std::endl;


	player_character.put_in_map(current_map, vec3d(door->place.position.x, door->place.position.y, door->place.position.z-2.0));
	hud->show_room_name(current_map->name);

	//player_character.entity->view_vector = -player_character.entity->view_vector;
	player_character.entity->view_vector = vec3d(0, 0, -1);


	float start = af::time_now + 1;
	float end = af::time_now + 2;



	//
	vec3d stepback_default = vec3d(0, 2, -5); // this will be the endpoint, we need to get it from the camera based on its current settings
	//float
	vec3d stepback_rotation_default = vec3d(0, 0, 0);


	//motion.canimate(&primary_camera.stepback.x, primary_camera.stepback_default.x, primary_camera.stepback_default.x, af::time_now, af::time_now + 1.4, interpolator::doubleFastIn, NULL, NULL); 
	primary_camera.stepback.y = stepback_default.y/2;
	primary_camera.stepback.z = stepback_default.z*2;
	motion.canimate(&primary_camera.stepback.y, primary_camera.stepback.y, stepback_default.y, start, end, interpolator::slowInOut, NULL, NULL);
	motion.canimate(&primary_camera.stepback.z, primary_camera.stepback.z, stepback_default.z, af::time_now, end, interpolator::slowInOut, NULL, NULL);
	//motion.canimate(&primary_camera.stepback.z, primary_camera.stepback_default.x, primary_camera.stepback_default.z, af::time_now, af::time_now + 1.4, interpolator::doubleFastIn, NULL, NULL);

	primary_camera.stepback_rotation.y = 2;
	motion.canimate(&primary_camera.stepback_rotation.y, primary_camera.stepback_rotation.y, stepback_rotation_default.y, af::time_now, end+0.3, interpolator::slowInOut, NULL, NULL);





	// reload the trinkets
	if (current_map->name == "Customize Your Character")
	{
		// clear all the trinkets
		for (unsigned i=0; i<current_map->entity2s.size(); i++)
		{
			if (current_map->entity2s[i]->entity2_type == Entity2::PICKUP_TRINKET)
			{
				if (current_map->remove_and_destroy_entity2(current_map->entity2s[i])) // yikes, this /shouldn't/ be a problem, I don't think
					i--;
			}
			
		}

		std::vector<Item::item_t> unique_list_of_items = player_character.get_unique_list_of_items();

		vec3d trinket_line_start = vec3d(12, 1, -17.5);
		vec3d trinket_distance = vec3d(-4, 0, 0);

		for (int i=0; i<(int)unique_list_of_items.size(); i++)
		{
			vec3d point_along = trinket_line_start + trinket_distance * i;
			PickupTrinket *pickup_trinket = new PickupTrinket(current_map, unique_list_of_items[i], point_along);
			current_map->entity2s.push_back(pickup_trinket);
		}
	}




	

	door->player_in_doorway = true;

	return true;
}







//vec3d epos;


#include <slug_3d/enemy.h>
#include <slug_3d/pickup_trinket.h>


void ProgramMaster::primary_timer_func()
{
	// UPDATING THE VELOCITY/POSITION OF OBJECTS
	motion.update(af::time_now);
	//0.4 REVISION // primary_camera.update();



	// update the rotation of the coins
	for (unsigned i=0; i<current_map->entity2s.size(); i++)
	{
		if (current_map->entity2s[i]->entity2_type == Entity2::ITEM)
		{
			if (current_map->entity2s[i]->place.rotation.y < 0) current_map->entity2s[i]->place.rotation.y -= 0.004;
			else current_map->entity2s[i]->place.rotation.y += 0.004;
		}
	}


	Entity *primary_camera__entity_attached_to = this->player_controlled_entity;
	//primary_camera.update_camera_tracking(primary_camera__entity_attached_to->position, primary_camera__entity_attached_to->view_vector, Camera3D::CAMERA_VIEW_TRACK_ALONG_X_BIRD);
	primary_camera.update_camera_tracking(primary_camera__entity_attached_to->position, primary_camera__entity_attached_to->view_vector);

	if (player_controlled_entity)
	{
		player_controlled_entity->update_player_controlls();
	}
		
	for (unsigned i=0; i<current_map->entity2s.size(); i++)
	{
		current_map->entity2s[i]->update();
		/*
		if (current_map->entity2s[i]->entity2_type == Entity2::ENEMY)
		{
			Enemy *enemy = static_cast<Enemy *>(current_map->entity2s[i]);
			//enemy->
		}
		*/
	}



	
	for (unsigned i=0; i<current_map->entity2s.size(); i++)
	{
		// if the player is outside the collision mesh's box... set his OUT_OF_BOUNDS flag
		if (current_map->entity2s[i]->entity2_type == Entity2::PICKUP_TRINKET)
		{
			Entity2 *entity = current_map->entity2s[i];
			if (entity->collides(player_character.entity->position))
			{
				PickupTrinket *pickup_trinket = static_cast<PickupTrinket *>(current_map->entity2s[i]);
				player_character.equip_shell(pickup_trinket->data);
				std::cout << "attempting to equip " << pickup_trinket->data << std::endl;
			}
		}
		if (current_map->entity2s[i]->entity2_type == Entity2::WORLD)
		{
			Entity2 *entity = current_map->entity2s[i];
			if (!entity->collides(player_character.entity->position))
			{
				//OUT_OF_BOUNDS
				if (entity->place.position.y > current_map->entity2s[i]->place.position.y) continue;
				player_controlled_entity->state_flags.set(PlayerCharacter::OUT_OF_BOUNDS);

				std::string *str = new std::string("OUT OF BOUNDS");
				dirty_send_signal(SIGNAL_SET_NOTIFICATION_TEXT, (void *)str);
				delete str;

				player_controlled_entity->position = vec3d(0, 3, 0);
			}
		}
	}

	




	AntEnemy *ant_enemy = NULL;
	if (current_map->name=="Sand Box" && current_map->get_num_enemies() < 30) // 30 enemies in this map
	{
		vec3d random_placement = vec3d(random_float(-40, 50), -1, random_float(-100, 0));


		ant_enemy = new AntEnemy(current_map, random_placement, vec3d(50, -1, 0), vec3d(-40, -1, -100));
		current_map->entity2s.push_back(ant_enemy);
		switch(random_int(0, 2))
		{
			case 0: ant_enemy->make_red(); break;
			case 1: ant_enemy->make_blue(); break;
			case 2: ant_enemy->make_white(); break;
		}
	}






	if (player_character.state.set(PlayerCharacter::DEAD))
	{
		//enter_into_door(home_door);

		//std::string *str = new std::string("YIKES!/You died. Keep trying.");
		//dirty_send_signal(SIGNAL_SET_DIALOGUE_TEXT, (void*)str);
		//delete str;
	}





	// DRAWING THE SCENE



	// clear the depth buffer

	al_clear_depth_buffer(1000);
	al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
	primary_camera.set_frustum_as_camera(display->al_display);







	//if (this->player_controlled_entity) player_controlled_entity->position += player_controlled_entity->_dirty_velocity_normal;



	// draw the map

	//

	// if the player step-collision collides with an entity

	player_character.update();

	if (player_character.state.has(PlayerCharacter::FRONTAL_STRIKE_ATTACK))
	{
		// just doin' this dirty... 3 points in space for testing collision
		// (aka... I didn't haven't learned the ray/box collision yet, so I'm doing this)
		std::vector<vec3d> strike_locations;
		for (int i=0; i<(int)player_character.strike_distance; i++)
		{
			strike_locations.push_back(player_character.entity->position + player_character.entity->view_vector * i * 1);
			strike_locations.push_back(player_character.entity->position + player_character.entity->view_vector * i * 2);
		}
		//strike_locations.push_back(player_character.entity->position + player_character.entity->view_vector * 1);
		//strike_locations.push_back(player_character.entity->position + player_character.entity->view_vector * 1.5);
		//strike_locations.push_back(player_character.entity->position + player_character.entity->view_vector * 2);

		

		//strike_locations.push_back(player_character.entity->position + player_character.entity->view_vector * 0.5);

		for(unsigned i=0; i<current_map->entity2s.size(); i++)
		{
			if (current_map->entity2s[i]->entity2_type != Entity2::ENEMY) continue;

			for (unsigned sl=0; sl<strike_locations.size(); sl++)
			{
				if (current_map->entity2s[i]->collides(strike_locations[sl]))
				{
					Enemy *enemy = static_cast<Enemy *>(current_map->entity2s[i]);
					if (enemy->take_damage(player_character.strength))
					{
						player_character.pickup_experience(enemy->exp_from_kill);
						
						std::string *str = new std::string("+" + tostring(enemy->exp_from_kill) + " exp");
						dirty_send_signal(SIGNAL_SET_NOTIFICATION_TEXT, (void*)str);
						delete str;

						current_map->remove_and_destroy_entity2(enemy);
						std::cout << std::endl << " > DEAD!! < ";
						i--;
					}
					std::cout << "hit!";

					enemy->place.position.x += player_character.entity->view_vector.x * 2;
					enemy->place.position.z += player_character.entity->view_vector.z * 2;

					break;
				}
			}
			
		}

		player_character.state.unset(PlayerCharacter::FRONTAL_STRIKE_ATTACK);
	}


	_update_new_triangle_thing();




	// drawing:



	if (current_map) current_map->draw();
	//if (current_map) current_map->draw_triangles_and_normals();
	if (current_map)
	{
		al_use_shader(NULL);
		current_map->draw_entities();
	}
	if (current_map)
	{
		vec3d player_collision_test_point = player_controlled_entity->position + vec3d(0, 0.1, 0);

		for (unsigned i=0; i<current_map->entity2s.size(); i++)
		{
			//current_map->entity2s[i]->place.start_transform();
			//current_map->entity2s[i]->bbox.draw();
			//current_map->entity2s[i]->place.restore_transform();
			
			current_map->entity2s[i]->update_player_collision(player_controlled_entity->position);
			

			/*
			switch(current_map->entity2s[i]->entity2_type)
			{
			case Entity2::INFO_POD:
				{
					InfoPod *info_pod = static_cast<InfoPod *>(current_map->entity2s[i]);
					break;
				}
				break;
			}
			*/





			if (current_map->entity2s[i]->player_inside)
			{
				//current_map->entity2s[i]->on_collide();

				switch(current_map->entity2s[i]->entity2_type)
				{
				case Entity2::DOOR:
					{
						Door *door = static_cast<Door *>(current_map->entity2s[i]);
						if (!door->player_in_doorway) enter_into_door(level.find_door(door->destination_door));
						break;
					}
				case Entity2::ITEM:
					{
						Item *item = static_cast<Item *>(current_map->entity2s[i]);

						//std::cout <<"A" << std::endl;
						//item->item_type;
						

						player_character.add_to_inventory(item->item_type);
						player_character.pickup_health(0.5);

						//std::cout <<"B" << std::endl;

						//std::string *str = new std::string("picked up a 
						//dirty_send_signal(asdf,

						std::cout << "picked up an item";

						current_map->remove_and_destroy_entity2(current_map->entity2s[i]);
						i--;
					}
					break;
				case Entity2::ENEMY:
					{
						Enemy *enemy = static_cast<Enemy *>(current_map->entity2s[i]);
						player_character.take_damage(enemy->damage_from_touching);
					}
					break;
				default:
					break;
				}

				/*
				if (i != 0) current_map->entity2s[i]->on_collide();
				if (current_map->entities[
				if (current_map->entity2s[i]->entity2_type == Entity2::DOOR)
				{
					Door *door = static_cast<Door *>(current_map->entity2s[i]);
					if (!door->player_in_doorway) enter_into_door(level.find_door(door->destination_door));
				}
				else if (current_map->entity2s[i]->entity2_type == Entity2::ITEM)
				{
					//player_stats->pickup_tomato();
					current_map->entity2s[i]->on_collide();//->pickup_tomato();
						
					current_map->remove_and_destroy_entity2(current_map->entity2s[i]);
					i--;
				}
				else if (current_map->entity2s[i]->entity2_type == Entity2::ENEMY)
				{
					std::cout << "E";
				}
				*/
				//std::cout << "collide" << std::endl;
			}
			else
			{
				if (current_map->entity2s[i]->entity2_type == Entity2::DOOR)
				{
					Door *door = static_cast<Door *>(current_map->entity2s[i]);
					door->player_in_doorway = false;
				}
				//player_in_doorway
			}

			/*
			.collides(player_controlled_entity->position))
				std::cout << "(" << i << "collides!!)" << std::endl;
			if (current_map->entity2s[i]->bbox.collides(player_controlled_entity->position))
				std::cout << "(" << i << "collides!!)" << std::endl;
				*/
		}
	}

		
	//if (player_controlled_entity)
	//	draw_crosshair(vec3d(player_controlled_entity->position.x, 0, player_controlled_entity->position.z));
}






void ProgramMaster::respawn()
{
	if (!player_controlled_entity) return;
	player_controlled_entity->position = vec3d(0, 6, 0);
}





