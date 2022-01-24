


#include <allegro_flare/allegro_flare.h>


#include <slug_3d/enemy.h>
//#include "allegro_flare.h"





Enemy::Enemy(Map *map, AllegroFlare::vec3d position, AllegroFlare::Model3D *model)
	: Entity2(map, Entity2::ENEMY, model)
	, view_direction(AllegroFlare::vec3d((AllegroFlare::random_float(0, 10)+0.1)*AllegroFlare::random_sign(), 0, (AllegroFlare::random_float(0, 10)+0.1)*AllegroFlare::random_sign()).normalized())
	, speed(0.06)
	, health(1)
	, damage_from_touching(0.5)
	, exp_from_kill(1)
{
	place.position.x = position.x;
	place.position.y = position.y;
	place.position.z = position.z;
	data = "enemy";

	bbox.resize(AllegroFlare::vec3d(1, 1, 1));
}

void Enemy::update()
{
	place.rotation.y = AllegroFlare::vec2d(view_direction.z, view_direction.x).get_angle() / AllegroFlare::TAU;
	place.rotation.x = 0; // dunno these
	place.rotation.z = 0; // dunno these
}

bool Enemy::take_damage(float damage)
{
	health -= damage;
	if (health <= 0)
	{
		state.set(DEAD_AND_CAN_BE_DESTROYED);
		return true;
	}
	return false;
}





AntEnemy::AntEnemy(Map *map, AllegroFlare::vec3d position, AllegroFlare::vec3d domain_min, AllegroFlare::vec3d domain_max)
	: Enemy(map, position, map->models["ant-03.obj"])
	, domain()
{
	//textures.set_texture_by_index(0, map->bitmaps["an_grey.png"]);
	model->texture = map->bitmaps["an_grey.png"];
	//colors.set_color(0, color::black);
	domain.min = AllegroFlare::vec3d(std::min(domain_min.x, domain_max.x), position.y, std::min(domain_min.z, domain_max.z));
	domain.max = AllegroFlare::vec3d(std::max(domain_min.x, domain_max.x), position.y, std::max(domain_min.z, domain_max.z));
}

bool AntEnemy::in_domain()
{
	return domain.collides(AllegroFlare::vec3d(place.position.x, place.position.y, place.position.z));
}

AllegroFlare::vec3d AntEnemy::get_domain_center()
{
	return (domain.max - domain.min) / 2 + domain.min;
}

void AntEnemy::face_target(AllegroFlare::vec3d target)
{
	view_direction = (target - AllegroFlare::vec3d(place.position.x, place.position.y, place.position.z)).normalized();
}

void AntEnemy::make_red()
{
	//set_color(0, color::red);
	speed = 0.1;
	health = 5;
	damage_from_touching = 1;
	exp_from_kill = 2;
}

void AntEnemy::make_blue()
{
	//colors.set_color(0, color::blue);
	speed = 0.1;
	health = 10;
	damage_from_touching = 2;
	exp_from_kill = 5;
}

void AntEnemy::make_white()
{
	//colors.set_color(0, color::red);
	speed = 0.2;
	health = 15;
	damage_from_touching = 2;
	//colors.set_color(0, color::white);
	exp_from_kill = 10;
}



void AntEnemy::update()
{
	state_counter -= 1.0/60.0;
	// check for a state change

	if (state_counter < 0)
	{
		// change the state!!
		if (state.has(MOVING))
		{
			state.unset(MOVING);
			state.set(TURNING);
			state_counter = AllegroFlare::random_float(0.1, 0.5);
		}
		else
		{
			state.set(MOVING);
			state.unset(TURNING);
			state_counter = AllegroFlare::random_float(1, 3);
		}
	}


	// update based on the current states

	if (!in_domain())
	{
		face_target(get_domain_center());
	}

	if (state.has(MOVING))
	{
      AllegroFlare::vec3d velocity = view_direction * speed;
		place.position.x += velocity.x;
		place.position.y += velocity.y;
		place.position.z += velocity.z;
		place.scale.z = cos(allegro_flare::Framework::time_now*20)*0.2 + 1.0;
	}

	if (state.has(TURNING))
	{
      AllegroFlare::vec2d point(view_direction.x, view_direction.z);
		point = rotate_point(point, speed);
		view_direction.x = point.x;
		view_direction.z = point.y;
	}

	Enemy::update(); // refreshes the rotation information;
}





BeetleEnemy::BeetleEnemy(Map *map, AllegroFlare::vec3d position)
	: Enemy(map, position, map->models["ant-03.obj"])
{
	//BeetleEnemy::textures.set_texture_by_index(0, map->bitmaps["ant-03.png"]);
}


