
#include "project.h"

test_project::test_project() { }

test_project::~test_project() { }

bool test_project::init()							{ return true; }

bool test_project::shutdown()						{ return true; }

bool test_project::render(const f32 delta_time)		{ return true; }

bool test_project::update(const f32 delta_time)		{ return true; }















void test_function() { LOG(Info, "Test function from the PROJECT"); }