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