#ifndef __AF_MAP_3D_HEADER
#define __AF_MAP_3D_HEADER



#include <AllegroFlare/Vec3D.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <allegro_flare/placement3d.h>
#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/ModelBin.hpp>


#include <string>
//#include "vec3d.h"
//#include "bitmap_bin.h"


//#include "placement3d.h"
//#include "model.h"
//#include "model_bin.h"
////#include "entity_factory.h"
#include <slug_3d/aabb3d.h>

#include <slug_3d/entity.h>
#include <slug_3d/entity2.h>

#include <slug_3d/collision_mesh.h>

#include <slug_3d/enemy.h>



class Map
{
public:
	std::string name;
   AllegroFlare::vec3d spawn;
   AllegroFlare::vec3d spawn_view;

   AllegroFlare::ModelBin models;
   AllegroFlare::BitmapBin bitmaps;

	//Model *OLD_collision_mesh;
	CollisionMesh *collision_mesh;

	std::vector<Entity2 *> entity2s; // these are like, colision maps and stuff
	std::vector<Entity *> entities; // thesee are more like physical bodies... the two should be merged.
	//std::vector<Enemy *> enemies; // I think it would be better if these (enemies, entities, and entity2s, etc) were all the same

	ALLEGRO_COLOR clear_color;

	std::vector<AABB3D *> bboxes;

	float world_size;

	Map();

	void clear();

	Entity2 *make_add_entity2(std::string model_identifier, AllegroFlare::vec3d position, AllegroFlare::vec3d scale);

	void my_dungeon_01();

	void draw();
	void draw_triangles_and_normals();
	void draw_entities();

	bool remove_and_destroy_entity2(Entity2 *);

	bool entity_registered(Entity *);
	void register_entity(Entity *);
	int unregister_entity(Entity *); // 0 if not found, otherwise num of entities matching entity that were removed.

	bool entity2_registered(Entity2 *);
	void register_entity2(Entity2 *);
	int unregister_entity2(Entity2 *); // 0 if not found, otherwise num of entities matching entity that were removed.

	void on_enter();

	int get_num_enemies();
};






#endif
