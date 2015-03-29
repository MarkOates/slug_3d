


#include "map_factory.h"
#include "item.h"
#include "door.h"


#include"info_pod.h"



static Entity2 *make_entity2(Map *map, std::string model, std::string texture0, vec3d position=vec3d(0,0,0), float rotation_y=0)
{
	Entity2 *e = new Entity2(map, Entity2::SCENERY, map->models[model], "");
	e->textures.set_texture_by_index(0, map->bitmaps[texture0]);
	map->entity2s.push_back(e);
	e->place.position = position;
	e->place.rotation = vec3d(0, rotation_y, 0);
	return e;
}



Map *MapFactory::construct()
{
	Map *current_map = new Map();
	Entity2 *e = NULL;
	current_map->name = "Construct";


	current_map->models["ground_quad-01.obj"]->scale(300, 300, 300);
	current_map->collision_mesh = new CollisionMesh(current_map->models["ground_quad-01.obj"]); // :) yay for collision mesh!! :D :D :D 




	Entity2 *instance = new Entity2(current_map, Entity2::SCENERY, current_map->models["ground_quad-01.obj"], "");
	instance->textures.set_texture_by_index(0, current_map->bitmaps["twon_texture.png"]);
	current_map->entity2s.push_back(instance);




	/*
	//make_entity2(current_map, "sign-01.obj", "hospital_sign.png", 0, 0);


	make_entity2(current_map, "sign-01.obj", "hospital_sign.png", vec3d(5, 0, -20), 0.65);

	// gas sign
	make_entity2(current_map, "sign-01.obj", "hospital_sign.png", vec3d(20, 0, -60), 0.5);

	// school sign
	make_entity2(current_map, "sign-01.obj", "hospital_sign.png", vec3d(68, 0, -30), 0.5);

	// shopping mall sign
	make_entity2(current_map, "sign-01.obj", "hospital_sign.png", vec3d(95, 0, 95), 0);



	*/


	// sweet ride
	make_entity2(current_map, "car-01.obj", "car_texture.png", vec3d(-106, 0, 81), 0.31);






	// coin
	/*
	for (unsigned i=0; i<20; i++)
	{
		e = make_entity2(current_map, "unit_coin-01.obj", "super_coin1.png", vec3d(10+random_float(-5, 5), 0.5, 10+random_float(-5, 5)), random_float(-5, 5));
		e->place.scale = vec3d(0.6, 0.6, 0.6);
		e->entity2_type = Entity2::ITEM;
	}
	*/




	// info pod :)

	InfoPod *info_pod = new InfoPod(current_map, vec3d(10, 0, -10), "Hey Guys!/This info pod will display/information about the game.");
	current_map->entity2s.push_back(info_pod);
		//e = make_entity2(current_map, "info_pod-03.obj", "infoppod3.jpg", vec3d(10, 0, -10), 0);
		//e->place.scale = vec3d(0.6, 0.6, 0.6);
		//e->entity2_type = Entity2::INFO_POD;
		//((InfoPod*)e)->set_message("Hey Guys!/This info pod will display/information about the game.");




	e = make_entity2(current_map, "forward_aarow-02.obj", "pointer_texture.png", vec3d(0, 0, 0), 0);
	




	// shopping mall sign
	e = make_entity2(current_map, "sign-01.obj", "hospital_sign.png", vec3d(0, 0, -3), 0);
	e->place.rotation.y = 0.25;






	// just a unit cube

	float scale = 1.0;
	current_map->models["unit_cube-01.obj"]->scale(scale, scale, scale);

	unsigned x=0, y=0, z=0;

	//for (unsigned z=0; z<10; z++)
		for (x=1; x<10; x++)
		{
			e = make_entity2(current_map, "unit_cube-01.obj", "unit_cube-01b.png", vec3d(x*scale*2, 0, z*scale*2), 0);
			e->place.rotation.y = random_float(0, TAU);
		}

		x = 0;
		for (z=1; z<10; z++)
		{
			e = make_entity2(current_map, "unit_cube-01.obj", "unit_cube-01b.png", vec3d(x*scale*2, 0, z*scale*2), 0);
			e->place.rotation.y = random_float(0, TAU);
		}








	//entity2->



	return current_map;
}




