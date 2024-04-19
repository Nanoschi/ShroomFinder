#pragma once

enum class ErrorType {
	WindowError = 1,
	RendererError,
	FileError,
	GlewError
};

auto reportError(ErrorType type, bool terminate = true) -> void;
