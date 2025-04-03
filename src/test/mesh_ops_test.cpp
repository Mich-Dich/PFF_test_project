
#include <PFF.h>

#include "mesh_ops_test.h"

namespace mesh_ops {

	PFF::util::random random;

	void mesh_ops::on_create() {

		random = PFF::util::random( 42 );

		//for (u32 x = 0; x <= 20; x++) {
		//	add_cube(random.get_vec3(-10, 10), random.get_vec3(0, 2), random.get_vec3(-glm::two_pi<f32>(), glm::two_pi<f32>()));
		//	add_sphere(random.get_vec3(-10, 10), random.get_vec3(0, 2), random.get_vec3(-glm::two_pi<f32>(), glm::two_pi<f32>()));
		//}



		u64 cube = add_cube(glm::vec3(0.0f), glm::vec3(2.f), glm::vec3(0.0f, 0.0f, 0.0f));
		u64 cube_2 = add_cube(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(2.f), glm::vec3(0.0f, 0.0f, 0.0f));
		
		//u64 index = boolean_subtract(cube, cube_2);
		//LOG(Trace, "index: " << index);

		recalculate_bounds();
		show_debug_bounds(m_mesh_asset.bounds_data);
		apply_mesh();
	}

	void mesh_ops::on_update(f32 delta_time) { }

}