Map *MapFactory::small_room_map()
{
	Model *model = NULL;
	Entity2 *entity2 = NULL;
	Item *item = NULL;
	Door *door = NULL;
	Map *current_map = new Map();
	current_map->name = "Small Room";


	/*

	Entity *entity = new Entity();
		entity->position = vec3d(0, 10, 0);
		entity->velocity = vec3d(0, 0, 0);
	current_map->entities.push_back(entity);

	*/




	// add a collision mesh

	current_map->collision_mesh = new CollisionMesh(current_map->models["yup.obj"]);




	// add an object to the map (in this case it's the same model as the collision_mesh)

	model = current_map->models["yup.obj"];
		//model->set_texture_by_name("ground_Plane.001", current_map->bitmaps["Grass_texture_sketchup_warehouse_type069_0.jpg"]);
		//model->set_texture_by_name("ramp_Plane", current_map->bitmaps["playground-04.obj"]);
		model->set_texture_by_name("Plane", current_map->bitmaps["now_with_stone_thing-01.png"]);
	current_map->entity2s.push_back(new Entity2(current_map, Entity2::WORLD, model, ""));




	item = new Item(current_map, Item::ITEM_TYPE_HEART, vec3d(2, 1, -5));
	current_map->entity2s.push_back(item);

	item = new Item(current_map, Item::ITEM_TYPE_HEART, vec3d(4, 1, -5));
	current_map->entity2s.push_back(item);

	item = new Item(current_map, Item::ITEM_TYPE_HEART, vec3d(6, 1, -5));
	current_map->entity2s.push_back(item);




	// add another object (this should probably be an entity instead)

	Entity2 *instance = new Entity2(current_map, Entity2::FORCE_FIELD, current_map->models["force_field_thing-02.obj"], "");
		instance->place.position.x = -18;
		instance->place.position.y = 0;
		instance->place.position.z = 3;
		instance->blender = BLENDER_ADDITIVE;
		instance->textures.set_texture_by_index(0, current_map->bitmaps["cool_yea_fan_sure.png"]);
		instance->textures.set_texture_by_index(1, current_map->bitmaps["cool_yea_fan_sure.png"]);
	current_map->entity2s.push_back(instance);




	// add doors

	door = new Door(current_map, Door::DOOR_LARGE, "door_to_" + current_map->name, vec3d(8, 0, 0), 0, "door_from_" + current_map->name);
	current_map->entity2s.push_back(door);


	//doorframe-01.obj




	return current_map;
}






Map *MapFactory::climber_map()
{
	Model *model = NULL;
	Door *door = NULL;
	Entity2 *entity2 = NULL;
	Map *current_map = new Map();
	current_map->name = "climber_map";

	current_map->clear_color = color::hex("782f6c");

	current_map->collision_mesh = new CollisionMesh(current_map->models["level-03.obj"]);

	model = current_map->models["level-03.obj"];
		model->set_texture_by_name("Plane", current_map->bitmaps["new_tex.jpg"]);
	current_map->entity2s.push_back(new Entity2(current_map, Entity2::WORLD, model, ""));
	


	Entity2 *instance = new Entity2(current_map, Entity2::FORCE_FIELD, current_map->models["force_field_thing-02.obj"], "");
		instance->place.position.x = -18;
		instance->place.position.y = 0; 
		instance->place.position.z = 3;
		instance->textures.set_texture_by_index(0, current_map->bitmaps["cool_yea_fan_sure.png"]);
		instance->textures.set_texture_by_index(1, current_map->bitmaps["cool_yea_fan_sure.png"]);
	current_map->entity2s.push_back(instance);



	// add doors

	door = new Door(current_map, Door::DOOR_LARGE, "door_to_" + current_map->name, vec3d(8, 0, -2), 0, "door_from_" + current_map->name);
	current_map->entity2s.push_back(door);

	return current_map;
}



#include "pickup_trinket.h"


