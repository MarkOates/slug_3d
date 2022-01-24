




#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Useful.hpp>
#include <cmath> // for std::fabs




#include <slug_3d/entity.h>
//#include "color.h"
//#include "useful.h"



//#include "useful3d.h"

/*
static vec3d cross_product(vec3d A, vec3d B)
{
	vec3d vector;
	vector.x = A.y*B.z - B.y*A.z;
	vector.y = B.x*A.z - A.x*B.z;
	vector.z = A.x*B.y - A.y*B.x; 
	return vector;
}


static float dot_product(vec3d A, vec3d B)
{
	return A * B;
}
*/


static void draw_3d_line(AllegroFlare::vec3d start, AllegroFlare::vec3d end, ALLEGRO_COLOR col=AllegroFlare::color::red)
{
	ALLEGRO_VERTEX vtx[2];
	vtx[0] = AllegroFlare::build_vertex(start.x, start.y, start.z, col, 0, 0);
	vtx[1] = AllegroFlare::build_vertex(end.x, end.y, end.z, col, 0, 0);
	al_draw_prim(&vtx[0], NULL, NULL, 0, 2, ALLEGRO_PRIM_LINE_LIST);
}




Entity::Entity(Map *map)
	: position(0)
	, up_vector(0, 1, 0)
	, view_vector(0, 0, 1)
	, velocity(0, 0, 0)
	//, velocity_normal(-0.3, -1, 0.3)
	//, velocity_magnitude(0)
	, moving_forward(false)
	, moving_backward(false)
	, strafing_right(false)
	, strafing_left(false)
	, turning_speed(0)
	, air_drag(0.06)
	, map(map)
	//, external_forces(0, 0, 0)
{}



void Entity::draw()
{
	bool draw_crosshairs = true;

	if (draw_crosshairs)
	{
		draw_crosshair(position, AllegroFlare::color::aquamarine, 1);
		draw_3d_line(position, position + velocity, AllegroFlare::color::pink);

      AllegroFlare::vec3d strafe_vector = cross_product(view_vector, up_vector);

		draw_3d_line(position, position + up_vector * 1, AllegroFlare::color::yellow);
		draw_3d_line(position, position + strafe_vector * 1, AllegroFlare::color::green);
	}
}


/*
void Entity::apply_force(vec3d direction_that_will_be_normalized, float magnitude)
{
	//http://www.gamedev.net/topic/357797-rotate-a-vector-by-90-degrees/
	//In a right-handed coordinate system, the rotations are as follows:
	//
	//90 degrees CW about x-axis: (x, y, z) -> (x, -z, y)
	//90 degrees CCW about x-axis: (x, y, z) -> (x, z, -y)
	//
	//90 degrees CW about y-axis: (x, y, z) -> (-z, y, x)
	//90 degrees CCW about y-axis: (x, y, z) -> (z, y, -x)
	//
	//90 degrees CW about z-axis: (x, y, z) -> (y, -x, z)
	//90 degrees CCW about z-axis: (x, y, z) -> (-y, x, z)
	//
	//If you're using a left-handed coordinate system, simply switch 'CW' with 'CCW' above. 


	vec3d velocity = velocity_normal.Normalized() * velocity_magnitude
				   + direction_that_will_be_normalized.Normalized() * magnitude;

	velocity_normal = velocity.Normalized();
	velocity_magnitude = velocity.GetMagnitude();
}
*/


void Entity::add_force(AllegroFlare::vec3d force)
{
	velocity += force;
}


void Entity::update_moving_flags()
{
	if (moving_backward || moving_forward) state_flags.set(MOVING);
	else state_flags.unset(MOVING);

	if (strafing_left || strafing_right) state_flags.set(STRAFING);
	else state_flags.unset(STRAFING);
}

void Entity::move_backward(bool yes)
{
	moving_backward = yes;
	update_moving_flags();
}
void Entity::move_forward(bool yes)
{
	moving_forward = yes;
	update_moving_flags();
}
void Entity::strafe_left(bool yes)
{
	strafing_left = yes;
	update_moving_flags();
}
void Entity::strafe_right(bool yes)
{
	strafing_right = yes;
	update_moving_flags();
}

void Entity::turning(float speed)
{
	turning_speed = speed;
}



void Entity::update_player_controlls()
{
	//vec3d velocity = velocity_normal.Normalized() * velocity_magnitude; //< problem

	float accel_velocity = 0.01;
	if (moving_forward) velocity += view_vector.normalized() * accel_velocity;
	if (moving_backward) velocity -= view_vector.normalized() * accel_velocity;
	
	if (strafing_right) velocity += get_strafe_vector() * accel_velocity;
	else if (strafing_left) velocity -= get_strafe_vector() * accel_velocity;

	if (std::fabs(turning_speed) > 0.0001)
	{
      AllegroFlare::vec2d point(view_vector.x, view_vector.z);
		point = rotate_point(point, turning_speed);

		view_vector.x = point.x;
		view_vector.z = point.y;
		//primary_camera.pitch -= af::current_event->mouse.dy * 0.004;
		//primary_camera.pitch = limit<float>(-TAU/4, TAU/4, primary_camera.pitch);

	}

	//position += velocity;

	//velocity_normal = velocity.Normalized();
	//velocity_magnitude = velocity.GetMagnitude();
}



AllegroFlare::vec3d Entity::get_strafe_vector()
{
	return cross_product(view_vector, up_vector);
}




bool Entity::activate_skill(std::string skill, std::string data)
{
	if (skill=="jump" && state_flags.has(ON_GROUND))
	{
		add_force(AllegroFlare::vec3d(0, 0.4, 0));
		return true;
	}
	return false;
}
