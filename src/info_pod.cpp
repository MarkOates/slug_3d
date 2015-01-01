


#include "info_pod.h"
#include "map.h"




InfoPod::InfoPod(Map *map, vec3d location, std::string message) // left-slash delineates lines
	: Entity2(map, Entity2::INFO_POD, map->models["info_pod-03.obj"], "")
	, message(message)
	, line()
	, title()
{
	place.position.x = location.x;
	place.position.y = location.y;
	place.position.z = location.z;

	place.rotation.y = 0.5;

	set_message(message);
	textures.set_texture_by_index(0, map->bitmaps["infoppod3.jpg"]);
}



void InfoPod::set_message(std::string message)
{
	this->message = message;
	std::vector<std::string> lines = php::explode("/", message);
	if (!lines.empty()) title = lines[0];
	for (unsigned i=1; i<6; i++)
	{
		if (i >= lines.size()) line[i-1] = "";
		else line[i-1] = lines[i-1];
	}
}



/*
void InfoPod::test_player_collision(vec3d position)
{
	bool collides_now = collides(position);

	if (collides_now && player_inside) { }
	else if (!collides_now && player_inside) on_leave();
	else if (collides_now && !player_inside) on_enter();

	player_inside = collides_now;
}
*/


#include "dirty_signal_send.h"



void InfoPod::on_enter()
{
	std::cout << "pod_enter";

	std::string *str = new std::string(message);
	dirty_send_signal(SIGNAL_SET_DIALOGUE_TEXT, (void *)str);
	delete str;
}


void InfoPod::on_leave()
{
	std::cout << "pod_leave";
	dirty_send_signal(SIGNAL_HIDE_DIALOGUE_TEXT, NULL);
}