Map *MapFactory::customize_character_room()
{
	InfoPod *info_pod = NULL;
	Item *item = NULL;
	Entity2 *entity2 = NULL;
	PickupTrinket *pickup_trinket = NULL;

	

	Map *current_map = create_a_map_from_model_with_cherries_in_it("Customize Your Character", color::firebrick, "customize_room-01c.obj", "quarter.png", "10x10_plane_tx-04.png");
		current_map->collision_mesh->model->set_texture_by_name("walls_Plane.004", current_map->bitmaps["bark.jpg"]);
		current_map->collision_mesh->model->set_texture_by_name("ground_Plane", current_map->bitmaps["scaly.jpg"]);

	//model = current_map->models["magick_world-04.obj"];
		entity2 = current_map->entity2s[0];//new Entity2(current_map, Entity2::WORLD, current_map->collision_mesh->model, "");
		entity2->colors.set_color(0, color::midnightblue);
		entity2->colors.set_color(1, color::aliceblue);
		//current_map->collision_mesh->model->set_color(0, color::midnightblue);
		//current_map->collision_mesh->model->set_color();


		current_map->clear_color = color::yellow;

		/*
	for (unsigned i=0; i<30; i++)
	{
		vec3d random_placement = vec3d(random_float(-40, 50), -1, random_float(-100, 0));
		current_map->entity2s.push_back(new AntEnemy(current_map, random_placement, vec3d(50, -1, 0), vec3d(-40, -1, -100)));
	}
	*/






	info_pod = new InfoPod(current_map, vec3d(12, 0, -0.5), "Spice Things Up/Here's where you keep all your fancy/trinkets that you've collected on your/quest.  Step into one to put it on!/");
	current_map->entity2s.push_back(info_pod);



	/*
	item = new Item(current_map, Item::ITEM_TYPE_BOTTLE_CAP, vec3d(65, -1, -60));
	current_map->entity2s.push_back(item);



	item = new Item(current_map, Item::ITEM_TYPE_DOLL_HEAD, vec3d(-40, -1, -82));
	current_map->entity2s.push_back(item);
	*/


	
	return current_map;
}





//"first_chaser", color::firebrick, "first_chaser-03.obj", "quarter.png", ""
Map *MapFactory::create_a_map_from_model_with_cherries_in_it(std::string map_name, ALLEGRO_COLOR bg_color, std::string model_identifier, std::string texture, std::string items_model_identifier)
{
	Model *model = NULL;
	Door *door = NULL;
	Entity2 *entity2 = NULL;
	Map *current_map = new Map();
	current_map->name = map_name;


	current_map->clear_color = bg_color;

	current_map->collision_mesh = new CollisionMesh(current_map->models[model_identifier]);

	model = current_map->models[model_identifier];
	//model->set_texture_by_name("Plane.001", current_map->bitmaps[texture]);
	model->textures.set_texture_by_index(0, current_map->bitmaps[texture]); //("Plane.001", 
	current_map->entity2s.push_back(new Entity2(current_map, Entity2::WORLD, model, ""));



	if (!items_model_identifier.empty() && current_map->models[items_model_identifier])
	{
		Map *map_to_add_items_to = current_map;
		Model *model_to_parse_for_items = current_map->models[items_model_identifier];

		// process the map
		std::cout << "size(start):" << model_to_parse_for_items->objects.size() << std::endl;
		for (unsigned i=0; i<model_to_parse_for_items->objects.size(); i++)
		{
			if (model_to_parse_for_items->objects[i].name.substr(0,strlen("cherry")) == "cherry")
			{
				vec3d centroid = model_to_parse_for_items->objects[i].get_centroid();
				std::cout << "   " << "cherry" << " found at " << centroid.ToString() << std::endl;

				Item *item = new Item(map_to_add_items_to, Item::ITEM_TYPE_HEART, centroid);
				map_to_add_items_to->register_entity2(item);
			
				//if (map_model->remove_object(i)) i--;
			}
		}
		std::cout << "size(end):" << model_to_parse_for_items->objects.size() << std::endl;

		std::cout << "...map post-processing complete." << std::endl;
	}





	door = new Door(current_map, Door::DOOR_LARGE, "door_to_" + tostring(map_name), vec3d(0, 0, 0), 0, "door_from_" + tostring(map_name));
	current_map->entity2s.push_back(door);

	return current_map;
}



