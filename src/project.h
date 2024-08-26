#pragma once

#include <PFF.h>

class PROJECT_NAME : public PFF::application {
public:

	PROJECT_NAME();
	~PROJECT_NAME();

	bool init() override;
	bool render(const f32 delta_time) override;
	bool update(const f32 delta_time) override;
	bool shutdown() override;

};

namespace PFF {

	application* create_application() { return new PROJECT_NAME(); }
}



















extern "C" __declspec(dllexport) void test_function();
