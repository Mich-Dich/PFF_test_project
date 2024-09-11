
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "tree_generator.h"

namespace test_project {
	
	static PFF::util::random random;
	static point* m_root;
    static u32 branch_max_depth = 0;
    static u32 trunk_max_depth = 0;


    void tree_generator::generate_trunk(point* parent, u32 current_segment) {

        if (current_segment >= branch_max_depth) {

            generate_branches(parent, 0, parent->direction);
            return;
        }

        float length = trunk_section_length + random.get_f32(-trunk_section_length_variation, trunk_section_length_variation);
        glm::vec3 end = parent->position + parent->direction * length;

        float size_ratio = 1.0f - (float)current_segment / trunk_segment_count;
        float new_size = starting_size * size_ratio;

        add_debug_line(parent->position, end, glm::vec4(0, 1, 0, 1), true);

        add_debug_cross(end, new_size);
        point* new_point = new point(end, parent->direction, length, new_size);
        parent->children.push_back(new_point);

        if (random.get_f32(0, 1) < trunk_split_chance) {

            glm::vec3 new_direction = glm::rotate(parent->direction, glm::radians(random.get_f32(-30.0f, 30.0f)), glm::vec3(1, 0, 0));
            new_direction = glm::rotate(new_direction, glm::radians(random.get_f32(-30.0f, 30.0f)), glm::vec3(0, 1, 0));
            point* split = new point(end, glm::normalize(new_direction), length, new_size);
            parent->children.push_back(split);
            generate_trunk(split, current_segment + 1);
        }

        generate_trunk(new_point, current_segment + 1);
    }

    void tree_generator::generate_branches(point* parent, u32 depth, glm::vec3 prefered_direction) {

        if (depth >= branch_max_depth)
            return;

        f32 new_length = branch_section_length * random.get_f32(-branch_section_length_variation, branch_section_length_variation);
        glm::vec3 new_direction = prefered_direction * random.get_vec3(-branch_direction_variation, branch_direction_variation);
        glm::vec3 end = parent->position + (new_length * new_direction);
        add_debug_line(parent->position, end, glm::vec4(0, 0, 1, 1), true);

        float size_ratio = 1.0f - (float)depth / branch_max_depth;
        float new_size = parent->size * size_ratio;
        point* child = new point(end, glm::normalize(new_direction), new_length, new_size);
        parent->children.push_back(child);

        const bool is_spliting = random.get_percent(branch_split_chance);

        if (is_spliting) {

            // generate a vector that has a diviation oposite from [child_diraction relative to prefered_direction]
            glm::vec3 branch_direction = prefered_direction;

            generate_branches(child, depth + 1, branch_direction);    // split of a new branch
        }
        
        generate_branches(child, depth + 1, glm::normalize(new_direction));        // continue with current branch
    }


	void tree_generator::on_create() {

        random = PFF::util::random(random_seed);
        m_root = new point(glm::vec3(0), direction, trunk_section_length, starting_size);     

        branch_max_depth = branch_segment_count + random.get_u32(0, branch_segment_count_variation);
        trunk_max_depth = trunk_segment_count + random.get_u32(0, trunk_segment_count_variation);
        generate_trunk(m_root, 0);
	}

	void tree_generator::on_destroy() {

		clear_debug_line();
		delete m_root;			// Clean up the old tree
	}

	void tree_generator::on_rebuild() {

		clear_debug_line();
		delete m_root;			// Clean up the old tree
		on_create();
	}

}
