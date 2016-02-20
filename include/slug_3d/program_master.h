#ifndef __SH_PROGRAM_MASTER_HEADER
#define __SH_PROGRAM_MASTER_HEADER




#include <allegro_flare/screen.h>
#include <allegro_flare/bins/bitmap_bin.h>
#include <allegro_flare/camera3d.h>
#include <allegro_flare/motion.h>

//#include "screen.h"
//#include "bitmap_bin.h"
//#include "camera3d.h"
#include <slug_3d/level.h>
#include <slug_3d/map.h>
#include <slug_3d/player_character.h>
//#include "motion_control.h"




//#include <flare_gui/flare_gui.h>



#include <slug_3d/gui_screen.h>



//extern Door *home_door;

class HUD;


class ProgramMaster : public Screen
{
protected:
	Motion motion;
	BitmapBin bitmaps;
	ModelBin models;

	void _update_new_triangle_thing();
	void _update_joystick_input_relative_to_camera();

   int warp_displacement_x;
   int warp_displacement_y;

public:
	Level level;
	Map *current_map;

	Camera3D primary_camera;
	PlayerCharacter player_character;

	float default_camera_pitch;

	bool use_show_mouse_as_cursor;

	HUD *hud;
	//FGUIScreen *gui_screen;

	Entity *player_controlled_entity; // could be the camera, another object, something...
									  // right now, it's just the this->player_character;


	int num_collision_steps;

	ProgramMaster(Display *display);

	void collision_response_func_CAR(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001);
	void collision_response_func_CRICKET(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001);
	void collision_response_func_BALL(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001);
	void collision_response_func_CAR_no_bounce(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001);
	void collision_response_func_ALONG(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001);
	void collision_response_func_CONTINUOUS(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001);
	void collision_response_func_ALONG_SLIPPY(Entity *entity, float time_to_collision, CollisionMesh::Face *face, float face_collision_stepout=0.0001);

	



public:
	void start_map(Map *map);
	void respawn();
	bool enter_into_door(Door *door);
	void toggle_mouse_as_cursor();




	void primary_timer_func() override;
	void primary_timer_func_COLLISION_RESPONSE_TEST();

	void receive_signal(const std::string &signal, void *data) override;

	void mouse_axes_func() override;
	void mouse_warp_func() override;
	void mouse_down_func() override;
	void key_up_func() override;
	void key_down_func() override;
	void joy_axis_func() override;
	void joy_button_down_func() override;
	void joy_button_up_func() override;
};




#endif
