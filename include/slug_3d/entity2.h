#ifndef __SH_ENTITY2__HEADER
#define __SH_ENTITY2__HEADER




#include <allegro_flare/blender.h>
#include <allegro_flare/model.h>


//#include "model.h"
//#include "map.h"

//#include "blender.h"

class Model;
class Map;
//class AABB3D;
#include <slug_3d/aabb3d.h>
//#include "model.h"




class Entity2
{
public:
	enum entity2_t
	{
		WORLD,
		DOOR,
		ITEM,
		SCENERY,
		FORCE_FIELD,
		PLAYER,
		ENEMY,
		INFO_POD,
		PICKUP_TRINKET
	};

	//enum entity2_state_t
	//{
	//	PLAYER_INSIDE = 0x01
	//};

//private:
	

public:
	Map *map;
	entity2_t entity2_type;

	AABB3D bbox;
	Model *model;
	blender_t blender;
	TextureSet textures;
	ColorSet colors;

	placement3d place;
	std::string data;
	bool player_inside;

	Entity2(Map *map, entity2_t entity2_type, Model *model, std::string data="");

	virtual void draw();
	void draw_triangles_and_normals();
	virtual void update();
	bool collides(vec3d point);

	bool Entity2::update_player_collision(vec3d player_location);

	virtual void on_collide(); //< not used, unfortunately... but was implemented in derived classes... unfortunately not here
	virtual void on_enter(); //< not used, unfortunately... but was implemented in derived classes... unfortunately not here
	virtual void on_leave(); //< not used, unfortunately... but was implemented in derived classes... unfortunately not here
};








#endif