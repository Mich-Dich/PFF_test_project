
#include "project.h"

PROJECT_NAME::PROJECT_NAME() { }

PROJECT_NAME::~PROJECT_NAME() { }

bool PROJECT_NAME::init()							{ return true; }

bool PROJECT_NAME::shutdown()						{ return true; }

bool PROJECT_NAME::render(const f32 delta_time)		{ return true; }

bool PROJECT_NAME::update(const f32 delta_time)		{ return true; }















void test_function() { LOG(Info, "Test function from the PROJECT"); }