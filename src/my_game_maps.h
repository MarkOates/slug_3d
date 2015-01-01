#ifndef __SH_MY_GAME_MAPS
#define __SH_MY_GAME_MAPS





#include "map.h"



Map *create_a_map_from_model_with_cherries_in_it(std::string map_name, ALLEGRO_COLOR bg_color, std::string model_identifier, std::string texture, std::string items_model_identifier);

Map *sandbox_map();

Map *first_world_hiding_under_a_leaf();

Map *bouncy_trouncy();

Map *small_room_map();

Map *customize_character_room();

Map *water_room();

Map *climber_map();

Map *terrain_map(std::vector<Map *> other_maps_to_make_doors_to);




#endif