#ifndef __SH_INFO_STAND_HEADER
#define __SH_INFO_STAND_HEADER



#include <AllegroFlare/Useful.hpp>



#include <slug_3d/entity2.h>
//#include "useful.h"
#include <slug_3d/hud.h>


class InfoPod : public Entity2
{
public:
	std::string message;
	std::string title;
	std::string line[5];
	HUD *hud;

public:
	InfoPod(Map *map, AllegroFlare::vec3d location, std::string message); // left-slash delineates lines;
	void set_message(std::string message);

	void on_enter() override;
	void on_leave() override;
};




#endif
