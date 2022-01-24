#ifndef __AF_AABB3D_HEADER
#define __AF_AABB3D_HEADER




#include <string>
//#include "vec3d.h"
//#include <allegro_flare/vec3d.h>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro_color.h>


class AABB3D
{
private:
	ALLEGRO_COLOR color;
public:
	std::string data;
	//vec3d _position;
	//vec3d _hsize;

   AllegroFlare::vec3d max, min;

	AABB3D(std::string data="");

	bool collides(AllegroFlare::vec3d point);
	//bool collides(AABB3D *other); // untested
	void draw();
	void resize(AllegroFlare::vec3d new_size);
};




#endif
