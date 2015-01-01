

#include "item.h"



Item::Item(Map *map, item_t item_type, vec3d location)
	: Entity2(map, Entity2::ITEM, map->models["just_a_textured_quad-01.obj"])
	, item_type(item_type)
	, pickup_text("")
	//, blend(BLENDER_NORMAL)
{
//	this->bbox._position = location;

	this->place.position.x = location.x;
	this->place.position.y = location.y;
	this->place.position.z = location.z;

	this->place.scale.x = 0.5;
	this->place.scale.y = 0.5;
	this->place.scale.z = 0.5;

	bbox.min = vec3d(-1, -1, -1);
	bbox.max = vec3d(1, 1, 1);

	/*
	set_message_text("You Found a Paper Clip!", "What magical powers might you wield", "with this lucky find?  ", "Nothing, nothing at all!  In fact,", "the only thing you can do with it", "is put it on your character.");
	set_message_text("You Found a Bottle Cap!", "Wow! What an achievement!  A bottle", "cap sure would look nice instead", "of your shell.  Ok, maybe not.", "But you can always use your", "imagination...");
	set_message_text("You Found a Leaf!", "Hey, not bad!  A leaf sure would", "add some color that your shell couldn't.");
	set_message_text("You Found a Barbie Doll Head!", "Sweet.  Now that's a classy accessory!", "That's the kind of fancy trinket", "you might wear to a mollusc party.");
	set_message_text("You Found a Lost Diamond Ring!", "Holy Cow!  I'm sure there's an upset", "lady somewhere who lost this.", "It's by far the most expensive", "thing you could wear!");
	*/


	if (item_type == ITEM_TYPE_HEART)
	{
		model = map->models["heart_item-01.obj"];
		textures.set_texture_by_index(0, map->bitmaps["heart_item-01tx.png"]);
		//speed_diff = random_float(0.9, 1.1);
		//blender = blender_t::BLENDER_ADDITIVE;
		data = "heart_item-01tx.png";
	}
	if (item_type == ITEM_TYPE_PAPER_CLIP)
	{
		data = "paper_clip.png";
		textures.set_texture_by_index(0, map->bitmaps["paper_clip.png"]);
		//speed_diff = random_float(0.9, 1.1);
		//bbox.min = vec3d(-1.0, -1.0, -1.0);
		//bbox.max = vec3d(1.0, 1.0, 1.0);
		//blender = blender_t::BLENDER_ADDITIVE;
		pickup_text = "You Found a Paper Clip!/What magical powers might you wield/with this lucky find? Well, nothing/magical.  But you can put it on in the/Water Room to change your look.";
	}
	if (item_type == ITEM_TYPE_DOLL_HEAD)
	{
		data = "doll_head32.png";
		textures.set_texture_by_index(0, map->bitmaps["doll_head32.png"]);
		pickup_text = "You Found a Doll Head/Sweet.  Now that's a classy accessory!/That's the kind of fancy trinket you/might wear to a mollusc party.";
	}
	if (item_type == ITEM_TYPE_BOTTLE_CAP)
	{
		data = "bottle_cap.png";
		textures.set_texture_by_index(0, map->bitmaps["bottle_cap.png"]);
		pickup_text = "You Found a Bottle Cap/Wow! What an achievement!  A bottle/cap sure would look nice instead/of your shell.  Ok, maybe not.  But you/can always use your imagination...";
	}
}

void Item::update()
{
	this->place.rotation.y += 0.005;
	//this->place.
}

void Item::on_collide()
{
	//SoundPlayer::play("pickup_shing.ogg");
	//std::cout << "collide";
}

#include "dirty_signal_send.h"

void Item::on_enter()
{
	std::string *str = new std::string(pickup_text);
	dirty_send_signal(SIGNAL_SET_DIALOGUE_TEXT, (void *)str);
	delete str;
}