

#include <slug_3d/door.h>
#include <slug_3d/map.h>




Door::Door(Map *map, door_t type, std::string door_name, vec3d location, float rotation, std::string destination_door)
	: Entity2(map, Entity2::DOOR, map->models["door-05.obj"])
	, door_name(door_name)
	, type(type)
	, destination_door(destination_door)
	, player_in_doorway(false)
{
	//this->textures.set_texture_by_index(0, map->bitmaps["door_texture_256.jpg"]);
	model->texture = map->bitmaps["door_texture_256.jpg"];

	this->place.position.x = location.x;
	this->place.position.y = location.y;
	this->place.position.z = location.z;

	//if (type == DOOR_LARGE)
	//{
	//}

	/*
	this->bbox._position = location;

	this->place.x = location.x;
	this->place.y = location.y;
	this->place.z = location.z;

	this->place.scale_x = 0.5;
	this->place.scale_y = 0.5;
	this->place.scale_z = 0.5;

	if (type == ITEM_TYPE_HEART)
	{
		textures.set_texture(0, map->bitmaps["heart_item-01tx.png"]);
		speed_diff = random_float(0.9, 1.1);
		bbox.min = vec3d(-1.0, -1.0, -1.0);
		bbox.max = vec3d(1.0, 1.0, 1.0);
		//blender = blender_t::BLENDER_ADDITIVE;
	}
	*/
}


