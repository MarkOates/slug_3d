#ifndef __SH_PROGRAM_MASTER_HEADER
#define __SH_PROGRAM_MASTER_HEADER




#include <allegro_flare/screen.h>
#include <allegro_flare/bins/bitmap_bin.h>
#include <allegro_flare/camera3d.h>
#include <allegro_flare/motion.h>

//#include "screen.h"
//#include "bitmap_bin.h"
//#include "camera3d.h"
#include "level.h"
#include "map.h"
#include "player_character.h"
//#include "motion_control.h"




//#include <flare_gui/flare_gui.h>



#include "gui_screen.h"



//extern Door *home_door;

class HUD;


class ProgramMaster : public Screen
{
public:
	Motion motion;
	BitmapBin bitmaps;
	ModelBin models;
	Camera3D primary_camera;
	float default_camera_pitch;

	bool use_show_mouse_as_cursor;

	//FGUIScreen *gui_screen;

	Level level;
	Map *current_map;

	HUD *hud;

	PlayerCharacter player_character;
	Entity *player_controlled_entity; // could be the camera, another object, something...


	int num_collision_steps;

	ProgramMaster(Display *display);




	void start_map(Map *map);

	bool enter_into_door(Door *door);


   inline bool basically_equal(const vec3d &first, const vec3d &other, float threshold=0.00001f) const;
   

	void collision_response_func_CAR(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001);

	void collision_response_func_CRICKET(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001);

	void collision_response_func_BALL(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001);

	void collision_response_func_CAR_no_bounce(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001);

	void collision_response_func_ALONG(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001);

	void collision_response_func_ALONG_SLIPPY(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001);

	

	void update_new_triangle_thing();



	//vec3d epos;


	void toggle_mouse_as_cursor();



	void _update_joystick_input_relative_to_camera();



	void primary_timer_func_COLLISION_RESPONSE_TEST();

	void receive_signal(const std::string &signal, void *data) override;

	void mouse_axes_func() override;
	void mouse_down_func() override;
	void primary_timer_func() override;
	void key_up_func();
	void key_down_func();
	void joy_axis_func() override;

	void respawn();

	void joy_down_func() override;

	void joy_up_func() override;
};




#endif