

#include <allegro_flare/allegro_flare.h>

#include <allegro_flare/camera3d.h>
#include <allegro_flare/frustum.h>
#include <allegro_flare/placement3d.h>


//#include "allegro_flare.h"
//#include "vec3d.h"
//#include "useful.h"
//#include "model.h"
//#include "placement3d.h"
//#include "model_bin.h"
#include "aabb3d.h"
//#include "frustum.h"
#include "map.h"
#include "collisions.h"
#include "entity.h"
#include "item.h"
#include "door.h"
//#include "camera3d.h"
#include "player_character.h"
#include "my_game_maps.h"
#include "level.h"
#include "program_master.h"
#include "hud.h"
#include "menu.h"




int main(int argc, char *argv)
{
	af::initialize();
	//Display *display = af::create_display(Display::FULLSCREEN_AUTO);
	Display *display = af::create_display(1920/3*2, 1080/3*2);

	ProgramMaster *game_program_master = new ProgramMaster(display);

	af::run_loop();
}