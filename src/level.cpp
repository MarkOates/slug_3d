



#include <slug_3d/level.h>

#include <AllegroFlare/Color.hpp>

//#include "color.h"


#include <slug_3d/map_factory.h>



Level::Level()
{
	//maps.push_back(create_a_map_from_model_with_cherries_in_it("first_chaser", color::firebrick, "first_chaser_03.obj", "quarter.png", "first_chaser-_items_03.obj"));
	//maps.push_back(create_a_map_from_model_with_cherries_in_it("Box Land", color::burlywood, "mpy_model_with_squares-02.obj", "try-dis.jpg", ""));
	//maps.push_back(create_a_map_from_model_with_cherries_in_it("first_chaser", color::firebrick, "first_chaser-03.obj", "quarter.png", "first_chaser_items-03.obj"));
	//maps.push_back(small_room_map());
	//maps.push_back(climber_map());


//	maps.push_back(MapFactory::construct());
   std::cout << "-----------------4" << std::endl;



	// these are the maps from the original slugs life
   std::cout << "-----------------4*" << std::endl;
	maps.push_back(MapFactory::sandbox_map());
   std::cout << "-----------------4A" << std::endl;
	maps.push_back(MapFactory::water_room());
   std::cout << "-----------------4B" << std::endl;
	maps.push_back(MapFactory::customize_character_room());
   std::cout << "-----------------4C" << std::endl;
	maps.push_back(MapFactory::bouncy_trouncy());
	maps.push_back(MapFactory::terrain_map(maps));
	maps.push_back(MapFactory::first_world_hiding_under_a_leaf()); // this should be the last room in the release version

   std::cout << "5------------------" << std::endl;
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





