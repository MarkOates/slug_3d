#ifndef __SH_LEVEL_HEADER
#define __SH_LEVEL_HEADER



#include "door.h"
#include "map.h"



class Level
{
public:
	std::vector<Map *> maps;



	Level();

	void list_all_entity2s();

	Door *find_door(std::string door_name);


};




#endif