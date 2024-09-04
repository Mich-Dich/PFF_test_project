#pragma once

#include <PFF.h>

namespace test_project {

	PFF_CLASS();
	class simple_terrain_script : public PFF::procedural_mesh_script {
	public:

		void on_create();
		void on_destroy() { LOG(Error, "ENDING script"); }
		void on_update(f32 delta_time);

		PFF_PROPERTY();
		f32 test_f32 = 3.2425f;
		
		PFF_PROPERTY();
		u32 test_unit = 42;
		
		PFF_PROPERTY();
		u64 test_unit_long = 5;

	};
}
