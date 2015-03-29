#ifndef __SH_MY_GAME_MAPS
#define __SH_MY_GAME_MAPS





#include <slug_3d/map.h>


class MapFactory
{
public:

	static Map *create_a_map_from_model_with_cherries_in_it(std::string map_name, ALLEGRO_COLOR bg_color, std::string model_identifier, std::string texture, std::string items_model_identifier);
	static Map *sandbox_map();
	static Map *first_world_hiding_under_a_leaf();
	static Map *bouncy_trouncy();
	static Map *small_room_map();
	static Map *customize_character_room();
	static Map *water_room();
	static Map *climber_map();
	static Map *terrain_map(std::vector<Map *> other_maps_to_make_doors_to);
	static Map *construct();
};



#endif