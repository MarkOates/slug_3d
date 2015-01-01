#ifndef __SH_ITEM_HEADER
#define __SH_ITEM_HEADER



#include <allegro_flare/bins/sample_bin.h>
#include <allegro_flare/model.h>
#include <allegro_flare/vec3d.h>


//#include "sample_bin.h"
//#include "model.h"
#include "aabb3d.h"
//#include "vec3d.h"
#include "map.h"


class Item : public Entity2
{
public:
	enum item_t
	{
		ITEM_TYPE_UNDEF,
		ITEM_TYPE_HEART,
		ITEM_TYPE_PAPER_CLIP,
		ITEM_TYPE_BOTTLE_CAP,
		ITEM_TYPE_LEAF,
		ITEM_TYPE_DOLL_HEAD,
		ITEM_TYPE_PIKCUP_TRINKET
	};

	SampleBin samples;
	std::string pickup_text;

	item_t item_type;
	float speed_diff;

public:
	Item(Map *map, item_t item_type, vec3d location);

	void update();

	void on_collide() override;
	void on_enter() override;
};




#endif