#pragma once

#include <PFF.h>

namespace PFF {

	PFF_CLASS();
	class simple_terrain_script : public procedural_mesh_script {
	public:

		void on_create();
		void on_destroy() { LOG(Error, "ENDING sdfgsdfipt"); }
		void on_update(f32 delta_time) { /*LOG(Debug, "script time: " << delta_time);*/ }

	};
}
