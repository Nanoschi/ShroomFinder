#pragma once
#include <string>
#include <iostream>
#include "error.h"

namespace {
	auto _getErrorString(ErrorType type) -> std::string {
		switch (type) {
		case ErrorType::WindowError:
			return "Failed to inizielize window";
		case ErrorType::RendererError:
			return "Failed to inizialize renderer";
		default:
			return "Unknown error: " + std::to_string((int)type);
		}
	}
}

auto reportError(ErrorType type, bool terminate) -> void {
	std::cerr << "[Error]: ";
	std::cerr << _getErrorString(type);
	std::cerr << std::endl;
	if (terminate) {
		std::terminate();
	}
}