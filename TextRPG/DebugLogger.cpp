#include "DebugLogger.h"
#include <regex>

std::unique_ptr<DebugLogger> DebugLogger::mInstance = nullptr;

DebugLogger* DebugLogger::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = std::make_unique<DebugLogger>();
	}

	return mInstance.get();
}

DebugLogger::DebugLogger()
{
	AutoScroll = true;
	Clear();
}

void DebugLogger::Clear()
{
	Buffer.clear();
	LineOffsets.clear();
	LineOffsets.push_back(0);
}

void DisplayText(const char* textStart, const char* textEnd)
{
	ImVec4 vec4colour;
	std::string line(textStart);
	size_t lineLength = textEnd - textStart;
	line = line.substr(0, lineLength);

	std::regex colourRegex("##.{8}.*?\\$\\$");

	auto coloursIterBegin = std::sregex_iterator(line.begin(), line.end(), colourRegex);
	auto coloursIterEnd = std::sregex_iterator();

	auto stringSplitBegin = std::sregex_token_iterator(line.begin(), line.end(), colourRegex, -1);
	auto stringSplitEnd = std::sregex_token_iterator();

	bool stringComplete = false;

	auto coloursIter = coloursIterBegin;
	auto stringSplitIter = stringSplitBegin;	

	while (!stringComplete)
	{
		if (coloursIter == coloursIterEnd && stringSplitIter == stringSplitEnd)
		{
			stringComplete = true;
		}
		else
		{
			if (stringSplitIter != stringSplitEnd)
			{
				std::string split = stringSplitIter->str();
				ImGui::TextUnformatted(split.c_str());				

				++stringSplitIter;
				if (split.length() == 0 || split[split.length() - 1] != '\n')
				{
					if (stringSplitIter != stringSplitEnd)
					{
						ImGui::SameLine();
					}
				}
			}

			if (coloursIter != coloursIterEnd)
			{
				std::string match = (*coloursIter).str();

				uint32 colour = std::stol(match.substr(2, 6), nullptr, 16);
				std::string rest = match.substr(8);
				rest = rest.erase(rest.length() - 2);

				vec4colour.x = (colour & 0xFF0000) >> 16;
				vec4colour.y = (colour & 0x00FF00) >> 8;
				vec4colour.z = (colour & 0x0000FF);
				vec4colour.w = 0xFF;

				ImGui::TextColored(vec4colour, rest.c_str());
				ImGui::SameLine();

				++coloursIter;
			}
		}
	}
}

void DebugLogger::Draw()
{
	if (!ImGui::Begin("Debug Logger"))
	{
		ImGui::End();
		return;
	}

	// Options menu
	if (ImGui::BeginPopup("Options"))
	{
		ImGui::Checkbox("Auto-scroll", &AutoScroll);
		ImGui::EndPopup();
	}

	// Main window
	if (ImGui::Button("Options"))
		ImGui::OpenPopup("Options");
	ImGui::SameLine();
	bool clear = ImGui::Button("Clear");
	ImGui::SameLine();
	bool copy = ImGui::Button("Copy");
	ImGui::SameLine();
	Filter.Draw("Filter", -100.0f);

	ImGui::Separator();
	ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

	if (clear)
		Clear();
	if (copy)
		ImGui::LogToClipboard();

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	const char* buf = Buffer.begin();
	const char* buf_end = Buffer.end();
	if (Filter.IsActive())
	{
		// In this example we don't use the clipper when Filter is enabled.
		// This is because we don't have a random access on the result on our filter.
		// A real application processing logs with ten of thousands of entries may want to store the result of search/filter.
		// especially if the filtering function is not trivial (e.g. reg-exp).
		for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
		{
			const char* line_start = buf + LineOffsets[line_no];
			const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
			if (Filter.PassFilter(line_start, line_end))
				DisplayText(line_start, line_end);
		}
	}
	else
	{
		// The simplest and easy way to display the entire buffer:
		//   ImGui::TextUnformatted(buf_begin, buf_end);
		// And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward to skip non-visible lines.
		// Here we instead demonstrate using the clipper to only process lines that are within the visible area.
		// If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them on your side is recommended.
		// Using ImGuiListClipper requires A) random access into your data, and B) items all being the  same height,
		// both of which we can handle since we an array pointing to the beginning of each line of text.
		// When using the filter (in the block of code above) we don't have random access into the data to display anymore, which is why we don't use the clipper.
		// Storing or skimming through the search result would make it possible (and would be recommended if you want to search through tens of thousands of entries)
		ImGuiListClipper clipper;
		clipper.Begin(LineOffsets.Size);
		while (clipper.Step())
		{
			for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
			{
				const char* line_start = buf + LineOffsets[line_no];
				const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
				DisplayText(line_start, line_end);
			}
		}
		clipper.End();
	}
	ImGui::PopStyleVar();

	if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		ImGui::SetScrollHereY(1.0f);

	ImGui::EndChild();
	ImGui::End();
}

void DebugLogger::LogMessage(LogLevel level, const char* msg, va_list args)
{
	int old_size = Buffer.size();

	std::string m(msg);
	m += "\n";

	va_list args_copy;
	va_copy(args_copy, args);

	Buffer.appendfv(m.c_str(), args_copy);

	va_end(args_copy);

	for (int new_size = Buffer.size(); old_size < new_size; old_size++)
	{
		if (Buffer[old_size] == '\n')
		{
			LineOffsets.push_back(old_size + 1);
		}
	}
}

void DebugLogger::LogError(const char* msg, ...)
{
	va_list args;
	va_start(args, msg);

	std::string m(msg);
	m = "##DF0000[ERROR]:$$ " + m;

	LogMessage(LogLevel::Error, m.c_str(), args);
	va_end(args);
}

void DebugLogger::LogWarning(const char* msg, ...)
{
	va_list args;
	va_start(args, msg);

	std::string m(msg);
	m = "##FF9E00[WARNING]:$$ " + m;

	LogMessage(LogLevel::Warning, m.c_str(), args);
	va_end(args);
}

void DebugLogger::LogMessage(const char* msg, ...)
{
	va_list args;
	va_start(args, msg);

	std::string m(msg);
	m = "##B9D9D9[DEBUG]:$$ " + m;

	LogMessage(LogLevel::Message, m.c_str(), args);
	va_end(args);
}