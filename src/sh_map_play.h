


#include "camera3d.h"
#include "map.h"
#include "entity.h"


class MapPlayNew : public SpeedHackGamePlayScreen
{
public:
	//BitmapBin bitmaps;
	Camera3D primary_camera;
	Map *current_map;

	Entity *player_controlled_entity;

	int num_collision_steps;

	MapPlayNew(Display *display)
		: SpeedHackGamePlayScreen("map_play", display)
		//: Screen(display)
		, current_map(NULL)
		, player_controlled_entity(NULL)
		, primary_camera(display->width(), display->height(), NULL)
		, num_collision_steps(0)
		, epos(0)
	{
	}

	void start_map(Map *map)
	{
		current_map = map;
		
		std::cout << "num entities: " << current_map->entities.size() << std::endl;
		std::cout << "num entity2s: " << current_map->entity2s.size() << std::endl;
	}

	void mouse_axes_func() //override
	{
		if (primary_camera.entity_attached_to)
		{
			vec2d point(primary_camera.entity_attached_to->view_vector.x, primary_camera.entity_attached_to->view_vector.z);
			point = rotate_point(point, -af::current_event->mouse.dx * 0.008);

			primary_camera.entity_attached_to->view_vector.x = point.x;
			primary_camera.entity_attached_to->view_vector.z = point.y;
			primary_camera.pitch -= af::current_event->mouse.dy * 0.004;
			primary_camera.pitch = limit<float>(-TAU/4, TAU/4, primary_camera.pitch);

			al_hide_mouse_cursor(al_get_current_display());
			al_set_mouse_xy(al_get_current_display(), al_get_display_width(al_get_current_display())/2, al_get_display_height(al_get_current_display())/2);
		}
	}

   inline bool basically_equal(const vec3d &first, const vec3d &other, float threshold=0.00001f) const
   {
    return fabs(first.x - other.x) < threshold && fabs(first.y - other.y) < threshold && fabs(first.z - other.z) < threshold;
   }
   

	void collision_response_func_CAR(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001)
	{
		entity->position += entity->velocity * time_to_collision;
		entity->position += face->normal * face_collision_stepout;
		vec3d reflection_vec = reflect(entity->velocity, face->normal);
		entity->velocity = reflection_vec;
		entity->velocity *= 0.95;
	}

	void collision_response_func_CRICKET(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001)
	{
		entity->position += entity->velocity * time_to_collision;
		entity->position += face->normal * face_collision_stepout;
		vec3d reflection_vec = reflect(entity->velocity, face->normal);
		entity->velocity = reflection_vec;
		entity->velocity *= 0.4;
	}

	void collision_response_func_BALL(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001)
	{
		entity->position += entity->velocity * time_to_collision;
		entity->position += face->normal * face_collision_stepout;
		vec3d reflection_vec = reflect(entity->velocity, face->normal);
		entity->velocity = reflection_vec;
		entity->velocity *= 1.0;
	}

	void collision_response_func_CAR_no_bounce(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001)
	{
		entity->position += entity->velocity * time_to_collision;
		entity->position += face->normal * face_collision_stepout;
		vec3d reflection_vec = reflect(entity->velocity, face->normal);
		entity->velocity = reflection_vec;
		entity->velocity *= 0.95;
	}

