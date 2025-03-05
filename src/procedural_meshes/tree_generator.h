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
		f32						size{};				// used for the size of the mesh later (radius)

		PFF_PROPERTY();
		std::vector<point*>		children{};
	};

	PFF_STRUCT(rebuild_on_property_change);
	struct section_settings {

		PFF_PROPERTY(UI_slider_drag_speed : 0.1f, min_value : 0.1f, max_value : 15.f);
		f32 section_default_length = 50.0f;

		PFF_PROPERTY(UI_slider_drag_speed : 0.02f, min_value : 0.f, max_value : 1.f);
		f32 section_length_variation = 0.2f;											// between 0-1		used as percent

		PFF_PROPERTY(UI_slider_drag_speed : 0.02f, min_value : 0.f, max_value : 60.f);
		f32 direction_variation = 40.f;													// between 0-1		used as percent		VALUE IN DEGREE
		
		PFF_PROPERTY(UI_slider_drag_speed : 0.001f, min_value : 0.f, max_value : 1.f);
		f32 split_chance = 0.34f;														// between 0-1		used as percent

		PFF_PROPERTY(UI_slider_drag_speed: 0.01f, min_value : -1.f, max_value : 1.f);
		glm::vec3 starting_direction = glm::vec3(0, 1, 0);

		PFF_PROPERTY(UI_slider_drag_speed: 0.01f, min_value : -1.f, max_value : 1.f);
		glm::vec3 grow_direction = glm::vec3(0, 1, 0);									// lerp to grow direction

		PFF_PROPERTY(UI_slider_drag_speed: 0.01f, min_value : 0.f, max_value : 10.f);
		f32 direction_change_speed = 0.5f;			// lerp between start- and grow-direction     0.3f means after 30% of the points for that section, the lerp time should be 1       This lets the trunk/branches start out in one direction and then slowly change to the grow direction

	};


	PFF_CLASS(rebuild_on_property_change);
	class tree_generator : public PFF::procedural_mesh_script {
	public:

		void on_create() override;
		void on_destroy() override;
		void on_rebuild() override;


		PFF_PROPERTY(UI_slider_drag_speed: 0.01f, min_value: 0.f, max_value: 1.f);
		glm::vec3 starting_direction = glm::vec3(0, 1, 0);
		
		PFF_PROPERTY(UI_slider_drag_speed: 0.01f, min_value: 0.f, max_value: 1.f);
		glm::vec3 grow_direction = glm::vec3(0, 1, 0);									// lerp to grow direction
		
		PFF_PROPERTY(UI_slider_drag_speed: 0.01f, min_value: 0.f, max_value: 1.f);
		f32 grow_direction_start_point = 0.5f;									// lerp to grow direction

		PFF_PROPERTY(UI_slider_drag_speed: 0.01f, min_value: 0.f, max_value: 1.f);
		f32 starting_size = 8.0f;

		PFF_PROPERTY(UI_slider_drag_speed: 1, min_value: -1, max_value: 6854521);
		int32 random_seed = 40;


		// Trunk properties
		PFF_PROPERTY(category: "trunk");
		section_settings trunk_section_settings{ 0.7f, 0.5f, 25.f, 0.081f, glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 1.f, 0.f), 0.62f };

		PFF_PROPERTY(category: "trunk", Udisplay_name: "segment count", I_slider_drag_speed: 1, min_value: 0, max_value: 50);
		u32 trunk_segment_count = 18;

		PFF_PROPERTY(category: "trunk", display_name : "segment count variation", UI_slider_drag_speed : 1, min_value : 0, max_value : 30);
		u32 trunk_segment_count_variation = 10;

		PFF_PROPERTY(category: "trunk", display_name: "repulsion strength",  UI_slider_drag_speed: 0.01f, min_value: 0.f, max_value: 1.f);
		f32 trunk_repulsion_strength = 1.f;
			
		PFF_PROPERTY(category: "trunk", display_name: "repulsion influence",  UI_slider_drag_speed: 0.1f, min_value: 0.f, max_value: 10.f);
		f32 trunk_repulsion_influence = 1.7f;
			
		PFF_PROPERTY(category: "trunk", display_name: "influence of repulsion on grow direction",  UI_slider_drag_speed: 0.05f, min_value: 0.f, max_value: 30.f);
		f32 trunk_influence_of_repulsion_on_grow_direction = 10.f;

		// Branch properties
		PFF_PROPERTY(category: "branch", display_name: "split chance");
		section_settings branch_section_settings{ 2.f, 0.5f, 40.f, 0.35f, glm::vec3(0), glm::vec3( 0.f, 1.f, 0.f), 0.92f };

		PFF_PROPERTY(category: "branch", display_name: "spawn chance", UI_slider_drag_speed : 0.01f, min_value : 0.f, max_value : 1.0f);
		f32 branch_spawn_chance = 0.15f;
		
		PFF_PROPERTY(category: "branch", display_name: "spawn height", UI_slider_drag_speed : 0.01f, min_value : 0.f, max_value : 1.f);
		f32 branch_spawn_height = 0.3f;													// height of the trunk in percent as start point to growing branches (continue to top of trunk)

		PFF_PROPERTY(category: "branch", display_name: "split chance", UI_slider_drag_speed : 0.01f, min_value : 0.f, max_value : 1.f);
		f32 branch_split_chance = 0.5f;														// between 0-1			height along trunk to start spawning branches

		PFF_PROPERTY(category: "branch", display_name: "start angle to trunk", UI_slider_drag_speed: 1, min_value: 0, max_value: 180);
		u32 branch_start_angle_to_trunk = 90;
		
		PFF_PROPERTY(category: "branch", display_name: "segment count", UI_slider_drag_speed: 1, min_value: 0, max_value: 10);
		u32 branch_segment_count = 3;
		
		PFF_PROPERTY(category: "branch", display_name: "segment count variation", UI_slider_drag_speed: 1, min_value: 0, max_value: 10);
		u32 branch_segment_count_variation = 1;

	private:

		PFF_FUNCTION();
		void generate_trunk(point* parent, u32 current_segment, f32 split_chance);

		PFF_FUNCTION();
		void generate_branches(point* parent, u32 depth, glm::vec3 prefered_direction, f32 split_chance);

		PFF_FUNCTION();
		point* find_point_at_height(point* start, f32 target_height);

	};
}
