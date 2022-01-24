#ifndef __AF_ENTITY_3D_HEADER
#define __AF_ENTITY_3D_HEADER



#include <AllegroFlare/Vec3D.hpp>
#include <allegro_flare/bit_flags.h>


//#include "vec3d.h"
//#include "flags.h"



class Map;

class Entity
{
public:

	enum entity_state_t
	{
		ON_GROUND = 0x01,
		MOVING = 0x02,
		STRAFING = 0x04
	};

   allegro_flare::BitFlags<int> state_flags;


	Map *map;

   AllegroFlare::vec3d position;
	bool moving_forward, moving_backward, strafing_right, strafing_left;

   AllegroFlare::vec3d view_vector;
   AllegroFlare::vec3d up_vector;

   AllegroFlare::vec3d velocity;
	float turning_speed;

	float air_drag; // 0 will be no drag (will not slow down to friction), 1 will be full drag (essentially cannot move, like being in molassas)
					// 0.06 is the default for air drag
	
	Entity(Map *map);

	void draw();

   AllegroFlare::vec3d get_strafe_vector();
	void add_force(AllegroFlare::vec3d force);


	void update_moving_flags();
	void update_player_controlls();

	virtual bool activate_skill(std::string skill, std::string data="");

	// these are some examples of skills (that were hard-coded)
	void move_backward(bool yes=true);
	void move_forward(bool yes=true);
	void strafe_left(bool yes=true);
	void strafe_right(bool yes=true);
	void turning(float delta);
};





#endif
