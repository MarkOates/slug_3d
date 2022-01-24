#ifndef __SH_ITEM_HEADER
#define __SH_ITEM_HEADER



#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Vec3D.hpp>


//#include "sample_bin.h"
//#include "model.h"
#include <slug_3d/aabb3d.h>
//#include "vec3d.h"
#include <slug_3d/map.h>


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

   AllegroFlare::SampleBin samples;
	std::string pickup_text;

	item_t item_type;
	float speed_diff;

public:
	Item(Map *map, item_t item_type, AllegroFlare::vec3d location);

	void update() override;

	void on_collide() override;
	void on_enter() override;
};




#endif