	void collision_response_func_ALONG(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001)
	{
		//intersect_info.t = 0.5;
		//std::cout << time_to_collision << std::endl;
		vec3d point_of_intersection = entity->position + time_to_collision * entity->velocity;
		draw_crosshair(point_of_intersection, color::red, 0.4); // point of collision

		float STEPOUT = face_collision_stepout;
		vec3d stepout_point = point_of_intersection + face->normal * STEPOUT;
		draw_crosshair(stepout_point, color::aqua, 0.4); // point of collision

		//float mag = entity->velocity.GetMagnitude();
		vec3d resultant_velocity_vector = reflect(entity->velocity, face->normal);
		draw_3d_line(stepout_point, stepout_point + resultant_velocity_vector.Normalized() * 2);

		//float mag = entity->velocity.GetMagnitude();
		vec3d projected_point = project(entity->position + entity->velocity, face->v0, face->normal);
			// returns a point in world coordinates /on the plane/ that is the projection of the point.
			// you should then take it and... uh... do a stepback (same as the collision point), then find the
			// difference between this and the stepback, (but you have to make sure that the tail (part after the collision)
			// is long enough for the projection to be correct), normalize it, set it to the magnitude of the
			// original velocity, and boom.

		vec3d projected_point_stepped_out = projected_point + face->normal * STEPOUT;

		draw_3d_line(stepout_point, projected_point_stepped_out, color::black);

		draw_crosshair(projected_point, color::darkcyan, 0.6);//stepout_point, resultant_velocity_vector, color::darkblue);


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


	struct collision_response_params
	{
	public:
		float gravity;
		float entity_air_drag;
		float environment_air_drag;

		float face_normal_stepout; // once a collision occurs, the Entity is positioned at the collision point,
									   // then the Entity is displaced (just slightly) along the normal of the 
									   // colliding face.  face_normal_stepout is the magnitude of that stepout
									   // 0.0001 to 0.001 has been used, larger numbers will cause strange things
									   // happen.

		vec3d resultant_vector(CollisionMesh::Face *face, Entity *entity); // after the entity collides with the face,
																		   // the resultant_vector is the direction 
																		   // (and velocity?) in which the entity
																		   // is now headed

		float impact_velocity_dampening; // 0 == velocity is dampened completely
										 // 1 == impact has no effect on velocity
	};



	void update_new_triangle_thing()
	{
		if (!current_map) return;






		//float AIR_DRAG = 0.06;
		//float AIR_DRAG = 0.01;
		float GRAVITY = -0.016; // reg -0.008;
		//float MIN_VELOCITY = 0.01;


		//current_map->objects[1]->place.rotation_y += 0.0025;  // yaya!!


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

		// do the tests biatch!!

		if (!current_map->collision_mesh) return;

		CollisionMesh &mesh = *current_map->collision_mesh;
		vec3d respawn(0, 20, 0);

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
					if (false) // use a custom collision response function
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
						collision_response_func_ALONG(colliding_entity, collision_time * time_left_in_timestep, colliding_face, face_collision_stepout);
					}
					/*
					else if (false)
					{
						collision_response_func_CAR(colliding_entity, collision_time * time_left_in_timestep, colliding_face, face_collision_stepout);
					}
					else 
					{
						// (default collision response goes here:)
						entity->position += entity->velocity * collision_time * time_left_in_timestep;
						entity->position += colliding_face->normal * face_collision_stepout;

						vec3d reflection_vec = reflect(entity->velocity, colliding_face->normal);
						entity->velocity = reflection_vec;
						entity->velocity *= 0.95;
					}
					*/

					colliding_face->draw(color::orange);
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



	vec3d epos;



	


	void primary_timer_func_COLLISION_RESPONSE_TEST()
	{
		//primary_camera.update();
		al_clear_depth_buffer(1000);
		al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
		primary_camera.set_frustum_as_camera(display->display);


		primary_camera.entity_attached_to->position = vec3d(0, -2, 0);


		Entity *entity = new Entity();
		//entity->position = vec3d(0, 0.5, 0);
		entity->position = vec3d(0, 1, 0);
		entity->velocity = epos;
		entity->draw();

		
		CollisionMesh::Face *face = NULL;

		// THREE OPTIONS
		face = new CollisionMesh::Face(
										build_vertex(-1.264863, 0.202511, 2.206481, color::white, 0, 0),
										build_vertex(-1.264863, 0.202511, -0.807603, color::white, 0, 0),
										build_vertex(1.749222, -0.915373, -0.807603, color::white, 0, 0),
										0, 0, vec3d(0.347740, 0.937591, 0.000000));
		//face = new CollisionMesh::Face(
		//								build_vertex(1.753840, -0.196039, 3.314322, color::white, 0, 0),
		//								build_vertex(-1.994693, 0.194116, 0.974821, color::white, 0, 0),
		//								build_vertex(0.350646, -0.944980, -2.973031, color::white, 0, 0),
		//								0, 0, vec3d(0.200374, 0.966590, -0.159858));
		//face = new CollisionMesh::Face(
		//								build_vertex(-4, 0, 3, color::orange, 0, 0), 
		//								build_vertex(5, 0, 0, color::orange, 0, 0),
		//								build_vertex(-5, 0, -4, color::orange, 0, 0),
		//								0, 0, vec3d(0, 1, 0));

		face->draw();


		IsectData intersect_info = IsectData();
		if (face->intersect(Ray(entity->position, entity->velocity), intersect_info))
		{
			//intersect_info.t = 0.5;
			std::cout << intersect_info.t << std::endl;
			vec3d point_of_intersection = entity->position + intersect_info.t * entity->velocity;
			draw_crosshair(point_of_intersection, color::red, 0.4); // point of collision

			float STEPOUT = 0.001f;
			vec3d stepout_point = point_of_intersection + face->normal * STEPOUT;
			draw_crosshair(stepout_point, color::aqua, 0.4); // point of collision

			//float mag = entity->velocity.GetMagnitude();
			vec3d resultant_velocity_vector = reflect(entity->velocity, face->normal);
			draw_3d_line(stepout_point, stepout_point + resultant_velocity_vector.Normalized() * 2);

			//float mag = entity->velocity.GetMagnitude();
			vec3d projected_point = project(entity->position + entity->velocity, face->v0, face->normal);
				// returns a point in world coordinates /on the plane/ that is the projection of the point.
				// you should then take it and... uh... do a stepback (same as the collision point), then find the
				// difference between this and the stepback, (but you have to make sure that the tail (part after the collision)
				// is long enough for the projection to be correct), normalize it, set it to the magnitude of the
				// original velocity, and boom.

			vec3d projected_point_stepped_out = projected_point + face->normal * STEPOUT;

			draw_3d_line(stepout_point, projected_point_stepped_out, color::black);

			draw_crosshair(projected_point, color::darkcyan, 0.6);//stepout_point, resultant_velocity_vector, color::darkblue);
			//draw_3d_line(stepout_point, resultant_velocity_vector, color::darkblue);
		}


		if (face) delete face;



		//if (current_map) current_map->draw();
		//if (current_map) current_map->draw_triangles_and_normals();
		//update_new_triangle_thing();
		//if (current_map) current_map->draw_entities();
	}



	void primary_timer_func() override
	{
		// UPDATING THE VELOCITY/POSITION OF OBJECTS

		primary_camera.update();
		if (player_controlled_entity)
		{
			player_controlled_entity->update_player_controlls();
		}
		
		for (unsigned i=0; i<current_map->entity2s.size(); i++)
		{
			current_map->entity2s[i]->update();
		}

		// DRAWING THE SCENE


		// clear the depth buffer

		al_clear_depth_buffer(1000);
		al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
		primary_camera.set_frustum_as_camera(display->display);



		//if (this->player_controlled_entity) player_controlled_entity->position += player_controlled_entity->_dirty_velocity_normal;



		// draw the map

		//

		// if the player step-collision collides with an entity

		update_new_triangle_thing();



		if (current_map) current_map->draw();
		//if (current_map) current_map->draw_triangles_and_normals();
		if (current_map)
		{
			current_map->draw_entities();
		}
		if (current_map)
		{
			for (unsigned i=0; i<current_map->entity2s.size(); i++)
			{
				//current_map->entity2s[i]->place.start_transform();
				//current_map->entity2s[i]->bbox.draw();
				//current_map->entity2s[i]->place.restore_transform();


				if (current_map->entity2s[i]->collides(player_controlled_entity->position))
				{
					if (i != 0) current_map->entity2s[i]->on_collide();
					//std::cout << "collide" << std::endl;
				}

				/*
				.collides(player_controlled_entity->position))
					std::cout << "(" << i << "collides!!)" << std::endl;
				if (current_map->entity2s[i]->bbox.collides(player_controlled_entity->position))
					std::cout << "(" << i << "collides!!)" << std::endl;
					*/
			}
		}

		
		//if (player_controlled_entity)
		//	draw_crosshair(vec3d(player_controlled_entity->position.x, 0, player_controlled_entity->position.z));
	}
	void key_up_func()
	{
		if (player_controlled_entity)
		{
			switch(af::current_event->keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
				player_controlled_entity->move_forward(false);
				break;
			case ALLEGRO_KEY_A:
				player_controlled_entity->strafe_left(false);
				break;
			case ALLEGRO_KEY_S:
				player_controlled_entity->move_backward(false);
				break;
			case ALLEGRO_KEY_D:
				player_controlled_entity->strafe_right(false);
				break;
			}
		}
	}
	void key_down_func()
	{
		if (player_controlled_entity)
		{
			// do the player_controlled_entity controls
			switch(af::current_event->keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
				player_controlled_entity->move_forward();
				break;
			case ALLEGRO_KEY_A:
				player_controlled_entity->strafe_left();
				break;
			case ALLEGRO_KEY_S:
				player_controlled_entity->move_backward();
				break;
			case ALLEGRO_KEY_D:
				player_controlled_entity->strafe_right();
				break;
			case ALLEGRO_KEY_UP:
				if (primary_camera.entity_attached_to)
					primary_camera.entity_attached_to->position.y += 1;
				break;
			case ALLEGRO_KEY_DOWN:
				if (primary_camera.entity_attached_to)
					primary_camera.entity_attached_to->position.y -= 1;
				break;
			case ALLEGRO_KEY_LEFT:
				if (primary_camera.entity_attached_to)
					primary_camera.entity_attached_to->position += primary_camera.entity_attached_to->get_strafe_vector() * 1;
				break;
			case ALLEGRO_KEY_RIGHT:
				if (primary_camera.entity_attached_to)
					primary_camera.entity_attached_to->position -= primary_camera.entity_attached_to->get_strafe_vector() * 1;
				break;
			default:
				break;
			}
		}

		// do the standard keyboard controls
		switch(af::current_event->keyboard.keycode)
		{
		case ALLEGRO_KEY_SPACE:
			if (!player_controlled_entity) return;
				player_controlled_entity->activate_skill("jump");
			// this is just for now, and just for testing
			//{
			//std::cout << "1";
			if (!current_map) break;

			

			//for (unsigned i=0; i<current_map->entities.size(); i++)
			//{
			//	if (primary_camera.entity_attached_to 
			//}
			//std::cout << "2";
			// toggle between a camera-owned entity, to the camera attached to an entity
			/*
			if (primary_camera.entity_attached_to == NULL
				|| primary_camera.entity_attached_to == current_map->entities[0])
			{
				primary_camera.entity_attached_to = new Entity();
				std::cout << "3";
			}
			else if (primary_camera.entity_attached_to && !current_map->entities.empty())
			{
				delete primary_camera.entity_attached_to;
				primary_camera.entity_attached_to = current_map->entities[0];
				std::cout << "4";
			}
			*/
			//std::cout << "5";
			break;
		default:
			break;
		}
	}
	void joy_axis_func() override
	{
		if (!player_controlled_entity) return;

		if (af::current_event->joystick.stick == 0)
		{
			if (af::current_event->joystick.axis == 0)
			{
				//player_controlled_entity->_dirty_velocity_normal.x = af::current_event->joystick.pos * 0.05;
				//player_controlled_entity->add_force(vec3d(af::current_event->joystick.pos * 0.05, 0, 0));
				//player_controlled_entity->strafe_right(false);
				//player_controlled_entity->strafe_left(false);

				//if (af::current_event->joystick.pos)
				player_controlled_entity->turning(-af::current_event->joystick.pos * 0.05);

				epos.x = af::current_event->joystick.pos * 3;
			}
			if (af::current_event->joystick.axis == 1)
			{
				//player_controlled_entity->_dirty_velocity_normal.z = -af::current_event->joystick.pos * 0.05;
				//player_controlled_entity->add_force(vec3d(0, 0, af::current_event->joystick.pos * 0.05));
				player_controlled_entity->move_forward(false);
				player_controlled_entity->move_backward(false);

				if (af::current_event->joystick.pos > 0) player_controlled_entity->move_backward();
				if (af::current_event->joystick.pos < 0) player_controlled_entity->move_forward();

				epos.y = -af::current_event->joystick.pos * 3;

			}
		}
		else if (af::current_event->joystick.stick == 1)
		{
			if (af::current_event->joystick.axis == 0)
			{
				// strafeing goes here, too
			}
			if (af::current_event->joystick.axis == 1)
			{
				if (primary_camera.entity_attached_to)
				{
					//primary_camera.pitch = -af::current_event->joystick.pos * 1.0;
					//primary_camera.pitch = limit<float>(-TAU/4, TAU/4, primary_camera.pitch);

					epos.z = -af::current_event->joystick.pos * 3;
				}
			}
		}
	}

	void respawn()
	{
		if (!player_controlled_entity) return;
		player_controlled_entity->position = vec3d(0, 6, 0);
	}

	void joy_down_func() override
	{
		if (!player_controlled_entity) return;

		std::cout << "BUTTON" << af::current_event->joystick.button << std::endl;

		switch(af::current_event->joystick.button)
		{
		case 0:
			player_controlled_entity->activate_skill("jump");
			break;
		case 1:
			break;
		case 3:
			respawn();
			break;
		case 4:
			player_controlled_entity->strafe_left();
			break;
		case 5:
			player_controlled_entity->strafe_right();
			break;
		default:
			break;
		}
	}

	void joy_up_func() override
	{
		if (!player_controlled_entity) return;


		switch(af::current_event->joystick.button)
		{
		case 4:
			player_controlled_entity->strafe_left(false);
			break;
		case 5:
			player_controlled_entity->strafe_right(false);
			break;
		default:
			break;
		}
	}
};
