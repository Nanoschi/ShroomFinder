#pragma once

enum class ErrorType {
	WindowError = 1,
	RendererError
};

auto reportError(ErrorType type, bool terminate = true) -> void;
