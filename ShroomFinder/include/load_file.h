#pragma once
#include <fstream>

#include "opengl/texture.h"

auto loadTextFile(const std::string& path) -> std::string;

auto loadTexture(const std::string path) -> Texture;