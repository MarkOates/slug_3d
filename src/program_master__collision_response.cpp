


#include <allegro_flare/allegro_flare.h>


#include "program_master.h"
//#include "allegro_flare.h"

#include "hud.h"




inline bool ProgramMaster::basically_equal(const vec3d &first, const vec3d &other, float threshold) const
{
return fabs(first.x - other.x) < threshold && fabs(first.y - other.y) < threshold && fabs(first.z - other.z) < threshold;
}
   

void ProgramMaster::collision_response_func_CAR(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout)
{
	entity->position += entity->velocity * time_to_collision;
	entity->position += face->normal * face_collision_stepout;
	vec3d reflection_vec = reflect(entity->velocity, face->normal);
	entity->velocity = reflection_vec;
	entity->velocity *= 0.95;
}

void ProgramMaster::collision_response_func_CRICKET(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout)
{
	entity->position += entity->velocity * time_to_collision;
	entity->position += face->normal * face_collision_stepout;
	vec3d reflection_vec = reflect(entity->velocity, face->normal);
	entity->velocity = reflection_vec;
	entity->velocity *= 0.4;
}

void ProgramMaster::collision_response_func_BALL(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout)
{
	entity->position += entity->velocity * time_to_collision;
	entity->position += face->normal * face_collision_stepout;
	vec3d reflection_vec = reflect(entity->velocity, face->normal);
	entity->velocity = reflection_vec;
	entity->velocity *= 1.0;
}

void ProgramMaster::collision_response_func_CAR_no_bounce(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout)
{
	entity->position += entity->velocity * time_to_collision;
	entity->position += face->normal * face_collision_stepout;
	vec3d reflection_vec = reflect(entity->velocity, face->normal);
	entity->velocity = reflection_vec;
	entity->velocity *= 0.95;
}

void ProgramMaster::collision_response_func_ALONG_SLIPPY(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout)
{
	bool draw_crosshairs = false;

	//intersect_info.t = 0.5;
	//std::cout << time_to_collision << std::endl;
	vec3d point_of_intersection = entity->position + time_to_collision * entity->velocity;
	if (draw_crosshairs) draw_crosshair(point_of_intersection, color::red, 0.4); // point of collision

	float STEPOUT = face_collision_stepout;
	vec3d stepout_point = point_of_intersection + face->normal * STEPOUT;
	if (draw_crosshairs) draw_crosshair(stepout_point, color::aqua, 0.4); // point of collision

	//float mag = entity->velocity.GetMagnitude();
	vec3d resultant_velocity_vector = reflect(entity->velocity, face->normal);
	if (draw_crosshairs) draw_3d_line(stepout_point, stepout_point + resultant_velocity_vector.Normalized() * 2);

	//float mag = entity->velocity.GetMagnitude();
	vec3d projected_point = project(entity->position + entity->velocity, face->v0, face->normal);
		// returns a point in world coordinates /on the plane/ that is the projection of the point.
		// you should then take it and... uh... do a stepback (same as the collision point), then find the
		// difference between this and the stepback, (but you have to make sure that the tail (part after the collision)
		// is long enough for the projection to be correct), normalize it, set it to the magnitude of the
		// original velocity, and boom.

	// plane normal projected on the plane... make a ray from the center to that point, and you'll get the slippery direction

	//vec3d plane_projected_normal = project((face->normal * face->normal), face->v0, face->normal).Normalized();


	vec3d projected_point_stepped_out = projected_point + face->normal * STEPOUT;

	if (draw_crosshairs) draw_3d_line(stepout_point, projected_point_stepped_out, color::black);

	if (draw_crosshairs) draw_crosshair(projected_point, color::darkcyan, 0.6);//stepout_point, resultant_velocity_vector, color::darkblue);


	// ok, great... now use it to do the collision response

	//std::cout << "1pos" << entity->position.GetString() << std::endl;
	//std::cout << "1vel" << entity->velocity.GetString() << std::endl;
	//std::cout << "1velmag" << entity->velocity.GetMagnitude() << std::endl;
	//std::cout << "1projected_point_stepped_out" << projected_point_stepped_out.GetString() << std::endl;
	//std::cout << "1stepout_point" << stepout_point.GetString() << std::endl;

	entity->position = stepout_point;

	// you have to watch out for 
	//if (basically_equal(projected_point_stepped_out, stepout_point)) entity->velocity = 0;
	//else entity->velocity = (projected_point_stepped_out - stepout_point).Normalized() * entity->velocity.GetMagnitude();

	entity->velocity = projected_point_stepped_out - stepout_point; // < velocity is NOT preserved,
																			// it is the difference of the 
																	// this one furgin works!!! 8o 8o 8o 8o

	//std::cout << "2pos" << entity->position.GetString() << std::endl;
	//std::cout << "2vel" << entity->velocity.GetString() << std::endl;

	//wait_for_keypress();
}

