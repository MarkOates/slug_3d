


#include <slug_3d/collision_mesh.h>


#include <iostream>




CollisionMesh::Face::Face(AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av0, AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av1, AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av2,
	int parent_models_object_num, int parent_models_face_num,
	AllegroFlare::vec3d normal
	)
	: av0(av0)
	, av1(av1)
	, av2(av2)
	, v0(AllegroFlare::vec3d(av0.x, av0.y, av0.z))
	, v1(AllegroFlare::vec3d(av1.x, av1.y, av1.z))
	, v2(AllegroFlare::vec3d(av2.x, av2.y, av2.z))
	, centroid((v0+v1+v2)/3)
	, parent_models_object_num(parent_models_object_num)
	, parent_models_face_num(parent_models_face_num)
	, normal(normal)
{
	// make a normal, if it is not provided << YOU WERE HERE!!
}




bool CollisionMesh::Face::intersect(const allegro_flare::Ray &r, allegro_flare::IsectData &isectData) const
{
	//http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-9-ray-triangle-intersection/m-ller-trumbore-algorithm/
	//#ifdef MOLLER_TRUMBORE
   AllegroFlare::vec3d edge1 = v1 - v0;
   AllegroFlare::vec3d edge2 = v2 - v0;
   AllegroFlare::vec3d pvec = cross_product(r.dir, edge2);
	float det = dot_product(edge1, pvec);
	if (det == 0) return false;
	float invDet = 1 / det;
   AllegroFlare::vec3d tvec = r.orig - v0;
	isectData.u = dot_product(tvec, pvec) * invDet;
	if (isectData.u < 0 || isectData.u > 1) return false;
   AllegroFlare::vec3d qvec = cross_product(tvec, edge1);
	isectData.v = dot_product(r.dir, qvec) * invDet;
	if (isectData.v < 0 || isectData.u + isectData.v > 1) return false;
	isectData.t = dot_product(edge2, qvec) * invDet;
//#else
//    ...
//#endif
	return true;
}



static AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL _create_vtx(AllegroFlare::vec3d vec, ALLEGRO_COLOR col)
{
   AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL ret_val;
	ret_val.x = vec.x;
	ret_val.y = vec.y;
	ret_val.z = vec.z;
	ret_val.u = 0;
	ret_val.v = 0;
	ret_val.nx = 0;
	ret_val.ny = 1;
	ret_val.nz = 0;
	ret_val.color = col;
	//return build_vertex(vec.x, vec.y, vec.z, col, 0, 0);	
	return ret_val;
}

void CollisionMesh::Face::draw(ALLEGRO_COLOR col)
{
   AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL vtx[3];
	vtx[0] = _create_vtx(v0, col);
	vtx[1] = _create_vtx(v1, col);
	vtx[2] = _create_vtx(v2, col);
	al_draw_prim(vtx, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
}



CollisionMesh::CollisionMesh(AllegroFlare::Model3D *m)
	: model(m)
	, faces()
{
   bool silence_cout = true;
	if (!silence_cout) std::cout << "+CollisionMesh()" << std::endl;
	if (!m) { std::cout << "  !*model is NULL" << std::endl; return; }
	if (m->get_num_named_objects() == 0) { std::cout << "  !*Model contains no named objects" << std::endl; return; }


	for (int o=0; o<m->get_num_named_objects(); o++)
	{
		if (!silence_cout) std::cout << "   parsing named object " << o << std::endl;
		//std::cout << "      has " << m->named_objects[o].index_list.size() << " vertexes" << std::endl;
		if (!silence_cout) std::cout << ")))" << std::endl;
		m->named_objects[0];
		if (!silence_cout) std::cout << ")))" << std::endl;
		if (!silence_cout) std::cout << o << std::endl;
		int size = m->named_objects[0].index_list.size();

		if (!silence_cout) std::cout << ")))" << std::endl;
		if (!silence_cout) std::cout << "      has " << size << " vertexes" << std::endl;
		if (!silence_cout) std::cout << ")))" << std::endl;
		if (m->named_objects[o].index_list.size() % 3 != 0)
		{
			if (!silence_cout) std::cout << "[CollisionMesh()] error: model's named_objects[].index_list.size() is not a multiple of 3; cannot load." << std::endl;
			break;
		}
		std::vector<int> &index_list = m->named_objects[o].index_list;
		for (int i=0; i<index_list.size(); i+=3)
		{
	/*
			if (m->objects[o].face_index_lists[f].size() != 3)
			{
				std::cout << "  !object " << o << " face " << f << " has " << m->objects[o].face_index_lists.size() << " vertexes." << std::endl;
				continue;
			}
	*/
			//m->objects[o].face_index_lists.size();

			faces.push_back(Face(
				m->vertexes[index_list[i]],
				m->vertexes[index_list[i+1]],
				m->vertexes[index_list[i+2]],
				o,
				i/3,
				AllegroFlare::vec3d(m->vertexes[index_list[i]].nx, m->vertexes[index_list[i]].ny, m->vertexes[index_list[i]].nz)
				// m->m->objects[o].get_face_normal(f)
				));
		}
	}
}
