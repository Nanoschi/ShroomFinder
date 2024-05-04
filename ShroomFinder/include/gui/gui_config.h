#pragma once
#include <string>
#include "SDL_render.h"
#include "vec2.hpp"

constexpr int DefaultWinWidth = 800;
constexpr int DefaultWinHeight = 800;

constexpr SDL_Color ClearColor{ 220, 220, 220, SDL_ALPHA_OPAQUE };

const std::string WinTitle = "Shroom Finder";

constexpr float ZoomSpeed = 1.1f;

constexpr int LargeMapTileXCount = 4;
constexpr int LargeMapTileYCount = 4;

constexpr double MapMaxLatitude = 55.0687080526247;
constexpr double MapMinLatitude = 47.149781116;

constexpr double MapMaxlongitude = 15.051238378;
constexpr double MapMinLongitude = 5.852489869;

constexpr double MapMaxLongDiff = MapMaxlongitude - MapMinLongitude;
constexpr double MapMaxLatDiff = MapMaxLatitude - MapMinLatitude;
constexpr glm::vec2 GeoSize(MapMaxLongDiff, MapMaxLatDiff);
constexpr glm::vec2 GeoMin(MapMinLongitude, MapMinLatitude);

constexpr float MapProjectionAdjustmentFactor = 0.16f;

constexpr int SpottingCategoryCount = 6;