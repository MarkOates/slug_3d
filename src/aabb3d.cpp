


#include "aabb3d.h"



#include <allegro_flare/useful.h>





AABB3D::AABB3D(std::string data)
	: data(data)
	, color(random_color())
{}



bool AABB3D::collides(vec3d point)
{
	if (point.x < min.x) return false;
	if (point.x > max.x) return false;
	if (point.y < min.y) return false;
	if (point.y > max.y) return false;
	if (point.z < min.z) return false;
	if (point.z > max.z) return false;
	return true;
}



void AABB3D::draw()
{
	vec3d hsize = (max - min)/2;
	vec3d position = (max - min)/2 + min;

	draw_crosshair(vec3d(position.x, position.y, position.z), color, 5.0);

	ALLEGRO_VERTEX v[4];

	// bottom_face
	for (unsigned i=0; i<4; i++)
		v[i] = build_vertex(position.x, position.y-hsize.y, position.z, color, 0, 0);

	v[0].x -= hsize.x;
	v[0].z += hsize.z;

	v[1].x += hsize.x;
	v[1].z += hsize.z;

	v[2].x += hsize.x;
	v[2].z -= hsize.z;

	v[3].x -= hsize.x;
	v[3].z -= hsize.z;

	al_draw_prim(&v, NULL, NULL, 0, 4, ALLEGRO_PRIM_LINE_LOOP);


	for (unsigned i=0; i<4; i++)
		v[i].y += hsize.y*2;

	al_draw_prim(&v, NULL, NULL, 0, 4, ALLEGRO_PRIM_LINE_LOOP);
}




void AABB3D::resize(vec3d new_size)
{
	new_size = vec3d(fabs(new_size.x), fabs(new_size.y), fabs(new_size.z));
	min = -(new_size/2);
	max = new_size/2;
}