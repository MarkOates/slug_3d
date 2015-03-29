





#include <slug_3d/player_character.h>
#include <slug_3d/map.h>





PlayerCharacter::PlayerCharacter(Map *map)
	: slug(NULL)
	, shell(NULL)
	, entity(NULL)
	, state()
	, hydration(4)
	, max_hydration(5)
	, health(2)
	, max_health(3)
	, experience_left_to_strengh_up(10)
	, strength(1)
	, numb_from_damage_counter(2)
	, numb_time(1.25)
	, inventory()
	, strike_distance(4)
	, strike_stretch(0)
	, all_leveled_up(false)
	, num_level_ups(0)
{
	
	slug = new Entity2(map, Entity2::FORCE_FIELD, models["hero-06.obj"], "");
	//models["hero-06.obj"]->textures.set_texture(0, bitmaps["scaly.jpg"]);
	//models["hero-06.obj"]->textures.set_texture(1, bitmaps["scaly.jpg"]);
	//models["hero-06.obj"]->textures.set_texture(2, bitmaps["scaly.jpg"]);
	slug->textures.set_texture_by_index(0, bitmaps["scaly.jpg"]);
	//slug->textures.set_texture(1, bitmaps["scaly.jpg"]);
	//slug->textures.set_texture(2, bitmaps["scaly.jpg"]);
	
	shell = new Entity2(NULL, Entity2::PLAYER, models["simple_bitmap_on_back-01.obj"], "");
	shell->textures.set_texture_by_index(0, bitmaps["nothing.png"]);//nothing.png
	shell->place.scale.x = 0.7;
	shell->place.scale.z = 0.7;
	
	entity = new Entity(NULL);
}




void PlayerCharacter::add_to_inventory(Item::item_t item)
{
	if (get_num_items(item) < 99) inventory.push_back(item);
	std::cout << "added_to_inventory";
}



std::vector<Item::item_t> PlayerCharacter::get_unique_list_of_items()
{
	std::vector<Item::item_t> item_list = inventory;
	///return std::unique (list.begin(), myvector.end(), myfunction);    /// bah, no time for this...
	for (unsigned i=0; i<inventory.size(); i++)
	{
		bool has_item = false;
		for (unsigned l=0; l<item_list.size(); l++)
		{
			if (item_list[i] == inventory[i])
			{
				has_item = true;
				break;
			}
		}
		if (!has_item) item_list.push_back(inventory[i]);
	}


	std::cout << "items:" << std::endl;
	for (unsigned i=0; i<item_list.size(); i++)
	{
		std::cout << item_list[i] << std::endl;
	}
	std::cout << "items:" << std::endl;


	return item_list;
}



int PlayerCharacter::get_num_items(Item::item_t item)
{
	int count = 0;
	for (unsigned i=0; i<inventory.size(); i++)
	{
		if (item == inventory[i]) count++;
	}
	return count;
}


#include <slug_3d/dirty_signal_send.h>

void PlayerCharacter::pickup_experience(float amt)
{
	total_exp_gained += amt;

	if (all_leveled_up) return;

	experience_left_to_strengh_up -= amt;
	if (experience_left_to_strengh_up <= 0)
	{
		bool leveled_up_successfully = false;
		int tries = 300;
		while (!leveled_up_successfully && tries > 0)
		{
			tries--;
			switch(random_int(0, 2))
			{
			case 0:
				// level up your strength;
				if (strength < 10) // SHOULD BE 40
				{
					strength += 1;
					std::string *str = new std::string("Strength++/You Leveled Up!/Your attack strength has increased by 1/");
					dirty_send_signal(SIGNAL_SET_DIALOGUE_TEXT, (void *)str);
					delete str;
					leveled_up_successfully = true;
				}
				break;
			case 1:
				// level up your max health;
				if (max_health < 20) // SHOULD BE 40
				{
					max_health += 1;
					std::string *str = new std::string("Max Health++/You Leveled Up!/Your maximum health has increased by 1/");
					dirty_send_signal(SIGNAL_SET_DIALOGUE_TEXT, (void *)str);
					delete str;
					//experience_left_to_strengh_up = 50;
					leveled_up_successfully = true;
				}
				break;
			case 2:
				// level up your hydration;
				if (max_hydration < 15) // SHOULD BE 40
				{
					max_hydration += 1;
					std::string *str = new std::string("Hydration++/You Leveled Up!/Your hydration has increased by 1/");
					dirty_send_signal(SIGNAL_SET_DIALOGUE_TEXT, (void *)str);
					delete str;
					//experience_left_to_strengh_up = 50;
					leveled_up_successfully = true;
				}
				break;
			}
		}

		if (leveled_up_successfully)
		{
			experience_left_to_strengh_up = 10;
			num_level_ups++;
		}
		else
		{
			all_leveled_up = true;
		}
	}
}


