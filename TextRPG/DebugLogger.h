#pragma once
#include "BaseIncludes.h"
#include "imgui.h"

enum class LogLevel
{
	Error,
	Warning,
	Message
};

class DebugLogger
{
private:
	ImGuiTextBuffer     Buffer;
	ImGuiTextFilter     Filter;
	ImVector<int>       LineOffsets;
	bool                AutoScroll;

	void LogMessage(LogLevel level, const char* msg, va_list args);

	DebugLogger();
	DebugLogger(const DebugLogger& other) = delete;

public:
	static DebugLogger& GetInstance();
	void Shutdown();
	
	void Clear();
	void Draw();

	void LogError(const char* msg, ...);
	void LogWarning(const char* msg, ...);
	void LogMessage(const char* msg, ...);
};