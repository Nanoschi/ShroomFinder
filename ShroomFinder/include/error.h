#pragma once

enum class ErrorType {
	WindowError = 1,
	RendererError,
	FileError
};

auto reportError(ErrorType type, bool terminate = true) -> void;
