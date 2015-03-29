#ifndef __SH_DOOR_HEADER
#define __SH_DOOR_HEADER




#include <allegro_flare/model.h>

//#include "model.h"
#include <slug_3d/entity2.h>


class Door : public Entity2
{
public:
	enum door_t
	{
		DOOR_LARGE,
		DOOR_SMALL,
		DOOR_CAVE
	};

	door_t type;
	std::string door_name;
	std::string destination_door;
	bool player_in_doorway; // lets the player leave the doorframe if he wants to enter back in

public:
	Door(Map *map, door_t type, std::string door_name, vec3d location, float rotation, std::string destination_door);
};




#endif