void ProgramMaster::collision_response_func_ALONG(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout)
{
	bool draw_crosshairs = false;

	//intersect_info.t = 0.5;
	//std::cout << time_to_collision << std::endl;
	vec3d point_of_intersection = entity->position + time_to_collision * entity->velocity;
	if (draw_crosshairs) draw_crosshair(point_of_intersection, color::red, 0.4); // point of collision

	float STEPOUT = face_collision_stepout;
	vec3d stepout_point = point_of_intersection + face->normal * STEPOUT;
	if (draw_crosshairs) draw_crosshair(stepout_point, color::aqua, 0.4); // point of collision

	//float mag = entity->velocity.GetMagnitude();
	vec3d resultant_velocity_vector = reflect(entity->velocity, face->normal);
	if (draw_crosshairs) draw_3d_line(stepout_point, stepout_point + resultant_velocity_vector.Normalized() * 2);

	//float mag = entity->velocity.GetMagnitude();
	vec3d projected_point = project(entity->position + entity->velocity, face->v0, face->normal);
		// returns a point in world coordinates /on the plane/ that is the projection of the point.
		// you should then take it and... uh... do a stepback (same as the collision point), then find the
		// difference between this and the stepback, (but you have to make sure that the tail (part after the collision)
		// is long enough for the projection to be correct), normalize it, set it to the magnitude of the
		// original velocity, and boom.

	vec3d projected_point_stepped_out = projected_point + face->normal * STEPOUT;

	if (draw_crosshairs) draw_3d_line(stepout_point, projected_point_stepped_out, color::black);

	if (draw_crosshairs) draw_crosshair(projected_point, color::darkcyan, 0.6);//stepout_point, resultant_velocity_vector, color::darkblue);


	// ok, great... now use it to do the collision response

	//std::cout << "1pos" << entity->position.GetString() << std::endl;
	//std::cout << "1vel" << entity->velocity.GetString() << std::endl;
	//std::cout << "1velmag" << entity->velocity.GetMagnitude() << std::endl;
	//std::cout << "1projected_point_stepped_out" << projected_point_stepped_out.GetString() << std::endl;
	//std::cout << "1stepout_point" << stepout_point.GetString() << std::endl;

	entity->position = stepout_point;

	// you have to watch out for 
	//if (basically_equal(projected_point_stepped_out, stepout_point)) entity->velocity = 0;
	//else entity->velocity = (projected_point_stepped_out - stepout_point).Normalized() * entity->velocity.GetMagnitude();

	entity->velocity = projected_point_stepped_out - stepout_point; // < velocity is NOT preserved,
																			// it is the difference of the 
																	// this one furgin works!!! 8o 8o 8o 8o

	//std::cout << "2pos" << entity->position.GetString() << std::endl;
	//std::cout << "2vel" << entity->velocity.GetString() << std::endl;

	//wait_for_keypress();
}


