#include <slug_3d/dirty_signal_send.h>




void dirty_send_signal(int signal, void *data)
{
	static Screen *my_screen = new Screen(NULL);
	my_screen->send_signal(signal, data);
};