#ifndef __AF_COLLISION_MESH_HEADER
#define __AF_COLLISION_MESH_HEADER



#include <AllegroFlare/Vec3D.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <allegro_flare/useful3d.h>



#include <vector>

#include <allegro5/allegro_primitives.h>

//#include "vec3d.h"

//#include "model.h"
//#include "useful3d.h"



class CollisionMesh
{
// CollisionMesh
// is essentially a Model, where
// all the faces have been cached
// into one long std::vector of Face objects.
public:
	class Face
		// -is triangulated
		// the Face class is essentially
		// a chashed version of the model's
		// data, that can be quickly
		// used when calculating collisions.
		// for the most part, the member
		// variables should not be modified
		// because they are all interdependent
		// they are left public for accessibility
	{
	public:
      AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av0, av1, av2;
      AllegroFlare::vec3d v0, v1, v2;
      AllegroFlare::vec3d normal;
      AllegroFlare::vec3d centroid;
		
		int parent_models_object_num;
		int parent_models_face_num;

		Face(AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av0, AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av1, AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av2,
			int parent_models_object_num, int parent_models_face_num,
			AllegroFlare::vec3d normal=AllegroFlare::vec3d(0)
			);

		bool intersect(const allegro_flare::Ray &r, allegro_flare::IsectData &isectData) const;

		void draw(ALLEGRO_COLOR col=AllegroFlare::color::azure);
	};


	std::vector<Face> faces;
   AllegroFlare::Model3D *model;

	CollisionMesh(AllegroFlare::Model3D *m);
};




#endif
