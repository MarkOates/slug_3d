

#include <allegro_flare/blender.h>


#include <slug_3d/map.h>

//#include "blender.h"



Map::Map()
	: name("Untitled Map")
	, spawn(0, 0, 0)
	, bitmaps()
	, models()
	, clear_color(AllegroFlare::color::hex("a1de65"))
	, bboxes()
	, collision_mesh(NULL)
{
   std::cout << "6------------------" << std::endl;
   models.set_full_path("/Users/markoates/Repos/slug_3d/bin/data/models");
	clear();
}



void Map::clear()
{
	for (unsigned i=0; i<entity2s.size(); i++)
		delete entity2s[i];
	entity2s.clear();

	spawn_view = AllegroFlare::vec3d(0, 0, 1).normalized();
	spawn = 0;

	bboxes.clear();

	collision_mesh = NULL;
}






/*
Entity2 *Map::make_add_entity2(std::string model_identifier, vec3d position, vec3d scale)
{
	Entity2 *entity2 = new Entity2(this, models[model_identifier]);

	//object->model->set_texture(bitmaps[texture_identifier], 0);

	entity2->place.x = position.x;
	entity2->place.y = position.y;
	entity2->place.z = position.z;

	entity2->place.scale_x = scale.x;
	entity2->place.scale_y = scale.y;
	entity2->place.scale_z = scale.z;

	entity2s.push_back(entity2);
	return entity2;
}
*/




bool Map::remove_and_destroy_entity2(Entity2 *entity2)
{
	if (unregister_entity2(entity2))
	{
		delete entity2;
		return true;
	}
	return false;
}



void Map::draw()
{
	al_clear_to_color(clear_color);

	// draw the objects
	for (unsigned i=0; i<entity2s.size(); i++)
	{
		//set_blender(BLENDER_ADDITIVE);
		entity2s[i]->draw();
		//set_blender(BLENDER_NORMAL);

	}

	// draw the entities
	for (unsigned e=0; e<entities.size(); e++)
		entities[e]->draw();
}



void Map::draw_triangles_and_normals()
{
	//draw_triangles_and_normals

	for (unsigned i=0; i<entity2s.size(); i++)
		entity2s[i]->draw_triangles_and_normals();
}




void Map::draw_entities()
{
   AllegroFlare::Model3D *unit_sphere = models["unit_sphere-01.obj"];
	if (!unit_sphere) return;
	for (unsigned i=0; i<entities.size(); i++)
	{
		//draw_crosshair(entities[i]->position, color::yellow, 0.25);
		//unit_sphere->draw(
		//unit_sphere->move_to(0, 0, 0
	}
}



bool Map::entity_registered(Entity *entity)
{
	for (unsigned i=0; i<entities.size(); i++)
		if (entities[i] == entity) return true;
	return false;
}



void Map::register_entity(Entity *entity)
{
	if (!entity_registered(entity)) entities.push_back(entity);
}



int Map::unregister_entity(Entity *entity)
{
	bool found = false;
	for (unsigned i=0; i<entities.size(); i++)
	{
		if (entities[i] == entity)
		{
			entities.erase(entities.begin() + i);
			i--;
			found = true;
		}
	}
	return found;
}




bool Map::entity2_registered(Entity2 *entity2)
{
	for (unsigned i=0; i<entity2s.size(); i++)
		if (entity2s[i] == entity2) return true;
	return false;
}



void Map::register_entity2(Entity2 *entity2)
{
	if (!entity2) return;

	if (!entity2_registered(entity2)) entity2s.push_back(entity2);
}



int Map::unregister_entity2(Entity2 *entity2)
{
	bool found = false;
	for (unsigned i=0; i<entity2s.size(); i++)
	{
		if (entity2s[i] == entity2)
		{
			entity2s.erase(entity2s.begin() + i);
			i--;
			found = true;
		}
	}
	return found;
}



int Map::get_num_enemies()
{
	int num_enemies = 0;
	// count the number of enemies
	for (unsigned i=0; i<entity2s.size(); i++)
	{
		// if the player is outside the collision mesh's box... set his OUT_OF_BOUNDS flag
		if (entity2s[i]->entity2_type == Entity2::ENEMY)
		{
			num_enemies++;
		}
	}
	return num_enemies;
}