void ProgramMaster::update_new_triangle_thing()
{

	if (!current_map) return;








	//float AIR_DRAG = 0.06;
	//float AIR_DRAG = 0.01;
	float GRAVITY = -0.016; // reg -0.008;
	//float MIN_VELOCITY = 0.01;


	//current_map->objects[1]->place.rotation_y += 0.0025;  // yaya!!

	for (unsigned e=0; e<current_map->entities.size(); e++)
	{
		current_map->entities[e]->state_flags.unset(Entity::ON_GROUND);
	}

	// apply air drag & gravity
	for (unsigned e=0; e<current_map->entities.size(); e++)
	{
		current_map->entities[e]->add_force(vec3d(0, GRAVITY, 0));
		//current_map->entities[e]->velocity = current_map->entities[e]->velocity * (1 - AIR_DRAG);
		current_map->entities[e]->velocity = current_map->entities[e]->velocity * (1 - current_map->entities[e]->air_drag);
	}
		
	for (unsigned e=0; e<current_map->entities.size(); e++)
	{
		//current_map->entities[e]->velocity_magnitude *= (1 - AIR_DRAG);
		//current_map->entities[e]->position += current_map->entities[e]->velocity_normal * current_map->entities[e]->velocity_magnitude;
		//current_map->entities[e]->position += current_map->entities[e]->velocity;
	}


		
	// draw the main character

	//player_controlled_entity2->draw();

	// do the tests biatch!!

	if (!current_map->collision_mesh) return;

	CollisionMesh &mesh = *current_map->collision_mesh;
	//vec3d respawn(0, 20, 0);

	/*
	for (unsigned i=0; i<mesh.faces.size(); i++)
	{
		draw_crosshair(mesh.faces[i].centroid, color::dodgerblue, 0.5);
		draw_3d_line(mesh.faces[i].centroid,
			mesh.faces[i].centroid+mesh.faces[i].normal*0.75, color::aliceblue);
	}
	*/


	// do the sweep to find the least intersection time

	float time_left_in_timestep = 1.0;
	num_collision_steps = 0;

	while (time_left_in_timestep > 0)
	{
		num_collision_steps++;
		//std::cout << time_left_in_timestep << std::endl;
		//
		// find the soonest intersection time
		//

		float collision_time = 1.0;
		CollisionMesh::Face *colliding_face = NULL;
		//Model::Object *colliding_model_object = NULL;
		Entity *colliding_entity = NULL;

		for (unsigned f=0; f<mesh.faces.size(); f++)
		{
			CollisionMesh::Face &face = mesh.faces[f];
			for (unsigned e=0; e<current_map->entities.size(); e++)
			{
				Entity &entity = *current_map->entities[e];
				if (entity.velocity.GetMagnitude() > 0)
				{
					IsectData intersect_info = IsectData();

					vec3d start_pos = entity.position;
					vec3d end_pos = entity.position + entity.velocity;

					if (face.intersect(Ray(start_pos, end_pos-start_pos), intersect_info))
					{
						//vec3d collision_point = (end_pos-start_pos) * intersect.t + start_pos;
						//draw_crosshair(collision_point, color::pink, 0.5); // turning this on will show the intersection point
																			// of the projected ray

						if (intersect_info.t >= 0.0f && intersect_info.t <= 1.0f)
							if (intersect_info.t < collision_time)
							{
								collision_time = intersect_info.t;
								//std::cout << std::endl << "respawn(" << f << ") intersect.t(" << intersect.t << ") vel.mag(" << entity.velocity.GetMagnitude() << ")" << std::endl;
								//entity.position = respawn;
								colliding_face = &face;
								colliding_entity = &entity;
								//colliding_model_object = 
							}
					}
				}
			}
			//out_there:;
		}

		
		//bool freeze_this_pass = false;
		//std::cout << "time_left: " << time_left_in_timestep << " - t: " << collision_time << std::endl;
		//if (collision_time < 0.0001)
		//{
		//	freeze_this_pass = true;
		//}



		// reposition the objects to the least intersection time

		//float collision_stepback = 0.0001;
		float face_collision_stepout = 0.001; // <- YOU WERE HERE (was previously set at 0.0001
		float collision_dampening = 1.0;

		for (unsigned e=0; e<current_map->entities.size(); e++)
		{
			Entity *entity = current_map->entities[e];

			if (colliding_entity == entity)
			{
				// collision_response 
				// collision_response_func(Entity *e, collision_time, time_left_in_timestep, Face *dcolliding_face, face_collision_stepout)
					// entity
					// 
/*				if (false) // use a custom collision response function
				{
					vec3d end_point_of_full_projection = entity->position + entity->velocity;
					//float time_to_collision = collision_time * time_left_in_timestep;
					entity->position += entity->velocity * collision_time * time_left_in_timestep;

					vec3d collision_point = entity->position;
						
					entity->position += colliding_face->normal * face_collision_stepout; // slight pushback to make the thing easier

					float vel_mag = entity->velocity.GetMagnitude();
					vec3d resultant_velocity_vector = project(end_point_of_full_projection, colliding_face->v0, colliding_face->normal.Normalized()).Normalized() * vel_mag;
					//resultant_velocity_vector = 

					entity->velocity = resultant_velocity_vector;
					//entity->velocity *= collision_dampening;

				}
				else if (true)
				{
				*/

				// set the collision response func to default:
					typedef void (ProgramMaster::*collision_response_func_t)(Entity *, float, CollisionMesh::Face *, float);
					
					collision_response_func_t collision_response_func = &ProgramMaster::collision_response_func_ALONG;
					colliding_entity->state_flags.set(Entity::ON_GROUND);


					if (colliding_face->parent_models_object_num >= (int)mesh.model->objects.size())
					{
						// cannot ditermine the colliding model::object
					}
					else
					{
						Model::Object *colliding_model_object = &mesh.model->objects[colliding_face->parent_models_object_num];
						// test for colliding model::object type (by name in the model)
						
						if (colliding_model_object->name.substr(0,strlen("water")) == "water")
						{
						}
						else if (colliding_model_object->name.substr(0,strlen("bounce")) == "bounce")
						{
						}
						else if (colliding_model_object->name.substr(0,strlen("super_bounce")) == "super_bounce")
						{
						}
						else if (colliding_model_object->name.substr(0,strlen("slippy")) == "slippy")
						{
							collision_response_func = &ProgramMaster::collision_response_func_ALONG_SLIPPY;
						}
						
					}



					(this->*collision_response_func)(colliding_entity, collision_time * time_left_in_timestep, colliding_face, face_collision_stepout);



					if (colliding_face->parent_models_object_num >= (int)mesh.model->objects.size())
					{
						// cannot ditermine the colliding model::object
					}
					else
					{
						Model::Object *colliding_model_object = &mesh.model->objects[colliding_face->parent_models_object_num];
						// test for colliding model::object type (by name in the model)
						
						if (colliding_model_object->name.substr(0,strlen("water")) == "water")
						{
							//std::cout << "W";
							player_character.pickup_hydration(0.005);
						}
						else if (colliding_model_object->name.substr(0,strlen("bounce")) == "bounce")
						{
							//colliding_entity->velocity += vec3d(0, 1, 0);
							colliding_entity->velocity += colliding_face->normal * 1;
						}
						else if (colliding_model_object->name.substr(0,strlen("super_bounce")) == "super_bounce")
						{
							//colliding_entity->velocity += vec3d(0, 1, 0);
							colliding_entity->velocity += colliding_face->normal * 8;
						}
						else if (colliding_model_object->name.substr(0,strlen("slippy")) == "slippy")
						{
							//colliding_entity->velocity += vec3d(0, 1, 0);
							std::cout << "S";
							//colliding_entity->velocity += colliding_face->normal * 10;
							colliding_entity->state_flags.unset(Entity::ON_GROUND);
						}
						
					}
				/*}*/
	
				//colliding_face->draw(color::orange); // if you wan tto draw the colliding face
			}
			else
			{
				entity->position += entity->velocity * collision_time * time_left_in_timestep;
			}
		}


		//if (freeze_this_pass) wait_for_keypress();

		time_left_in_timestep -= (time_left_in_timestep * collision_time);
		//for (long long i=0; i<9999999; i++) {}
	}
	//std::cout << "============" << num_steps << std::endl;
}

