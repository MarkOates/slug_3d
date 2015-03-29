#ifndef __SH_PICKUP
#define __SH_PICKUP





#include <slug_3d/item.h>
#include <slug_3d/player_character.h>


class PickupTrinket : public Item
{
public:
	Item::item_t pickup_item_type;
	PickupTrinket(Map *map, Item::item_t type, vec3d location);
	void on_enter() override;
};




#endif