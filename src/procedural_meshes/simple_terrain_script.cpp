
#include "simple_terrain_script.h"

#include "engine/render/render_public_data.h"

namespace test_project {

	static PFF::util::noise noise(PFF::util::noise_type::perlin);
	
	static const glm::ivec2 grid_size = glm::ivec2(5);			// number of grid tiles
	static const glm::vec2 grid_tile_size = glm::ivec2(100);	// size of a grid tile
	static const glm::vec2 grid_resolution = glm::ivec2(10);
	static const int iterations_x = static_cast<u32>(grid_size.x * grid_resolution.x);
	static const int iterations_y = static_cast<u32>(grid_size.y * grid_resolution.y);

	static const glm::vec2 offset = glm::vec2(
		(static_cast<f32>(grid_size.x) / 2) * grid_tile_size.x,
		(static_cast<f32>(grid_size.y) / 2) * grid_tile_size.y
	);
	static const glm::vec2 pos_multiplier = glm::vec2(
		(grid_tile_size.x / grid_resolution.x),
		(grid_tile_size.y / grid_resolution.y)
	);

	void simple_terrain_script::on_create() {

		noise.Set_fractal_type(PFF::util::fractal_type::FBm);
		noise.set_frequency(0.005f);
		noise.set_fractal_octaves(4);
		noise.set_fractal_lacunarity(2.3f);

		int counter = 0;
		for (int y = 0; y <= iterations_y; ++y) {
			for (int x = 0; x <= iterations_x; ++x) {

				add_vertex(counter, 
					glm::vec3(
						(x * pos_multiplier.x) - offset.x,
						noise.get_noise((f32)x, (f32)y) * 50.f,
						(y * pos_multiplier.y) - offset.y),
					glm::vec3{ 0, 1, 0 },
					glm::vec2((f32)x / grid_resolution.x, (f32)y / grid_resolution.y));
				counter++;
			}
		}

		for (int y = 0; y < iterations_y; y++) {
			for (int x = 0; x < iterations_x; x++) {

				const int top_left = y * ((iterations_x)+1) + x;
				const int top_right = top_left + 1;
				const int bottom_left = (y + 1) * ((iterations_x)+1) + x;
				const int bottom_right = bottom_left + 1;
				add_quad(top_right, top_left, bottom_left, bottom_right);
			}
		}

		add_surface(0, static_cast<int>(m_mesh_asset.indices.size()));
		recalculate_bounds();
		apply_mesh();
	}

	void simple_terrain_script::on_update(f32 delta_time) {

		static f32 pos_offset = 0;
		pos_offset += delta_time * 20;
		int counter = 0;
		for (int y = 0; y <= iterations_y; ++y) {
			for (int x = 0; x <= iterations_x; ++x) {

				m_mesh_asset.vertices[counter].position.y = noise.get_noise((f32)x + pos_offset, (f32)y + pos_offset) * height_scale;
				counter++;
			}
		}
		apply_mesh();
	}

}
