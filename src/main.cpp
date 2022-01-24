

#include <allegro_flare/allegro_flare.h>
#include <allegro5/allegro_opengl.h>

#include <slug_3d/program_master.h>



int main(int argc, char *argv[])
{
   allegro_flare::Framework::initialize();
	//Display *display = af::create_display(Display::FULLSCREEN_AUTO);
	//Display *display = af::create_display(1920/3*2, 1080/3*2, ALLEGRO_OPENGL);
   allegro_flare::Display *display = allegro_flare::Framework::create_display(1920, 1080, ALLEGRO_OPENGL);
   std::cout << "-----------------2" << std::endl;
	
	ProgramMaster *game_program_master = new ProgramMaster(display);
   std::cout << "-----------------3" << std::endl;

   allegro_flare::Framework::run_loop();

	return 0;
}
