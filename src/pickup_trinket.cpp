


#include "pickup_trinket.h"



PickupTrinket::PickupTrinket(Map *map, Item::item_t type, vec3d location)
	: Item(map, type, location)
	, pickup_item_type(type)
{
	Entity2::entity2_type = Entity2::PICKUP_TRINKET;
	item_type = type;
}



void PickupTrinket::on_enter() {}