Map *MapFactory::sandbox_map()
{
	InfoPod *info_pod = NULL;
	Item *item = NULL;

	Map *current_map = create_a_map_from_model_with_cherries_in_it("Sand Box", color::firebrick, "sandbox-04.obj", "quarter.png", "10x10_plane_tx-04.png");
		current_map->collision_mesh->model->set_texture_by_name("floor_Plane.002", current_map->bitmaps["sand-01.jpg"]);
		current_map->collision_mesh->model->set_texture_by_name("platform_Plane.001", current_map->bitmaps["scaly.jpg"]);
		current_map->collision_mesh->model->set_texture_by_name("walls_Plane", current_map->bitmaps["bark.jpg"]);
	


	for (unsigned i=0; i<30; i++)
	{
		vec3d random_placement = vec3d(random_float(-40, 50), -1, random_float(-100, 0));
		current_map->entity2s.push_back(new AntEnemy(current_map, random_placement, vec3d(50, -1, 0), vec3d(-40, -1, -100)));
	}




	info_pod = new InfoPod(current_map, vec3d(12, 0, -5), "Bump and Grind/Welcome to the Sand Box.  As you can/see, there are plenty of bugs just/running around like mad.  This is a/great place to develop your experience.");
	current_map->entity2s.push_back(info_pod);




	item = new Item(current_map, Item::ITEM_TYPE_BOTTLE_CAP, vec3d(65, -1, -60));
	current_map->entity2s.push_back(item);



	item = new Item(current_map, Item::ITEM_TYPE_DOLL_HEAD, vec3d(-40, -1, -82));
	current_map->entity2s.push_back(item);



	
	return current_map;
}



Map *MapFactory::bouncy_trouncy()
{
	Map *map = create_a_map_from_model_with_cherries_in_it("Bouncy Trouncy", color::firebrick, "bouncy_trouncy-06t.obj", "quarter.png", "10x10_plane_tx-04.jpg");

	map->clear_color = color::darkgreen;

	map->collision_mesh->model->textures.set_texture_by_index(0, map->bitmaps["bark.jpg"]);
	map->collision_mesh->model->textures.set_texture_by_index(1, map->bitmaps["bark.jpg"]);
	map->collision_mesh->model->textures.set_texture_by_index(2, map->bitmaps["water2.png"]);
	map->collision_mesh->model->textures.set_texture_by_index(3, map->bitmaps["water2.png"]);
	map->collision_mesh->model->textures.set_texture_by_index(4, map->bitmaps["water2.png"]);
	map->collision_mesh->model->textures.set_texture_by_index(5, map->bitmaps["grass128.jpg"]);




	InfoPod *info_pod = new InfoPod(map, vec3d(-10, 0, -16), "Bouncy Stuff/Be sure to jump on the blue bouncy/parts, they sure can take you places!/");
	map->entity2s.push_back(info_pod);




	map->entity2s.push_back(new AntEnemy(map, vec3d(-15, 0, -18), vec3d(-15, 0, -18), vec3d(-23, 0, 0)));
	map->entity2s.push_back(new AntEnemy(map, vec3d(-15, 0, -18), vec3d(-15, 0, -18), vec3d(-23, 0, 0)));



	for (unsigned i=0; i<15; i++)
	{
		AntEnemy *ant_enemy = new AntEnemy(map, vec3d(2, 8, 9), vec3d(-52, 8, 38), vec3d(2, 8, 9));
		ant_enemy->make_white();
		map->entity2s.push_back(ant_enemy);
	}



	map->entity2s.push_back(new AntEnemy(map, vec3d(-17, 19, 16), vec3d(-17, 19, 16), vec3d(-23, 19, 21)));
	map->entity2s.push_back(new AntEnemy(map, vec3d(-17, 19, 16), vec3d(-17, 19, 16), vec3d(-23, 19, 21)));



	//map->entity2s.push_back(new AntEnemy(map, vec3d(-17, 19, 16), vec3d(-17, 19, 16), vec3d(-23, 19, 21)));



	info_pod = new InfoPod(map, vec3d(-67, 15.5, 7.7), "Go for it/Big jump ahead, enjoy the ride!/");
	map->entity2s.push_back(info_pod);




	for (unsigned i=0; i<15; i++)
	{
		AntEnemy *ant_enemy = new AntEnemy(map, vec3d(-111.5, 99.37, -45), vec3d(-111.5, 99.37, -45), vec3d(-60, 99.37, -34));
		ant_enemy->make_white();
		map->entity2s.push_back(ant_enemy);
	}




	return map;
}

