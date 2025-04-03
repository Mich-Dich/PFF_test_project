#pragma once

#include <PFF.h>
#include <entry_point.h>

class test_project : public PFF::application {
public:

	test_project();
	~test_project();

	bool init() override;
	bool render(const f32 delta_time) override;
	bool update(const f32 delta_time) override;
	bool shutdown() override;

};

namespace PFF {		// TODO: move to generated

	application* create_application() { return new test_project(); }
}
