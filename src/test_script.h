#pragma once

#include <PFF.h>

namespace PFF {
	
	PFF_CLASS();
	class DefaultScript : public entity_script {
	public:

		void on_create() { LOG(Info, "STARTING script"); }
		void on_destroy() { LOG(Error, "ENDING sdfgsdfipt"); }
		void on_update(f32 delta_time) { /*LOG(Debug, "script time: " << delta_time);*/ }

	public:
		PFF_PROPERTY();
		float m_example_float_property = 3.14f;

		PFF_PROPERTY();
		int m_example_int_property = 42;
	};
}
