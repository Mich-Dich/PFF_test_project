#pragma once

#include <PFF.h>

namespace test_project {

	PFF_CLASS();
	class simple_terrain_script : public PFF::procedural_mesh_script {
	public:

		void on_create();
		void on_destroy() { LOG(Error, "ENDING script"); }
		void on_update(f32 delta_time);

		PFF_PROPERTY(UI_slider_drag_speed: 10.f, min_value : -200.f, max_value : 200.f);
		f32 height_scale = 100.f;

	};
}
