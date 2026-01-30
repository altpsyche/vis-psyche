#pragma once

namespace VizEngine
{
	// Common OpenGL types and utilities

	/**
	 * Standard texture slot assignments for PBR rendering.
	 * Use these constants to avoid slot collisions between materials and manual binding.
	 */
	namespace TextureSlots
	{
		// Material textures (0-4)
		constexpr int Albedo = 0;
		constexpr int Normal = 1;
		constexpr int MetallicRoughness = 2;
		constexpr int AO = 3;
		constexpr int Emissive = 4;

		// IBL textures (5-7)
		constexpr int Irradiance = 5;
		constexpr int Prefiltered = 6;
		constexpr int BRDF_LUT = 7;

		// Shadow map (8)
		constexpr int ShadowMap = 8;

		// Post-processing (9-11)
		constexpr int HDRBuffer = 9;
		constexpr int BloomTexture = 10;
		constexpr int ColorGradingLUT = 11;

		// User/custom (12-15)
		constexpr int Custom0 = 12;
		constexpr int Custom1 = 13;
		constexpr int Custom2 = 14;
		constexpr int Custom3 = 15;
	}
}