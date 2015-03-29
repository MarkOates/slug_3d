	float _sign(ALLEGRO_VERTEX p1, ALLEGRO_VERTEX p2, ALLEGRO_VERTEX p3)
	{
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}

	bool PointInTriangle(ALLEGRO_VERTEX pt, ALLEGRO_VERTEX v1, ALLEGRO_VERTEX v2, ALLEGRO_VERTEX v3)
	{
		bool b1, b2, b3;

		b1 = _sign(pt, v1, v2) < 0.0f;
		b2 = _sign(pt, v2, v3) < 0.0f;
		b3 = _sign(pt, v3, v1) < 0.0f;

		return ((b1 == b2) && (b2 == b3));
	}

	float _sign(vec3d p1, vec3d p2, vec3d p3)
	{
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}

	bool PointInTriangle(vec3d pt, vec3d v1, vec3d v2, vec3d v3)
	{
		bool b1, b2, b3;

		b1 = _sign(pt, v1, v2) < 0.0f;
		b2 = _sign(pt, v2, v3) < 0.0f;
		b3 = _sign(pt, v3, v1) < 0.0f;

		return ((b1 == b2) && (b2 == b3));
	}




//#include <

//bool raysphere(vec3d sphere_center, vec3d direction_vec,
//	vec3d start_of_ray, float sphere_radius)


bool raysphere(float xc, float yc, float zc,
	float xd, float yd, float zd,
	float xs, float ys, float zs,
	float r)
{
	float b = 2*(xd*(xs-xc)+yd*(ys-yc)+zd*(zs-zc));
	float c=xs*xs-2*xs*xc+xc*xc+ys*ys-2*ys*yc+yc*yc+zs*zs-2*zs*zc+zc*zc-r*r;
	float disc=(b*b-4*c);
	if (disc < 0) return false; // this means we would need to divide by 
	else return true;
}




#include <allegro_flare/useful.h>
#include <allegro_flare/vec3d.h>


//#include "useful.h"


//#include "vec3d.h"

//bool rayplane(vec3d normal_vector,
//			vec3d ray_start,
//			vec3d ray_direction,
//			vec3d point1, point2, point3, point4)
//{}



float trianglearea(vec3d p1, vec3d p2, vec3d p3)
{
	// this is the "heron formula"

	float a=sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y)+(p2.z-p1.z)*(p2.z-p1.z));
	float b=sqrt((p3.x-p2.x)*(p3.x-p2.x)+(p3.y-p2.y)*(p3.y-p2.y)+(p3.z-p2.z)*(p3.z-p2.z));
	float c=sqrt((p3.x-p1.x)*(p3.x-p1.x)+(p3.y-p1.y)*(p3.y-p1.y)+(p3.z-p1.z)*(p3.z-p1.z));

	float s=(a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}



bool rayplane(float nx, float ny, float nz,
	float xs, float ys, float zs,
	float xd, float yd, float zd,
	vec3d p1, vec3d p2, vec3d p3, vec3d p4)
{
	float a = xd*nx+yd*ny+zd*nz;
	if (a == 0) return false;
	//if (basically_equal(a, 0, 0.00000001)) return false; // maybe?
	float t=(p1.x*nx+p1.y*ny+p1.z*nz-nx*xs-ny*ys-nz*zs)/a;

	if (t<0)
		return false; // the plane is colliding /behind/ the plane

	// these three points are the point of the intersection on the plane
	float x=xs+t*xd; 
	float y=ys+t*yd;
	float z=zs+t*zd;

	// you could return it from here if you wanted to, to return
	// the point colliding on a continuous plane.

	// now.. calculate the area of the triangle 

	vec3d cp(x, y, z); // the collision point
	if (abs(trianglearea(p1,p3,p4)-trianglearea(p1,p4,cp)-trianglearea(p1,p3,cp)-trianglearea(p3,p4,cp)) < 0.00001 || abs(trianglearea(p1, p2, p3)-trianglearea(p1,p2,cp)-trianglearea(p2,p3,cp)-trianglearea(p1,p3,cp))<0.00001)
		return true;
	return false;
	//if (basically_equal(trianglearea(p1,p3,p4), trianglearea(p1,p4,cp) + trianglearea(p1,p3,cp) + trianglearea(p3,p4,cp), 0.00001)
}





bool rayplane(float nx, float ny, float nz,
	float xs, float ys, float zs,
	float xd, float yd, float zd,
	vec3d p1, vec3d p2, vec3d p3)
{
	float a = xd*nx+yd*ny+zd*nz;
	if (a == 0) return false;
	//if (basically_equal(a, 0, 0.00000001)) return false; // maybe?
	float t=(p1.x*nx+p1.y*ny+p1.z*nz-nx*xs-ny*ys-nz*zs)/a;

	if (t<0)
	{
		//std::cout << ".";
		return false; // the plane is colliding /behind/ the plane
	}

	// these three points are the point of the intersection on the plane
	float x=xs+t*xd; 
	float y=ys+t*yd;
	float z=zs+t*zd;

	// you could return it from here if you wanted to, to return
	// the point colliding on a continuous plane.

	// now.. calculate the area of the triangle 

	vec3d cp(x, y, z);

	//draw_crosshair(cp, color::yellow, 4);

	if (PointInTriangle(cp, p1, p2, p3)) return true; // << this seems to work much more effectively than the function trianglearea option below:
		return false;

	//if (abs(trianglearea(p1, p2, p3)-trianglearea(p1,p2,cp)-trianglearea(p2,p3,cp)-trianglearea(p1,p3,cp))<0.00001)
	//	return true;
	return false;
	//if (basically_equal(trianglearea(p1,p3,p4), trianglearea(p1,p4,cp) + trianglearea(p1,p3,cp) + trianglearea(p3,p4,cp), 0.00001)
}



vec3d get_ray_plane_intersection_point(float nx, float ny, float nz,
	float xs, float ys, float zs,
	float xd, float yd, float zd,
	vec3d p1, vec3d p2, vec3d p3)
{
	float a = xd*nx+yd*ny+zd*nz;
	if (a == 0) return false;
	//if (basically_equal(a, 0, 0.00000001)) return false; // maybe?
	float t=(p1.x*nx+p1.y*ny+p1.z*nz-nx*xs-ny*ys-nz*zs)/a;

	if (t<0)
		return false; // the plane is colliding /behind/ the plane

	// these three points are the point of the intersection on the plane
	float x=xs+t*xd; 
	float y=ys+t*yd;
	float z=zs+t*zd;

	return vec3d(x, y, z);
}