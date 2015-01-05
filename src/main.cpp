

#include <allegro_flare/allegro_flare.h>

#include <allegro_flare/camera3d.h>
#include <allegro_flare/frustum.h>
#include <allegro_flare/placement3d.h>


//#include "allegro_flare.h"
//#include "vec3d.h"
//#include "useful.h"
//#include "model.h"
//#include "placement3d.h"
//#include "model_bin.h"
#include "aabb3d.h"
//#include "frustum.h"
#include "map.h"
#include "collisions.h"
#include "entity.h"
#include "item.h"
#include "door.h"
//#include "camera3d.h"
#include "player_character.h"
#include "my_game_maps.h"
#include "level.h"
#include "program_master.h"
#include "hud.h"
#include "menu.h"






/*
class Model2;

Model2 make_cube(float size=1.0f);


class Model2
{
public:
	std::vector<ALLEGRO_VERTEX> vertices;
	std::vector<int> indices;
	placement3d place;

	Model2()
		: place()
		, vertices()
		, indices()
	{
	}

	void draw()
	{
		place.start_transform();
		if (!vertices.empty() && !indices.empty())
			al_draw_indexed_prim(&vertices[0], NULL, NULL, &indices[0], indices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
		place.restore_transform();
	}
};


Model2 make_cube(float size)
{
	Model2 model;
	model.vertices.resize(8);

	float hsize = size/2;

	model.vertices[0] = build_vertex(hsize, -hsize, -hsize, color::orange, 0, 0);
	model.vertices[1] = build_vertex(hsize, -hsize, hsize, color::orange, 0, 0);
	model.vertices[2] = build_vertex(-hsize, -hsize, hsize, color::orange, 0, 0);
	model.vertices[3] = build_vertex(-hsize, -hsize, -hsize, color::antiquewhite, 0, 0);
	model.vertices[4] = build_vertex(hsize, hsize, -hsize, color::lightgoldenrodyellow, 0, 0);
	model.vertices[5] = build_vertex(hsize, hsize, hsize, color::lightsteelblue, 0, 0);
	model.vertices[6] = build_vertex(-hsize, hsize, hsize, color::lightseagreen, 0, 0);
	model.vertices[7] = build_vertex(-hsize, hsize, -hsize, color::lightskyblue, 0, 0);

	int indices[] = { 1-1, 2-1, 3-1,
						1-1, 3-1, 4-1,
						5-1, 8-1, 7-1,
						5-1, 7-1, 6-1, // 12
						1-1, 5-1, 6-1,
						1-1, 6-1, 2-1,
						2-1, 6-1, 7-1,
						2-1, 7-1, 3-1, // 12
						3-1, 7-1, 8-1,
						3-1, 6-1, 4-1,
						5-1, 1-1, 4-1,
						5-1, 4-1, 8-1 }; // 36 points 


	model.indices.assign(indices, indices + sizeof(indices) / sizeof(int));
	//model.indices.assign(indices, indices + sizeof(indices) / sizeof(int));

	return model;
}





class EasyProgram : public Screen
{
private:
	FontBin fonts;
	ModelBin models;
	BitmapBin bitmaps;

	Camera3D camera;
	Model2 cube;
//	std::vector<Model2 *> models;
public:
	EasyProgram(Display *display)
		: Screen(display)
		, camera(vec3d(0,0,-10))
		, fonts()
		, cube()
//		, models()
	{
		cube = make_cube(3);
		models["car-01.obj"]->textures.set_texture_by_index(0, bitmaps["hospital_sign.png"]);
	}
	void primary_timer_func() override
	{
		//camera.position.z = -camera.position.z;
		//camera.position.z = sin(af::time_now) * 20 + 10;

		cube.place.rotation.x = sin(af::time_now) * 0.1;
		cube.place.rotation.y = cos(af::time_now) * 0.1;
		//cube.place.rotation.z = tan(af::time_now) * 0.1;

		//al_clear_depth_buffer(1000);
		//al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
		camera.set_frustum_as_camera(display->display);

		//al_draw_text(fonts["DroidSans.ttf 20"], color::white, 0, 0, ALLEGRO_ALIGN_CENTER, "Hello World");

		//Model2 cube = make_cube(3);
		//cube.draw();
		cube.place.start_transform();
		models["car-01.obj"]->draw();
		cube.place.restore_transform();

		//models["hero-06.obj"]->draw();
		//camera.set_frustum_as_camera();
	}
};

*/



int main(int argc, char *argv)
{
	af::initialize();
	//Display *display = af::create_display(Display::FULLSCREEN_AUTO);
	Display *display = af::create_display(1920/3*2, 1080/3*2);

	ProgramMaster *game_program_master = new ProgramMaster(display);
	//EasyProgram *easy_program = new EasyProgram(display);

	af::run_loop();
}