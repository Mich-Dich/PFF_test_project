#pragma once

#include <PFF.h>

namespace test_project {

	// MAYBE: potential upgrade		
	//		rebuild_on_property_change												will rebuild when any property is changed
	//		rebuild_on_wached_property_change		PFF_PROPERTY(watched)			will rebuild when a wached property is changed

	PFF_STRUCT(rebuild_on_property_change);
	struct point {

		point(const glm::vec3& pos, const glm::vec3& dir, float len, float sz)
			: position(pos), direction(dir), length(len), size(sz) {}

		~point() {
			for (auto child : children)
				delete child;
		}

		PFF_PROPERTY();
		glm::vec3				position = {};

		PFF_PROPERTY();
		glm::vec3				direction = {};

		PFF_PROPERTY();
		f32						length{};

		PFF_PROPERTY();
		f32						size{};			// used for the size of the mesh later

		PFF_PROPERTY();
		std::vector<point*>		children{};
	};

	PFF_CLASS(rebuild_on_property_change);
	class tree_generator : public PFF::procedural_mesh_script {
	public:

		void on_create() override;
		void on_destroy() override;
		void on_rebuild() override;

		PFF_PROPERTY(UI_slider_drag_speed: 0.01f, min_value: 0.f, max_value: 1.f);
		glm::vec3 direction = glm::vec3(0, 1, 0);

		PFF_PROPERTY(UI_slider_drag_speed: 0.01f, min_value: 0.f, max_value: 1.f);
		f32 starting_size = 8.0f;

		PFF_PROPERTY(UI_slider_drag_speed: 1, min_value: 0, max_value: 6854521);
		u32 random_seed = 42;

		// Trunk properties
		PFF_PROPERTY(category: "trunk", display_name: "section length", UI_slider_drag_speed: 5, min_value: 10.f, max_value: 300.f);
		f32 trunk_section_length = 110.0f;

		PFF_PROPERTY(category: "trunk", display_name: "section length variation", UI_slider_drag_speed: 0.1f, min_value: 1.f, max_value: 100.f);
		f32 trunk_section_length_variation = 50.0f;

		PFF_PROPERTY(category: "trunk", display_name: "split chance", UI_slider_drag_speed: 0.01f, min_value: 0.f, max_value: 1.f);
		f32 trunk_split_chance = 0.170f;
		
		PFF_PROPERTY(category: "trunk", Udisplay_name: "segment count", I_slider_drag_speed: 1, min_value: 0, max_value: 10);
		u32 trunk_segment_count = 5;

		PFF_PROPERTY(category: "trunk", display_name : "segment count variation", UI_slider_drag_speed : 1, min_value : 0, max_value : 10);
		u32 trunk_segment_count_variation = 5;

		// Branch properties
		PFF_PROPERTY(category: "branch", display_name: "section length", UI_slider_drag_speed: 1, min_value: 1.f, max_value: 150.f);
		f32 branch_section_length = 50.0f;
		
		PFF_PROPERTY(category: "branch", display_name: "section length variation", UI_slider_drag_speed: 0.02f, min_value: 0.f, max_value: 5.f);
		f32 branch_section_length_variation = 0.2f;
		
		PFF_PROPERTY(category: "branch", display_name: "direction variation", UI_slider_drag_speed: 0.02f, min_value: 0.f, max_value: 5.f);
		f32 branch_direction_variation = 0.2f;

		PFF_PROPERTY(category: "branch", display_name: "split chance", UI_slider_drag_speed: 0.01f, min_value: 0.f, max_value: 1.f);
		f32 branch_split_chance = 0.34f;

		PFF_PROPERTY(category: "branch", display_name: "segment count", UI_slider_drag_speed: 1, min_value: 0, max_value: 10);
		u32 branch_segment_count = 5;
		
		PFF_PROPERTY(category: "branch", display_name: "segment count variation", UI_slider_drag_speed: 1, min_value: 0, max_value: 10);
		u32 branch_segment_count_variation = 5;

	private:

		PFF_FUNCTION();
		void generate_trunk(point* parent, u32 current_segment);

		PFF_FUNCTION();
		void generate_branches(point* parent, u32 depth, glm::vec3 prefered_direction);

	};
}
