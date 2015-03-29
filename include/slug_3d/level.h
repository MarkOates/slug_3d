#ifndef __SH_LEVEL_HEADER
#define __SH_LEVEL_HEADER



#include <slug_3d/door.h>
#include <slug_3d/map.h>



class Level
{
public:
	std::vector<Map *> maps;



	Level();

	void list_all_entity2s();

	Door *find_door(std::string door_name);


};




#endif