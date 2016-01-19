

#include <allegro_flare/allegro_flare.h>
#include <allegro5/allegro_opengl.h>

#include <slug_3d/program_master.h>



int main(int argc, char *argv[])
{
	af::initialize();
	//Display *display = af::create_display(Display::FULLSCREEN_AUTO);
	//Display *display = af::create_display(1920/3*2, 1080/3*2, ALLEGRO_OPENGL);
	Display *display = af::create_display(1920, 1080, ALLEGRO_OPENGL);
	
	ProgramMaster *game_program_master = new ProgramMaster(display);

	af::run_loop();

	return 0;
}
