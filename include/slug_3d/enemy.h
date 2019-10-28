#ifndef __SH_ENEMY_CLASS
#define __SH_ENEMY_CLASS




#include <allegro_flare/model3d.h>
#include <allegro_flare/bit_flags.h>



//#include "entity.h"
#include <slug_3d/entity2.h>
//#include "model.h"
#include <slug_3d/map.h>
#include <slug_3d/aabb3d.h>
//#include "flags.h"

// for this... no collision map walking on ramps business... no time for that...
// just put em in a box and make them walk around that box



class Enemy : public Entity2
{
public:
	enum enemy_state_t
	{
		MOVING = 0x01,
		TURNING = 0x02,
		DEAD_AND_CAN_BE_DESTROYED = 0x04,
		FLASHING_DAMAGE = 0x08,
		DYING_ANIMATION = 0x16,
	};

	vec3d view_direction;
	float speed;
	BitFlags<int> state;
	float health;
	float flashing_damage_counter;
	float damage_from_touching;

	int exp_from_kill;

	Enemy(Map *map, vec3d position, Model3D *model);
	void update() override;
	bool take_damage(float damage);
};





class AntEnemy : public Enemy
{
public:
	float state_counter;
	AABB3D domain;
	//vec3d target;
	AntEnemy(Map *map, vec3d position, vec3d domain_min=0, vec3d domain_max=0);

	void update() override;

	bool in_domain();
	vec3d get_domain_center();
	void face_target(vec3d target);

	void make_red();
	void make_blue();
	void make_white();
};




class BeetleEnemy : public Enemy
{
public:
	BeetleEnemy(Map *map, vec3d position);
};





#endif
