
#include "simple_terrain_script.h"

#include "engine/render/render_public_data.h"

//#define USE_NEW_VERSION

namespace PFF {

	void simple_terrain_script::on_create() {

		LOG(Info, "STARTING simple_terrain_script");

#ifndef USE_NEW_VERSION

		//m_mesh_asset->name = "simple_terrain";

		//PFF::util::noise noise(PFF::util::noise_type::perlin);
		//noise.Set_fractal_type(PFF::util::fractal_type::FBm);
		//noise.set_frequency(0.005f);
		//noise.set_fractal_octaves(4);
		//noise.set_fractal_lacunarity(2.3f);

		const glm::ivec2 grid_size = glm::ivec2(5);			// number of grid tiles
		const glm::vec2 grid_tile_size = glm::ivec2(100);	// size of a grid tile
		const glm::vec2 grid_resolution = glm::ivec2(100);
		const int iterations_x = static_cast<u32>(grid_size.x * grid_resolution.x);
		const int iterations_y = static_cast<u32>(grid_size.y * grid_resolution.y);

		const glm::vec2 offset = glm::vec2(
			(static_cast<f32>(grid_size.x) / 2) * grid_tile_size.x,
			(static_cast<f32>(grid_size.y) / 2) * grid_tile_size.y
		);
		const glm::vec2 pos_multiplier = glm::vec2(
			(grid_tile_size.x / grid_resolution.x),
			(grid_tile_size.y / grid_resolution.y)
		);

		m_mesh_asset->vertices.resize((iterations_x + 1) * (iterations_y + 1));
		m_mesh_asset->indices.resize((iterations_x * iterations_y) * 6);

		int counter = 0;
		for (int y = 0; y <= iterations_y; ++y) {
			for (int x = 0; x <= iterations_x; ++x) {

				m_mesh_asset->vertices[counter] = geometry::vertex(
					glm::vec3(
					(x * pos_multiplier.x) - offset.x,
					/*noise.get_noise((f32)x, (f32)y) * */50.f,
					(y * pos_multiplier.y) - offset.y
				),
					{ 0, 0, 1 },
					glm::vec4{ 1.f },
					static_cast<f32>(x) / grid_resolution.x,
					static_cast<f32>(y) / grid_resolution.y
				);
				counter++;
			}
		}

		counter = 0;
		for (int y = 0; y < iterations_y; y++) {
			for (int x = 0; x < iterations_x; x++) {

				int top_left = y * ((iterations_x)+1) + x;
				int top_right = top_left + 1;
				int bottom_left = (y + 1) * ((iterations_x)+1) + x;
				int bottom_right = bottom_left + 1;

				m_mesh_asset->indices[counter + 0] = top_left;
				m_mesh_asset->indices[counter + 1] = bottom_left;
				m_mesh_asset->indices[counter + 2] = top_right;

				m_mesh_asset->indices[counter + 3] = top_right;
				m_mesh_asset->indices[counter + 4] = bottom_left;
				m_mesh_asset->indices[counter + 5] = bottom_right;
				counter += 6;
			}
		}

		geometry::Geo_surface new_surface{};
		new_surface.count = static_cast<int>(m_mesh_asset->indices.size());
		m_mesh_asset->surfaces.push_back(new_surface);

		recalculate_bounds();
		apply_mesh();

#else

		m_mesh_asset->name = "simple_terrain";

		PFF::util::noise noise(PFF::util::noise_type::perlin);
		noise.Set_fractal_type(PFF::util::fractal_type::FBm);
		noise.set_frequency(0.005f);
		noise.set_fractal_octaves(4);
		noise.set_fractal_lacunarity(2.3f);

		const glm::ivec2 grid_size = glm::ivec2(5);			// number of grid tiles
		const glm::vec2 grid_tile_size = glm::ivec2(100);	// size of a grid tile
		const glm::vec2 grid_resolution = glm::ivec2(100);
		const int iterations_x = static_cast<u32>(grid_size.x * grid_resolution.x);
		const int iterations_y = static_cast<u32>(grid_size.y * grid_resolution.y);

		const glm::vec2 offset = glm::vec2(
			(static_cast<f32>(grid_size.x) / 2) * grid_tile_size.x,
			(static_cast<f32>(grid_size.y) / 2) * grid_tile_size.y
		);
		const glm::vec2 pos_multiplier = glm::vec2(
			(grid_tile_size.x / grid_resolution.x),
			(grid_tile_size.y / grid_resolution.y)
		);

		m_mesh_asset->vertices.resize((iterations_x + 1) * (iterations_y + 1));
		m_mesh_asset->indices.resize((iterations_x * iterations_y) * 6);

		int counter = 0;
		for (int y = 0; y <= iterations_y; ++y) {
			for (int x = 0; x <= iterations_x; ++x) {

				add_vertex(glm::vec3((x * pos_multiplier.x) - offset.x, noise.get_noise((f32)x,
						(f32)y) * 50.f,
						(y * pos_multiplier.y) - offset.y),
					{ 0, 0, 1 },
					glm::vec2((f32)x / grid_resolution.x, (f32)y / grid_resolution.y));
				counter++;
			}
		}

		counter = 0;
		for (int y = 0; y < iterations_y; y++) {
			for (int x = 0; x < iterations_x; x++) {

				const int top_left = y * ((iterations_x)+1) + x;
				const int top_right = top_left + 1;
				const int bottom_left = (y + 1) * ((iterations_x)+1) + x;
				const int bottom_right = bottom_left + 1;

				add_quad(top_left, bottom_left, top_right, bottom_right);
				counter += 6;
			}
		}

		add_surface(0, static_cast<int>(m_mesh_asset->indices.size()));
		recalculate_bounds();
		apply_mesh();

#endif
	}

}