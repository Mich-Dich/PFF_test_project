#pragma once

#include <PFF.h>

namespace test_project {

	// MAYBE: potential upgrade		
	//		rebuild_on_property_change												will rebuild when any property is changed
	//		rebuild_on_wached_property_change		PFF_PROPERTY(watched)			will rebuild when a wached property is changed

	PFF_STRUCT();
	struct point {

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

		point(const glm::vec3& pos, const glm::vec3& dir, float len, float sz)
			: position(pos), direction(dir), length(len), size(sz) {}

		~point() {
			for (auto child : children) 
				delete child;
		}
	};

	PFF_CLASS(rebuild_on_property_change);
	class tree_generator : public PFF::procedural_mesh_script {
	public:

		void on_create();
		void on_destroy() { LOG(Error, "ENDING script"); }
		void on_update(f32 delta_time);
		void on_rebuild();

		PFF_PROPERTY(category: "trunk", display_name : "direction", UI_slider_drag_speed : 0.01f, min_value : 0.f, max_value : 1.f);
		glm::vec3 trunk_direction = glm::vec3(0, 1, 0);

		PFF_PROPERTY(category: "trunk", display_name : "length", UI_slider_drag_speed : 0.01f, min_value : 0.f, max_value : 1.f);
		f32 trunk_length = 50.0f;
		
		PFF_PROPERTY(category: "trunk", display_name : "size", UI_slider_drag_speed : 0.01f, min_value : 0.f, max_value : 1.f);
		f32 trunk_size = 1.0f;

		PFF_PROPERTY(category: "trunk", display_name : "max depth", UI_slider_drag_speed : 0.01f, min_value : 0.f, max_value : 1.f);
		u32 max_depth = 5;

	private:
		
		PFF_FUNCTION();
		void generate_tree_structure(point* parent, int depth, int max_depth);

	};
}