void PlayerCharacter::pickup_hydration(float amt)
{
	hydration += amt;
	if (hydration >= max_hydration) hydration = max_hydration;
}


void PlayerCharacter::pickup_health(float amt)
{
	health += amt;
	if (health >= max_health) health = max_health;
}


void PlayerCharacter::equip_shell(std::string model_identifier)
{
	//if (shell) shell->map->remove_and_destroy_entity2(shell);

	shell->textures.set_texture_by_index(0, bitmaps[model_identifier]);
	//shell = new Entity2(map, Entity2::
	//if (models[model_identifier])
	//if (!

	//shell = NULL;

	//shell->map->model
}


void PlayerCharacter::picukup_strike_distance()
{
	strike_distance += 2;
}



void PlayerCharacter::put_in_map(Map *map, vec3d location)
{
	if (map)
	{
		if (entity->map) entity->map->unregister_entity(entity);
		if (slug->map) slug->map->unregister_entity2(slug);
		if (shell && shell->map) shell->map->unregister_entity2(shell);

		map->register_entity(entity);
		map->register_entity2(slug);
		map->register_entity2(shell);
	}

	entity->position = location;
	entity->velocity = 0;
		
	entity->map = map;
	slug->map = map;
	if (shell) shell->map = map;
}



void PlayerCharacter::try_frontal_attack()
{
	state.set(FRONTAL_STRIKE_ATTACK);
	strike_stretch = 1;
}



void PlayerCharacter::try_spinning_attack()
{
	state.set(SPINNING_STRIKE_ATTACK);
	std::cout << "attack!";
}


bool PlayerCharacter::take_damage(float hydration, float health)
{
	if (state.has(NUMB_FROM_DAMAGE)) return false;

	this->health -= health;
	this->hydration -= hydration;
	if (hydration < 0) hydration = 0;
	if (health < 0)
	{
		health = 0;
		state.set(DEAD);
	}

	state.set(NUMB_FROM_DAMAGE);
	numb_from_damage_counter = numb_time; // seconds

	return true;
}



bool PlayerCharacter::take_damage(float amt)
{
	if (state.has(NUMB_FROM_DAMAGE)) return false;

	health -= std::max(0.0f, (amt - hydration));
	hydration -= amt;

	if (hydration < 0) hydration = 0;
	if (health < 0)
	{
		health = 0;
		state.set(DEAD);
	}

	state.set(NUMB_FROM_DAMAGE);
	numb_from_damage_counter = numb_time; // seconds

	return true;
}



float PlayerCharacter::get_y_rotation()
{
	return vec2d(entity->view_vector.z, entity->view_vector.x).get_angle() / TAU;//-vec2d(entity->view_vector.z, entity->view_vector.x).GetAngle();
}



float PlayerCharacter::get_x_rotation()
{
	//return vec2d(entity->view_vector.y, entity->view_vector.x).GetAngle() / TAU;//-vec2d(entity->view_vector.z, entity->view_vector.x).GetAngle();
	return 0;
}



#include <allegro_flare/allegro_flare.h>

//#include "allegro_flare.h"


void PlayerCharacter::update()
{
	numb_from_damage_counter -= 1.0/60.0;
	if (numb_from_damage_counter <= 0)
	{
		numb_from_damage_counter = 0;
		state.unset(NUMB_FROM_DAMAGE); // eh... doing this every frame is kinda lame
	}


	slug->place.position.x = entity->position.x;
	slug->place.position.y = entity->position.y;
	slug->place.position.z = entity->position.z;

	if (shell)
	{
		shell->place.position.x = entity->position.x;
		shell->place.position.y = entity->position.y;
		shell->place.position.z = entity->position.z;
	}

	slug->place.scale.z = 1.0;

	//bool moving = true;
	if (entity->state_flags.has(Entity::MOVING))
	{
		slug->place.scale.y = 1.0 + cos(af::time_now*10) * 0.3;
		slug->place.scale.z = 1.0 + cos(af::time_now*11) * 0.2;

		if (shell)
		{
			shell->place.position.y = shell->place.position.y + cos(af::time_now*9) * 0.05 + 0.1;
		}
	}


	strike_stretch -= 0.1;
	if (strike_stretch < 0) strike_stretch = 0;
	slug->place.scale.z = slug->place.scale.z + interpolator::quadrupleSlowIn(strike_stretch) * strike_distance;


	float player_rotation_y = get_y_rotation();


	slug->place.rotation.y = player_rotation_y;
	//slug->place.rotation_x = get_x_rotation();
	if (shell) shell->place.rotation.y = player_rotation_y;
}
