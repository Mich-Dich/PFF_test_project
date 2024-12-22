
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "tree_generator.h"

namespace test_project {
	
	static PFF::util::random random;
	static point* m_root;
    static u32 branch_max_depth = 0;
    static u32 trunk_max_depth = 0;
    static std::vector<point*> all_points;

	// HELPFULL TIP
	//		random.get_f32( MIN, MAX )                          gives a random float
	//		random.get_percent( PERCENT_FROM_0_TO_1 )           gives a bool weighted by the percent
	//		random.get_vec3( MIN, MAX )                         gives a random vector

    // calculate repulsion force
    static glm::vec3 calculate_repulsion(const glm::vec3& position, const f32 radius) {

        glm::vec3 repulsion(0.0f);
        for (const auto& p : all_points) {
            const glm::vec3 diff = position - p->position;
            const f32 distance = glm::length(diff);
            if (distance > 0 && distance < radius)
                repulsion += glm::normalize(diff) * (1.0f - distance / radius);
        }
        return repulsion;
    }


    point* tree_generator::find_point_at_height(point* start, f32 target_height) {

        f32 current_height = 0;
        point* current = start;

        while (current && current->children.size() > 0) {
            if (current_height + current->length >= target_height)
                return current;
            
            current_height += current->length;
            current = current->children[0];  // Assume the first child is the main trunk
        }
        return current;
    }


    void tree_generator::generate_trunk(point* parent, u32 current_segment, f32 split_chance) {

        if (current_segment >= trunk_max_depth)
            return;

        // Calculate new direction
        const f32 angle = glm::radians(random.get<f32>(-trunk_section_settings.direction_variation, trunk_section_settings.direction_variation));
        const glm::vec3 rotation_axis = glm::cross(parent->direction, glm::vec3(random.get<f32>(-1, 1), 0, random.get<f32>(-1, 1)));
        glm::vec3 new_direction = glm::rotate(parent->direction, angle, rotation_axis);

        // Lerp towards grow direction
        const f32 lerp_factor = glm::min(current_segment / static_cast<float>(trunk_max_depth), 1.0f);
        new_direction = glm::normalize(PFF::math::lerp(new_direction, grow_direction, lerp_factor * trunk_section_settings.direction_change_speed));

        // Calculate new length and position
        const f32 new_length = trunk_section_settings.section_default_length * (1.0f + random.get<f32>(-trunk_section_settings.section_length_variation, trunk_section_settings.section_length_variation));
        glm::vec3 new_position = parent->position + new_direction * new_length;

        // Apply repulsion
        const f32 repulsion_radius = new_length * trunk_repulsion_strength;
        const glm::vec3 repulsion = calculate_repulsion(new_position, repulsion_radius);
        new_position += repulsion * trunk_repulsion_influence;

        // Update grow direction based on repulsion
        const glm::vec3 updated_grow_direction = glm::normalize(grow_direction + repulsion * trunk_influence_of_repulsion_on_grow_direction);
        new_direction = glm::normalize(PFF::math::lerp(new_direction, updated_grow_direction, lerp_factor * trunk_section_settings.direction_change_speed));

        const f32 new_size = parent->size * (1.0f - current_segment / static_cast<f32>(trunk_max_depth));

        point* new_point = new point(new_position, new_direction, new_length, new_size);
        parent->children.push_back(new_point);
        all_points.push_back(new_point);

        add_debug_line(parent->position, new_position, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        generate_trunk(new_point, current_segment + 1, split_chance);

        if (random.get_percent(split_chance)) {
        
            const glm::vec3 split_direction = glm::rotate(new_direction, angle * random.get<f32>(0.6f, glm::two_pi<f32>()), rotation_axis);
            point* split_point = new point(new_position, split_direction, new_length, new_size);
            parent->children.push_back(split_point);
            all_points.push_back(split_point);
            generate_trunk(split_point, current_segment + 5, split_chance * 0.5f);
        }
    }


    void tree_generator::generate_branches(point* parent, u32 depth, glm::vec3 prefered_direction, f32 split_chance) {

        LOG(Debug, "branch [" << depth << "] branch_max_depth [" << branch_max_depth << "]");
        if (depth >= branch_max_depth)
            return;
        
        
        //add_debug_line(parent->position, parent->position + prefered_direction, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        
        const f32 lerp_factor = glm::min(depth / static_cast<float>(branch_max_depth), 1.0f);
        const glm::vec3 new_direction = glm::normalize(PFF::math::lerp(prefered_direction, (branch_section_settings.grow_direction + random.get_vec3(-0.5f, 0.5f)), lerp_factor * branch_section_settings.direction_change_speed));

        const f32 new_length = branch_section_settings.section_default_length * (1.0f + random.get<f32>(-branch_section_settings.section_length_variation, branch_section_settings.section_length_variation));
        glm::vec3 new_position = parent->position + new_direction * new_length;

        const f32 new_size = parent->size * (1.0f - depth / static_cast<f32>(branch_max_depth));

        point* new_point = new point(new_position, new_direction, new_length, new_size);
        parent->children.push_back(new_point);
        all_points.push_back(new_point);

        add_debug_line(parent->position, new_position, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

        generate_branches(new_point, depth + 1, prefered_direction, split_chance * 0.8f);

        //if (random.get_percent(split_chance)) {             // Chance to split

        //    const glm::vec3 split_direction = glm::rotate(new_direction, angle * random.get<f32>(0.6f, glm::two_pi<f32>()), rotation_axis);
        //    point* split_point = new point(new_position, split_direction, new_length, new_size);
        //    parent->children.push_back(split_point);
        //    all_points.push_back(split_point);
        //    generate_branches(split_point, depth + 1, prefered_direction, split_chance * 0.5f);
        //}
    }


    void tree_generator::on_create() {

        if (random_seed > -1)
            random = PFF::util::random(random_seed);
        else
            random = PFF::util::random();


        m_root = new point(glm::vec3(0), starting_direction, trunk_section_settings.section_default_length, starting_size);
        all_points.clear();
        all_points.push_back(m_root);

        branch_max_depth = PFF::math::max<u32>(1, (branch_segment_count + random.get<int32>(-(int32)branch_segment_count_variation, branch_segment_count_variation)));
        trunk_max_depth = PFF::math::max<u32>(1, (trunk_segment_count + random.get<int32>(-(int32)trunk_segment_count_variation, trunk_segment_count_variation)));
        LOG(Debug, "setting branch_max_depth to: " << branch_max_depth);

        generate_trunk(m_root, 0, trunk_section_settings.split_chance);

        u32 start_index = (u32)((f32)trunk_max_depth * branch_spawn_height);
        std::vector<point*> trunk_points{ m_root };
        u32 iteration = 0;
        while (trunk_points.size()) {

            std::vector<point*> buffer{};
            for (point* current : trunk_points)
                for (point* child : current->children)
                    buffer.push_back(child);                                            // get all points of trunk and any sub trunk

            if (iteration >= start_index) {                                             // Check if we've passed the branch spawn height

                for (point* current : trunk_points) {
                    if (random.get_percent(branch_spawn_chance)) {                          // Chance to spawn a branch at this point

                        // Generate a random direction in the horizontal plane
                        f32 random_angle = random.get<f32>(0, glm::two_pi<f32>());
                        glm::vec3 random_direction = glm::vec3(std::cos(random_angle), 0, std::sin(random_angle));
                        generate_branches(current, 0, random_direction, branch_section_settings.split_chance);
                    }
                }
            }

            trunk_points = buffer;
            iteration++;
        }
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
