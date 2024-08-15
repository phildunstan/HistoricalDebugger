// Copyright Philip Dunstan

#pragma once

#include "CoreMinimal.h"
#include "imgui.h"

namespace HistoricalDebuggerImGui
{
    HISTORICALDEBUGGER_API bool Begin(const TCHAR* Name, bool* Open = nullptr, ImGuiWindowFlags Flags = 0); // Push a new Dear ImGui window to add widgets to.
    HISTORICALDEBUGGER_API void End();
	
    HISTORICALDEBUGGER_API void RecordedTextUnformatted(const FString& Id, FString& Text); // raw text without formatting.

	template <typename FmtType, typename... Types>
	void RecordedText(const FString& Id, const FmtType& Fmt, Types... Args) // formatted text
	{
		FString Text = FString::Printf(Fmt, Args...);
		RecordedTextUnformatted(Id, Text);
	}
}

namespace HDImGui = HistoricalDebuggerImGui;