#pragma once

namespace mesh_ops {

	PFF_CLASS();
	class mesh_ops : public PFF::procedural_mesh_script {
	public:

		void on_create();
		void on_destroy() { LOG(Error, "ENDING script"); }
		void on_update(f32 delta_time);

	};
}
