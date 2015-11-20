


#include <slug_3d/collision_mesh.h>


#include <iostream>




CollisionMesh::Face::Face(ALLEGRO_VERTEX_WITH_NORMAL av0, ALLEGRO_VERTEX_WITH_NORMAL av1, ALLEGRO_VERTEX_WITH_NORMAL av2,
	int parent_models_object_num, int parent_models_face_num,
	vec3d normal
	)
	: av0(av0)
	, av1(av1)
	, av2(av2)
	, v0(vec3d(av0.x, av0.y, av0.z))
	, v1(vec3d(av1.x, av1.y, av1.z))
	, v2(vec3d(av2.x, av2.y, av2.z))
	, centroid((v0+v1+v2)/3)
	, parent_models_object_num(parent_models_object_num)
	, parent_models_face_num(parent_models_face_num)
	, normal(normal)
{
	// make a normal, if it is not provided << YOU WERE HERE!!
}




bool CollisionMesh::Face::intersect(const Ray &r, IsectData &isectData) const
{
	//http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-9-ray-triangle-intersection/m-ller-trumbore-algorithm/
	//#ifdef MOLLER_TRUMBORE
	vec3d edge1 = v1 - v0;
	vec3d edge2 = v2 - v0;
	vec3d pvec = cross_product(r.dir, edge2);
	float det = dot_product(edge1, pvec);
	if (det == 0) return false;
	float invDet = 1 / det;
	vec3d tvec = r.orig - v0;
	isectData.u = dot_product(tvec, pvec) * invDet;
	if (isectData.u < 0 || isectData.u > 1) return false;
	vec3d qvec = cross_product(tvec, edge1);
	isectData.v = dot_product(r.dir, qvec) * invDet;
	if (isectData.v < 0 || isectData.u + isectData.v > 1) return false;
	isectData.t = dot_product(edge2, qvec) * invDet;
//#else
//    ...
//#endif
	return true;
}



static ALLEGRO_VERTEX_WITH_NORMAL _create_vtx(vec3d vec, ALLEGRO_COLOR col)
{
	ALLEGRO_VERTEX_WITH_NORMAL ret_val;
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
	ALLEGRO_VERTEX_WITH_NORMAL vtx[3];
	vtx[0] = _create_vtx(v0, col);
	vtx[1] = _create_vtx(v1, col);
	vtx[2] = _create_vtx(v2, col);
	al_draw_prim(vtx, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
}



CollisionMesh::CollisionMesh(ModelNew *m)
	: model(m)
	, faces()
{
	std::cout << "+CollisionMesh()" << std::endl;
	if (!m) { std::cout << "  !*model is NULL" << std::endl; return; }
	if (m->get_num_named_objects() == 0) { std::cout << "  !*Model contains no named objects" << std::endl; return; }


	for (int o=0; o<m->get_num_named_objects(); o++)
	{
		std::cout << "   parsing named object " << o << std::endl;
		//std::cout << "      has " << m->named_objects[o].index_list.size() << " vertexes" << std::endl;
		std::cout << ")))" << std::endl;
		m->named_objects[0];
		std::cout << ")))" << std::endl;
		std::cout << o << std::endl;
		int size = m->named_objects[0].index_list.size();

		std::cout << ")))" << std::endl;
		std::cout << "      has " << size << " vertexes" << std::endl;
		std::cout << ")))" << std::endl;
		if (m->named_objects[o].index_list.size() % 3 != 0)
		{
			std::cout << "[CollisionMesh()] error: model's named_objects[].index_list.size() is not a multiple of 3; cannot load." << std::endl;
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
				vec3d(m->vertexes[index_list[i]].nx, m->vertexes[index_list[i]].ny, m->vertexes[index_list[i]].nz)
				// m->m->objects[o].get_face_normal(f)
				));
		}
	}
}