#include "info_pod.h"

Map *MapFactory::water_room()
{
	Map *map = create_a_map_from_model_with_cherries_in_it("Water Room", color::blue, "water_room-03e.obj", "water2.png", "");
	InfoPod *info_pod = NULL;

	map->collision_mesh->model->textures.set_texture_by_index(1, map->bitmaps["water2.png"]);
	map->collision_mesh->model->textures.set_texture_by_index(2, map->bitmaps["water_room-05.jpg"]);
	map->collision_mesh->model->textures.set_texture_by_index(3, map->bitmaps["Grass_texture_sketchup_warehouse_type069_0.jpg"]);

	//model = current_map->models["level_select_worl-02.obj"];
	//	model->set_texture_by_name("Plane.000", current_map->bitmaps["trees.png"]);
	//	model->set_texture_by_name("Plane.001_Plane.002", current_map->bitmaps["Grass_texture_sketchup_warehouse_type069_0.jpg"]);
	//current_map->entity2s.push_back(new Entity2(current_map, Entity2::WORLD, model, ""));



	info_pod = new InfoPod(map, vec3d(-13, 0, -11), "Water Room/Aahhhhhh, there's nothing nicer/than taking a nice cool dip in/the water to replenish your hydration./");
	map->entity2s.push_back(info_pod);




	return map;
}




#include "info_pod.h"




Map *MapFactory::first_world_hiding_under_a_leaf()
{
	Model *model = NULL;
	Door *door = NULL;
	Entity2 *entity2 = NULL;
	InfoPod *info_pod = NULL;
	Map *current_map = new Map();
	current_map->name = "Hiding Under a Leaf";
	


	current_map->clear_color = color::hex("193d41");

	current_map->collision_mesh = new CollisionMesh(current_map->models["magick_world-04.obj"]);
	
	model = current_map->models["magick_world-04.obj"];
		model->set_texture_by_name("walls_Plane.001", current_map->bitmaps["trees.png"]);
		model->set_texture_by_name("Plane_Plane.003", current_map->bitmaps["grass128.jpg"]);
		model->set_texture_by_name("elevated_Plane.002", current_map->bitmaps["grass128.jpg"]);
		model->set_texture_by_name("water_Plane.004", current_map->bitmaps["water2.png"]);
		
//		model->set_texture_by_name("Plane.001_Plane.002", current_map->bitmaps["Grass_texture_sketchup_warehouse_type069_0.jpg"]);
		entity2 = new Entity2(current_map, Entity2::WORLD, model, "");
		entity2->colors.set_color(3, color::green);
		entity2->colors.set_color(2, color::burlywood);
		current_map->entity2s.push_back(entity2);



	// add an enemy

	current_map->entity2s.push_back(new AntEnemy(current_map, vec3d(-28, 0.9, -84), vec3d(-28, 0, -84), vec3d(-5, 0, -60)));



	// add an info pod

	info_pod = new InfoPod(current_map, vec3d(-7, 0, -15), "Welcome to a slug's life/This is your first message via/an InfoPod.  Stand on these/throughout the game and you can/gain valuable information for your quest/");
	current_map->entity2s.push_back(info_pod);



	//

	info_pod = new InfoPod(current_map, vec3d(-11, 0, -51.5), "Jumping and Attacking/You can jump with either the spacebar/or one of the three buttons on your/joystick.  You'll need to jump to get from/place to place.");
	current_map->entity2s.push_back(info_pod);





	// add an item

	current_map->entity2s.push_back(new Item(current_map, Item::ITEM_TYPE_PAPER_CLIP, vec3d(13, 0.65, -44)));

	info_pod = new InfoPod(current_map, vec3d(16, 0.65, -37), "Accessories/You may have lost your shell,/but things aren't all that bad./In fact, if you look around a bit/on your quest, you might find some/other things you could put on instead.");
	current_map->entity2s.push_back(info_pod);




	// add the door out

	door = new Door(current_map, Door::DOOR_CAVE, "door_to_Select a Level", vec3d(-20, 0.9, -87), 0, "door_from_Select a Level");
	current_map->entity2s.push_back(door);

	//home_door = door;




	return current_map;

}




