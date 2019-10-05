
#include <slug_3d/entity2.h>




//////////////////// Entity2





Entity2::Entity2(Map *map, entity2_t entity2_type, Model3D *model, std::string data)
	: map(map)
	, model(model)
	, place()
	, data(data)
	, entity2_type(entity2_type)
	, player_inside(false)
//	, entity_state()
{
	//model->get
	//bbox = model->get_bbox();
	bbox.min = model->get_min_vertex_coordinate();
	bbox.max = model->get_max_vertex_coordinate();
}



void Entity2::draw()
{
	if (!model) return;

	place.start_transform();
	//set_blender(blender);
	//model->draw(&textures, &colors);
	model->draw();
	//bbox.draw();
	//set_blender(BLENDER_NORMAL);
	place.restore_transform();
}



void Entity2::draw_triangles_and_normals()
{
	if (!model) return;

	place.start_transform();
	// TODO:
	//model->draw_triangles_and_normals();
	//bbox.draw();
	place.restore_transform();
}



void Entity2::update() {}



bool Entity2::collides(vec3d point)
{
	// collision does not take into account ROTATION or SCALE for now
	point -= vec3d(place.position.x, place.position.y, place.position.z);
	return bbox.collides(point);
}



bool Entity2::update_player_collision(vec3d player_location)
{
	bool collides_now = collides(player_location);

	if (collides_now && player_inside) { }
	else if (!collides_now && player_inside) on_leave();
	else if (collides_now && !player_inside) on_enter();
	else if (collides_now) on_collide();

	player_inside = collides_now;
	return collides_now;
}



void Entity2::on_enter()
{
	
}



void Entity2::on_leave()
{

}




void Entity2::on_collide()
{
	//std::cout << "collide";
}

