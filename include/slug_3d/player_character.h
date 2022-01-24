
#ifndef __SH_PLAYER_CHARACTER
#define __SH_PLAYER_CHARACTER



#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/BitmapBin.hpp>



//#include "model_bin.h"
//#include "bitmap_bin.h"
#include <slug_3d/entity.h>
//#include "model.h"
#include <slug_3d/map.h>
#include <slug_3d/item.h>


class PlayerCharacter
{
public:
	enum player_character_state_t
	{
		FRONTAL_STRIKE_ATTACK = 0x01,
		SPINNING_STRIKE_ATTACK = 0x02,
		NUMB_FROM_DAMAGE = 0x04,
		DEAD = 0X08,
		OUT_OF_BOUNDS = 0x10
	};

	std::vector<Item::item_t> inventory;
	void add_to_inventory(Item::item_t item);
	int get_num_items(Item::item_t item);

   AllegroFlare::ModelBin models;
   AllegroFlare::BitmapBin bitmaps;
	Entity *entity;
	Entity2 *slug;
	Entity2 *shell;
   allegro_flare::BitFlags<int> state;

	int strike_distance;
	float strike_stretch;
	int num_level_ups;

	float numb_from_damage_counter;
	float const numb_time;
	bool all_leveled_up;
	int total_exp_gained;

	float strength;
	float experience_left_to_strengh_up;
	void pickup_experience(float ammt);

	float hydration;
	float max_hydration;
	void pickup_hydration(float ammt);

	float health;
	float max_health;
	void pickup_health(float ammt);


	PlayerCharacter(Map *map);

	void equip_shell(std::string model_identifier);

	void put_in_map(Map *map, AllegroFlare::vec3d location);

	float get_y_rotation();

	float get_x_rotation();

	bool take_damage(float amt);
	bool take_damage(float hydration, float health);

	void try_frontal_attack();
	void try_spinning_attack();

	void picukup_strike_distance();

	std::vector<Item::item_t> get_unique_list_of_items();

	void update();
};




#endif