Map *MapFactory::terrain_map(std::vector<Map *> other_maps_to_make_doors_to)
{
	Model *model = NULL;
	Door *door = NULL;
	Entity2 *entity2 = NULL;
	InfoPod *info_pod = NULL;
	Map *current_map = new Map();
	current_map->name = "Select a Level";



	current_map->clear_color = color::hex("012600");



	// add a collision mesh

	current_map->collision_mesh = new CollisionMesh(current_map->models["level_select_worl-02.obj"]);





	// add an object to the map (in this case it's the same model as the collision_mesh)

	model = current_map->models["level_select_worl-02.obj"];
		model->set_texture_by_name("Plane.000", current_map->bitmaps["trees.png"]);
		model->set_texture_by_name("Plane.001_Plane.002", current_map->bitmaps["grass128.jpg"]);
	current_map->entity2s.push_back(new Entity2(current_map, Entity2::WORLD, model, ""));





	// add another object (this should probably be an entity instead)

	/*
	Entity2 *instance = new Entity2(current_map, Entity2::FORCE_FIELD, current_map->models["force_field_thing-02.obj"], "");
		instance->place.x = -18;
		instance->place.y = 0; 
		instance->place.z = 3;
		instance->textures.set_texture(0, current_map->bitmaps["cool_yea_fan_sure.png"]);
		instance->textures.set_texture(1, current_map->bitmaps["cool_yea_fan_sure.png"]);
	current_map->entity2s.push_back(instance);
	*/


	/*

	instance = new Entity2(current_map, Entity2::FORCE_FIELD, current_map->models["hero-06.obj"], "");
		instance->place.x = 0;
		instance->place.y = 0; 
		instance->place.z = 0;
		instance->textures.set_texture(0, current_map->bitmaps["scaly.jpg"]);
		//instance->textures.set_texture(1, current_map->bitmaps["scaly.jpg"]);
	current_map->entity2s.push_back(instance);

	*/




	// add some enemies

	current_map->entity2s.push_back(new AntEnemy(current_map, vec3d(0, 0, 0), vec3d(-20, 0, -16), vec3d(0, 0, 16)));
	current_map->entity2s.push_back(new AntEnemy(current_map, vec3d(0, 0, 0), vec3d(-20, 0, -16), vec3d(0, 0, 16)));





	
	// add the info pod

	info_pod = new InfoPod(current_map, vec3d(-5, 0, 5), "Pick Your Destination/From here, you can travel to any level/in the game.  Simply step through the door/and off you go.  And don't worry, you/can always come right back from/where you came.");
	current_map->entity2s.push_back(info_pod);





	// this one is just to select a level...

	door = new Door(current_map, Door::DOOR_CAVE, "door_from_Select a Level", vec3d(-12, 0, -7), 0, "door_to_Select a Level");
	current_map->entity2s.push_back(door);


	


	// add doors

	/*
	door = new Door(current_map, Door::DOOR_LARGE, "door_from_cilmber_map", vec3d(20, 0, 2), 0, "door_to_cilmber_map");
	current_map->entity2s.push_back(door);

	door = new Door(current_map, Door::DOOR_LARGE, "door_from_small_room_map", vec3d(-13, 0, 2), 0, "door_to_small_room_map");
	current_map->entity2s.push_back(door);

	door = new Door(current_map, Door::DOOR_LARGE, "door_from_small_room_map", vec3d(-13, 0, 2), 0, "door_to_small_room_map");
	current_map->entity2s.push_back(door);
	*/


	vec3d door_start_x(-27, 0, 16);
	vec3d door_distance(7, 0, 0);

	for (unsigned i=0; i<other_maps_to_make_doors_to.size(); i++)
	{
		if (other_maps_to_make_doors_to[i] == current_map) continue;

		door = new Door(current_map, Door::DOOR_LARGE, "door_from_" + other_maps_to_make_doors_to[i]->name, door_start_x + door_distance*i, 0, "door_to_" + other_maps_to_make_doors_to[i]->name);
		current_map->entity2s.push_back(door);
	}





	return current_map;
}

