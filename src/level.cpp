


#include "level.h"

#include <allegro_flare/color.h>

//#include "color.h"


#include "my_game_maps.h"



Level::Level()
{
	maps.push_back(sandbox_map());
	maps.push_back(water_room());
	maps.push_back(customize_character_room());
	//maps.push_back(create_a_map_from_model_with_cherries_in_it("first_chaser", color::firebrick, "first_chaser_03.obj", "quarter.png", "first_chaser-_items_03.obj"));
	//maps.push_back(create_a_map_from_model_with_cherries_in_it("Box Land", color::burlywood, "mpy_model_with_squares-02.obj", "try-dis.jpg", ""));
	//maps.push_back(create_a_map_from_model_with_cherries_in_it("first_chaser", color::firebrick, "first_chaser-03.obj", "quarter.png", "first_chaser_items-03.obj"));
	//maps.push_back(small_room_map());
	//maps.push_back(climber_map());

	maps.push_back(bouncy_trouncy());

	maps.push_back(terrain_map(maps));
	maps.push_back(first_world_hiding_under_a_leaf()); // this should be the last room in the release version


}

void Level::list_all_entity2s()
{
	for (unsigned m=0; m<maps.size(); m++)
	{
		for (unsigned i=0; i<maps[m]->entity2s.size(); i++)
		{
			if (maps[m]->entity2s[i]->entity2_type == Entity2::DOOR)
			{
				Door *door = static_cast<Door *>(maps[m]->entity2s[i]);
				std::cout << "map: " << m << " ins: " << maps[m]->entity2s[i]->entity2_type ;//<< std::endl;
				std::cout << "name: " << door->door_name << std::endl;
				//Door *door = static_cast<Door *>(maps[m]->entity2s[i]);
				//if (door->door_name == door_name) return door;
			}
		}
	}
}

Door *Level::find_door(std::string door_name)
{
	for (unsigned m=0; m<maps.size(); m++)
	{
		for (unsigned i=0; i<maps[m]->entity2s.size(); i++)
		{
			if (maps[m]->entity2s[i]->entity2_type == Entity2::DOOR)
			{
				Door *door = static_cast<Door *>(maps[m]->entity2s[i]);
				std::cout << "map: " << m << " ins: " << maps[m]->entity2s[i]->entity2_type ;//<< std::endl;
				std::cout << "name: " << door->door_name << std::endl;
				//Door *door = static_cast<Door *>(maps[m]->entity2s[i]);
				if (door->door_name == door_name)
				{
					std::cout << "found door! \"" << door_name << "\"" << std::endl;
					return door;
				}
			}
		}
	}

	std::cout << "could not find the door \"" << door_name << "\"" << std::endl;
	return NULL;

}





