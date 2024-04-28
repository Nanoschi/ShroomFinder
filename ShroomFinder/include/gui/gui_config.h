#pragma once
#include <string>
#include "SDL_render.h"

constexpr int DefaultWinWidth = 800;
constexpr int DefaultWinHeight = 800;

constexpr SDL_Color ClearColor{ 220, 220, 220, SDL_ALPHA_OPAQUE };

const std::string WinTitle = "Shroom Finder";

constexpr float ZoomSpeed = 1.1f;

constexpr int LargeMapTileXCount = 4;
constexpr int LargeMapTileYCount = 4;

constexpr double MapMaxLatitude = 53.6044905;
constexpr double MapMinLatitude = 47.149781116;

constexpr double MapMaxlongitude = 15.051238378;
constexpr double MapMinLongitude = 5.852489869;