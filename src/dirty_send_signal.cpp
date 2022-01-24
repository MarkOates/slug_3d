#include <slug_3d/dirty_signal_send.h>




void dirty_send_signal(int signal, void *data)
{
	static allegro_flare::Screen *my_screen = new allegro_flare::Screen(NULL);
	my_screen->send_signal(signal, data);
};
