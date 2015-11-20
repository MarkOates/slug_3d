#ifndef __SH_DIRTY_SIGNAL_SEND_HEADER
#define __SH_DIRTY_SIGNAL_SEND_HEADER





#include <allegro_flare/allegro_flare.h>

//#include "allegro_flare.h"



enum signal_send_t
{
	SIGNAL_SET_DIALOGUE_TEXT = 0,
	SIGNAL_HIDE_DIALOGUE_TEXT,
	SIGNAL_SET_NOTIFICATION_TEXT
};


void dirty_send_signal(int signal, void *data);





#endif

