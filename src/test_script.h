#pragma once

#include <PFF.h>

namespace PFF {

	PFF_CLASS();
	class DefaultScript : public entity_script {
	public:


	public:
		PFF_PROPERTY();
		float m_ExampleFloatProperty = 3.14f;

		PFF_PROPERTY();
		int m_ExampleIntProperty = 10;
	};
}
