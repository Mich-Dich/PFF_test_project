
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "tree_generator.h"

namespace test_project {
	
	static PFF::util::random random{};
	static point* m_root;


	void tree_generator::generate_tree_structure(point* parent, int depth, int max_depth) {

		if (depth > max_depth) return;

		glm::vec3 end = parent->position + parent->direction * parent->length;
		add_debug_line(parent->position, end, true);

		if (depth == max_depth) return;

		int num_branches = random.get_u32(1, 4);
		for (int i = 0; i < num_branches; ++i) {

			float angle_x = glm::radians(random.get_f32(-45.0f, 45.0f));
			float angle_y = glm::radians(random.get_f32(-45.0f, 45.0f));
			float angle_z = glm::radians(random.get_f32(-45.0f, 45.0f));

			glm::vec3 new_direction = glm::rotate(parent->direction, angle_x, glm::vec3(1, 0, 0));
			new_direction = glm::rotate(new_direction, angle_y, glm::vec3(0, 1, 0));
			new_direction = glm::rotate(new_direction, angle_z, glm::vec3(0, 0, 1));

			float new_length = parent->length * 0.8f;
			float new_size = parent->size * 0.8f;

			point* child = new point(end, glm::normalize(new_direction), new_length, new_size);
			parent->children.push_back(child);

			generate_tree_structure(child, depth + 1, max_depth);
		}
	}


	void tree_generator::on_create() {

		// start cross for visual help
		add_debug_cross(glm::vec3(), 10);

		m_root = new point(glm::vec3(0), trunk_direction, trunk_length, trunk_size);
		generate_tree_structure(m_root, 0, max_depth);
	}

	void tree_generator::on_update(f32 delta_time) { }

	void tree_generator::on_rebuild() {

		LOG(Trace, "tree_generator::on_rebuild()");
		clear_debug_line();
		delete m_root;			// Clean up the old tree
		on_create();
	}

}
